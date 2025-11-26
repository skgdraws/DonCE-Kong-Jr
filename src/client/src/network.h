#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>
#include <stddef.h>

// Estructura de conexion de red
typedef struct {
    int sockfd;
    bool connected;
    char serverAddress[256];
    int serverPort;
} NetworkConnection;

// Inicializar el sistema de red
bool initNetwork(void);

// Conectar al servidor Java
bool connectToServer(const char* address, int port);

// Desconectar del servidor
void disconnectFromServer(void);

// Enviar datos al servidor
bool sendToServer(const char* data, size_t length);

// Recibir datos del servidor (no bloqueante)
int receiveFromServer(char* buffer, size_t bufferSize);

// Verificar si esta conectado
bool isConnected(void);

// Limpiar recursos de red
void cleanupNetwork(void);

// Obtener informacion de conexion
NetworkConnection* getNetworkConnection(void);

#endif // NETWORK_H
