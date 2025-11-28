#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Estructura que contiene informacion de la conexion de red
 */
typedef struct {
    int sockfd;                 ///< Descriptor del socket
    bool connected;             ///< Estado de conexion
    char serverAddress[256];    ///< Direccion IP del servidor
    int serverPort;             ///< Puerto del servidor
} NetworkConnection;

/**
 * @brief Inicializa el sistema de red (Winsock en Windows)
 * @return true si la inicializacion fue exitosa, false en caso contrario
 */
bool initNetwork(void);

/**
 * @brief Conecta al servidor Java via TCP
 * @param address Direccion IP del servidor (ej: "127.0.0.1")
 * @param port Puerto del servidor
 * @return true si la conexion fue exitosa, false en caso contrario
 */
bool connectToServer(const char* address, int port);

/**
 * @brief Cierra la conexion con el servidor
 */
void disconnectFromServer(void);

/**
 * @brief Envia datos al servidor
 * @param data Puntero a los datos a enviar
 * @param length Longitud de los datos en bytes
 * @return true si el envio fue exitoso, false en caso contrario
 */
bool sendToServer(const char* data, size_t length);

/**
 * @brief Envia un comando al servidor en formato Java UTF
 * @param command Comando de texto a enviar (sera envuelto en formato UTF con prefijo de longitud)
 * @return true si el envio fue exitoso, false en caso contrario
 */
bool sendCommandToServer(const char* command);

/**
 * @brief Recibe datos del servidor (operacion no bloqueante)
 * @param buffer Buffer donde almacenar los datos recibidos
 * @param bufferSize Tamaño del buffer
 * @return Numero de bytes recibidos, 0 si no hay datos, -1 en caso de error
 */
int receiveFromServer(char* buffer, size_t bufferSize);

/**
 * @brief Verifica si hay una conexion activa con el servidor
 * @return true si esta conectado, false en caso contrario
 */
bool isConnected(void);

/**
 * @brief Libera recursos de red y limpia el sistema
 */
void cleanupNetwork(void);

/**
 * @brief Obtiene la informacion de la conexion actual
 * @return Puntero a la estructura de conexion
 */
NetworkConnection* getNetworkConnection(void);

#endif // NETWORK_H
