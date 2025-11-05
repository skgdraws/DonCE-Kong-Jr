<div align="center">

# 🎮 DonCE-Kong-Jr

<img src="https://img.shields.io/badge/Language-C%20%7C%20Java-blue.svg" alt="Language">
<img src="https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-lightgrey.svg" alt="Platform">
<img src="https://img.shields.io/badge/Architecture-Client--Server-orange.svg" alt="Architecture">
<img src="https://img.shields.io/badge/License-MIT-green.svg" alt="License">

**Un juego multijugador inspirado en el clásico Donkey Kong Jr. con arquitectura híbrida C/Java**

[Características](#-características) •
[Arquitectura](#-arquitectura) •
[Instalación](#-instalación) •
[Uso](#-uso) •
[Documentación](#-documentación)

</div>

---

## 📖 Descripción

DonCE-Kong-Jr es un juego estilo Donkey Kong Jr. con arquitectura cliente-servidor híbrida. El servidor está implementado en **Java** para aprovechar su robustez en aplicaciones de red, mientras que el cliente y el manager están desarrollados en **C** para un control más directo del hardware y rendimiento gráfico. El proyecto demuestra comunicación entre procesos, manejo de sockets, y arquitectura de sistemas distribuidos multi-lenguaje.

## ✨ Características

- 🎯 **Arquitectura Cliente-Servidor**: Comunicación eficiente mediante sockets
- 👥 **Multijugador**: Soporte para múltiples clientes simultáneos
- 🎨 **Interfaz Gráfica**: Renderizado de gráficos utilizando assets personalizados
- 🔊 **Sistema de Sonido**: Efectos de sonido y música de fondo
- 📊 **Sistema de Gestión**: Manager para controlar el flujo del juego
- 🏆 **Sistema de Puntuación**: Seguimiento de puntajes y rankings

## 🏗️ Arquitectura

El proyecto está dividido en tres componentes principales:

```
DonCE-Kong-Jr/
│
├── src/
│   ├── client/          # Cliente del juego (C)
│   │   └── main.c       # Interfaz gráfica y controles
│   │
│   ├── server/          # Servidor del juego (Java)
│   │   └── main.java    # Lógica del servidor
│   │
│   └── manager/         # Gestor del sistema (C)
│       └── main.c       # Coordinador de sesiones
│
├── assets/
│   ├── img/            # Sprites y recursos gráficos
│   ├── sound/          # Efectos de sonido y música
│   └── font/           # Fuentes tipográficas
│
└── docs/               # Documentación del proyecto
    └── especificaciones.pdf
```

### Componentes

1. **Cliente (C)**: 
   - Maneja la interfaz de usuario y la interacción del jugador
   - Renderizado gráfico optimizado
   - Control directo de entrada/salida

2. **Servidor (Java)**: 
   - Gestiona la lógica del juego y estado global
   - Manejo robusto de conexiones concurrentes
   - Comunicación entre múltiples clientes
   - Sistema de sincronización de juego

3. **Manager (C)**: 
   - Coordina el servidor y gestiona las sesiones de juego
   - Monitoreo de recursos del sistema
   - Administración de partidas activas

## 🚀 Instalación

### Prerrequisitos

**Para los componentes en C (Cliente y Manager):**
- Compilador GCC
- Make
- Bibliotecas de desarrollo (SDL2, pthread, etc.)

**Para el componente en Java (Servidor):**
- JDK 11 o superior
- Maven o Gradle (opcional, para gestión de dependencias)

### Linux

```bash
# Clonar el repositorio
git clone https://github.com/skgdraws/DonCE-Kong-Jr.git
cd DonCE-Kong-Jr

# Compilar componentes en C
make client
make manager

# Compilar servidor Java
cd src/server
javac main.java
# O con Maven/Gradle si está configurado
# mvn clean package
```

### Windows

```powershell
# Clonar el repositorio
git clone https://github.com/skgdraws/DonCE-Kong-Jr.git
cd DonCE-Kong-Jr

# Compilar componentes en C usando MinGW
gcc -o client.exe src/client/main.c
gcc -o manager.exe src/manager/main.c

# Compilar servidor Java
cd src/server
javac main.java
```

## 🎮 Uso

### Iniciar el Servidor (Java)

```bash
cd src/server
java main [puerto]
```

### Iniciar el Manager

```bash
./manager [opciones]
```

### Iniciar el Cliente

```bash
./client [servidor] [puerto]
```

### Ejemplo de Sesión Completa

```bash
# Terminal 1 - Iniciar servidor (Java)
cd src/server
java main 8080

# Terminal 2 - Iniciar manager (C)
./manager

# Terminal 3 - Iniciar cliente 1 (C)
./client localhost 8080

# Terminal 4 - Iniciar cliente 2 (C)
./client localhost 8080
```

## 🎯 Controles del Juego

- **←/→**: Mover izquierda/derecha
- **↑**: Subir
- **↓**: Bajar
- **Espacio**: Saltar
- **ESC**: Pausar/Menú

## 📚 Documentación

Para más detalles sobre el diseño y especificaciones del proyecto, consulta:

- [Especificaciones del Proyecto](docs/especificaciones.pdf)

## 🛠️ Desarrollo

### Estructura de Comunicación

El proyecto utiliza una arquitectura híbrida:
- **Sockets TCP/IP** para comunicación cliente-servidor
- **Protocolo personalizado** para mensajes del juego
- **Java NIO** en el servidor para manejo eficiente de conexiones
- **Multithreading** para manejar múltiples conexiones concurrentes
- **IPC (Inter-Process Communication)** entre manager y servidor

### Compilación en Modo Debug

```bash
# Componentes C
make debug

# Servidor Java
javac -g main.java
```

### Limpieza

```bash
# Limpiar componentes C
make clean

# Limpiar archivos Java
cd src/server
rm *.class
```

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor:

1. Fork el proyecto
2. Crea una rama para tu feature (`git checkout -b feature/AmazingFeature`)
3. Commit tus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abre un Pull Request

## 📝 Licencia

Este proyecto fue desarrollado con fines educativos.

## 👥 Autores

- **Pamela Chacón** - [@PamelaChB](https://github.com/pamelachb)
- **Franco Sagot** [@SKGDraws](https://github.com/skgdraws)
- **Kevin Ruiz** - [@Kevrr](https://github.com/kevrr)


## 🙏 Agradecimientos

- Inspirado en el clásico Donkey Kong Jr. de Nintendo
- Desarrollado como proyecto académico

---

<div align="center">
Made with ❤️ for learning purposes
</div>