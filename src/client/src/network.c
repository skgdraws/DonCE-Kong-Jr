#include "network.h"
#include <SDL3/SDL.h>
#include <string.h>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef int socklen_t;
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <fcntl.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket close
#endif

// Instancia global de conexion
static NetworkConnection connection = {
    .sockfd = INVALID_SOCKET,
    .connected = false,
    .serverAddress = "",
    .serverPort = 0
};

NetworkConnection* getNetworkConnection(void) {
    return &connection;
}

bool initNetwork(void) {
#ifdef _WIN32
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        SDL_Log("WSAStartup failed: %d", result);
        return false;
    }
    SDL_Log("Winsock inicializado correctamente");
#endif
    return true;
}

bool connectToServer(const char* address, int port) {
    if (connection.connected) {
        SDL_Log("Ya existe una conexion activa");
        return false;
    }

    // Crear socket TCP
    connection.sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connection.sockfd == INVALID_SOCKET) {
#ifdef _WIN32
        SDL_Log("Error al crear socket: %d", WSAGetLastError());
#else
        SDL_Log("Error al crear socket");
#endif
        return false;
    }

    // Configurar direccion del servidor
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    
#ifdef _WIN32
    serverAddr.sin_addr.s_addr = inet_addr(address);
    if (serverAddr.sin_addr.s_addr == INADDR_NONE) {
        SDL_Log("Direccion IP invalida");
        closesocket(connection.sockfd);
        connection.sockfd = INVALID_SOCKET;
        return false;
    }
#else
    if (inet_pton(AF_INET, address, &serverAddr.sin_addr) <= 0) {
        SDL_Log("Direccion IP invalida");
        closesocket(connection.sockfd);
        connection.sockfd = INVALID_SOCKET;
        return false;
    }
#endif

    // Conectar al servidor
    if (connect(connection.sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
#ifdef _WIN32
        SDL_Log("Error al conectar al servidor: %d", WSAGetLastError());
#else
        SDL_Log("Error al conectar al servidor");
#endif
        closesocket(connection.sockfd);
        connection.sockfd = INVALID_SOCKET;
        return false;
    }

    // Configurar socket como no bloqueante
#ifdef _WIN32
    u_long mode = 1;
    if (ioctlsocket(connection.sockfd, FIONBIO, &mode) != 0) {
        SDL_Log("Error al configurar socket no bloqueante: %d", WSAGetLastError());
        closesocket(connection.sockfd);
        connection.sockfd = INVALID_SOCKET;
        return false;
    }
#else
    int flags = fcntl(connection.sockfd, F_GETFL, 0);
    if (fcntl(connection.sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        SDL_Log("Error al configurar socket no bloqueante");
        closesocket(connection.sockfd);
        connection.sockfd = INVALID_SOCKET;
        return false;
    }
#endif

    // Guardar informacion de conexion
    strncpy(connection.serverAddress, address, sizeof(connection.serverAddress) - 1);
    connection.serverPort = port;
    connection.connected = true;

    SDL_Log("Conectado al servidor %s:%d", address, port);
    return true;
}

void disconnectFromServer(void) {
    if (connection.sockfd != INVALID_SOCKET) {
        closesocket(connection.sockfd);
        connection.sockfd = INVALID_SOCKET;
    }
    connection.connected = false;
    SDL_Log("Desconectado del servidor");
}

bool sendToServer(const char* data, size_t length) {
    if (!connection.connected || connection.sockfd == INVALID_SOCKET) {
        SDL_Log("No hay conexion activa");
        return false;
    }

    int totalSent = 0;
    while (totalSent < length) {
        int sent = send(connection.sockfd, data + totalSent, length - totalSent, 0);
        if (sent == SOCKET_ERROR) {
#ifdef _WIN32
            int error = WSAGetLastError();
            if (error != WSAEWOULDBLOCK) {
                SDL_Log("Error al enviar datos: %d", error);
                disconnectFromServer();
                return false;
            }
#else
            if (errno != EWOULDBLOCK && errno != EAGAIN) {
                SDL_Log("Error al enviar datos");
                disconnectFromServer();
                return false;
            }
#endif
            // Socket no bloqueante, reintentar
            SDL_Delay(1);
            continue;
        }
        totalSent += sent;
    }

    return true;
}

int receiveFromServer(char* buffer, size_t bufferSize) {
    if (!connection.connected || connection.sockfd == INVALID_SOCKET) {
        return -1;
    }

    int received = recv(connection.sockfd, buffer, bufferSize - 1, 0);
    
    if (received == SOCKET_ERROR) {
#ifdef _WIN32
        int error = WSAGetLastError();
        if (error == WSAEWOULDBLOCK) {
            return 0; // No hay datos disponibles
        }
        SDL_Log("Error al recibir datos: %d", error);
#else
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            return 0; // No hay datos disponibles
        }
        SDL_Log("Error al recibir datos");
#endif
        disconnectFromServer();
        return -1;
    }
    
    if (received == 0) {
        SDL_Log("Servidor cerro la conexion");
        disconnectFromServer();
        return -1;
    }

    buffer[received] = '\0';
    return received;
}

bool isConnected(void) {
    return connection.connected && connection.sockfd != INVALID_SOCKET;
}

void cleanupNetwork(void) {
    disconnectFromServer();
#ifdef _WIN32
    WSACleanup();
    SDL_Log("Winsock limpiado");
#endif
}
