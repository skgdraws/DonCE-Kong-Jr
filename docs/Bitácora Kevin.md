# Bitácora de Desarrollo - Kevin
## Proyecto: DonCE-Kong-Jr

---

## Fase 1 - Implementación de Sockets y Comunicación

### Tareas Asignadas
- [X] Creación de Sockets en Java
- [X] Implementación del sistema de comunicación cliente-servidor
- [X] Desarrollo de clases de lógica del juego
- [X] Creación de subclases para enemigos y coleccionables
- [X] Mejoras en la comunicación con clientes

### Progreso Detallado

#### Commit: c25dcaf - [ADD] Sockets java
**Horas trabajadas:** 8 horas

**Actividades realizadas:**
- Creación de la clase `Server.java` para gestionar conexiones TCP
- Implementación de la clase `Client.java` para conexiones de clientes
- Desarrollo de `ClientListener.java` para escuchar mensajes de clientes
- Creación de `Listener.java` interfaz para escuchadores
- Implementación de `Sender.java` para envío de mensajes

**Problemas encontrados:**
- Manejo de múltiples conexiones simultáneas
- Sincronización de threads en servidor

**Soluciones implementadas:**
- Uso de ServerSocket para aceptar conexiones en puerto 2121
- Implementación de threads separados para cada cliente
- Uso de BufferedReader/PrintWriter para comunicación

**Aprendizajes:**
- Arquitectura cliente-servidor en Java
- Manejo de excepciones de I/O
- Patrones de comunicación asincrónica

**Pendientes para siguiente sesión:**
- Integración con lógica del juego
- Pruebas de estabilidad bajo carga

---

#### Commit: 6956555 - [ADD] Clases para lógica del juego
**Horas trabajadas:** 10 horas

**Actividades realizadas:**
- Creación de la clase `Entity.java` como entidad base
- Implementación de `Player.java` con mecánicas de movimiento y gravedad
- Desarrollo de `Platform.java` para plataformas del juego
- Creación de `Vine.java` para las lianas del juego
- Implementación de `Logic.java` como gestor principal del juego
- Desarrollo de colisiones y física del juego

**Problemas encontrados:**
- Complejidad en el manejo de colisiones
- Gravedad y movimiento de entidades
- Detección de intersecciones

**Soluciones implementadas:**
- Uso de rectangulos (Rectangle) para detección de colisiones
- Sistema de velocidad (vx, vy) para movimiento
- Método de colisiones comprobando todas las entidades

**Aprendizajes:**
- Estructuras de datos para entidades del juego
- Física básica en 2D
- Patrón de componentes para entidades

**Pendientes para siguiente sesión:**
- Refinamiento de detección de colisiones
- Balanceo de mecánicas

---

#### Commit: ee27cdb - [ADD] Subclases para enemigos y coleccionables
**Horas trabajadas:** 8 horas

**Actividades realizadas:**
- Creación de `Enemy.java` como clase base para enemigos
- Implementación de `EnemyFactory.java` (patrón Factory)
- Desarrollo de `RedEnemy.java` y `RedFactory.java`
- Creación de `BlueEnemy.java` y `BlueFactory.java`
- Implementación de `Collectible.java` para frutas
- Desarrollo de `CollectibleFactory.java` y subclases:
  - `Banana.java` y `BananaFactory.java`
  - `Orange.java` y `OrangeFactory.java`
  - `Strawberry.java` y `StrawberryFactory.java`

**Problemas encontrados:**
- Diseño del patrón Factory
- Diferenciación de tipos de enemigos

**Soluciones implementadas:**
- Uso del patrón Factory para crear instancias
- Herencia de clases para enemigos y frutas
- Atributos específicos para cada tipo (valor de puntos, velocidad)

**Aprendizajes:**
- Patrón Factory en Java
- Herencia y polimorfismo
- Gestión de múltiples tipos de entidades

**Pendientes para siguiente sesión:**
- Comportamiento específico de enemigos
- Animaciones y efectos

---

#### Commit: a6caa5e - [UPDATE] Cambios a clases del juego
**Horas trabajadas:** 6 horas

**Actividades realizadas:**
- Refinamiento de clases de entidades
- Mejora de métodos de colisión
- Actualización de atributos públicos
- Optimización de lógica de movimiento

**Problemas encontrados:**
- Inconsistencias en atributos
- Accesibilidad de variables

**Soluciones implementadas:**
- Estandarización de atributos públicos para acceso directo
- Mejora de métodos de actualización
- Refinamiento de lógica de física

**Aprendizajes:**
- Diseño de APIs públicas en Java
- Encapsulación vs acceso directo

**Pendientes para siguiente sesión:**
- Refactorización de acceso a variables

---

#### Commit: e26ab1a - [UPDATE] Cambios a lógica del juego
**Horas trabajadas:** 7 horas

**Actividades realizadas:**
- Implementación de gestión de múltiples instancias de juego
- Creación de `App.java` como clase principal
- Desarrollo de sistema de comandos CLI
- Mejora de manejo de colisiones
- Integración con sistema de sockets

**Problemas encontrados:**
- Gestión de dos juegos simultáneos
- Sincronización de estados

**Soluciones implementadas:**
- Clase App con dos instancias Logic independientes
- Sistema de comandos para debugging
- Métodos separados para cada juego

**Aprendizajes:**
- Patrón singleton para servidores
- Gestión de estado compartido
- Creación de interfaces de usuario CLI

**Pendientes para siguiente sesión:**
- Pruebas de sincronización
- Handling de desconexiones

---

#### Commit: 9231e25 - [UPDATE] Envío de datos a clientes
**Horas trabajadas:** 8 horas

**Actividades realizadas:**
- Implementación de `GameClientHandler.java` para manejar clientes individuales
- Desarrollo de serialización de estado del juego
- Creación de protocolo de comunicación
- Envío de actualizaciones de juego a clientes

**Problemas encontrados:**
- Serialización de objetos complejos
- Latencia de comunicación
- Sincronización de estado

**Soluciones implementadas:**
- Conversión a strings para serialización simple
- Updates periódicos del estado
- Buffers para mensajes

**Aprendizajes:**
- Protocolos de comunicación en juegos
- Serialización de datos
- Manejo de buffers en red

**Pendientes para siguiente sesión:**
- Compresión de datos
- Optimización de ancho de banda

---

#### Commit: 530f322 - [UPDATE] Cambios para comunicación con clientes
**Horas trabajadas:** 6 horas

**Actividades realizadas:**
- Refinamiento del sistema de comunicación
- Mejora de protocolos de mensajes
- Optimización de envío de datos
- Debugging de problemas de conexión

**Problemas encontrados:**
- Pérdida de conexión ocasional
- Desincronización entre cliente-servidor

**Soluciones implementadas:**
- Sistema de heartbeat para verificar conexión
- Resincronización de estado
- Mejor manejo de excepciones

**Aprendizajes:**
- Robustez en comunicación de red
- Detección de fallos
- Recuperación de errores

**Pendientes para siguiente sesión:**
- Testing exhaustivo
- Optimización de performance

---

### Mejoras Recientes (Noviembre 2025)

#### Actividad: Actualización de Java 21
**Horas trabajadas:** 1 hora

**Actividades realizadas:**
- Actualización de configuración de IntelliJ a Java 21 LTS
- Modificación de archivo `.idea/misc.xml`
- Verificación de compatibilidad de código

**Problemas encontrados:**
- Proyecto inicialmente en Java 18

**Soluciones implementadas:**
- Actualización de languageLevel a JDK_21
- Actualización de project-jdk-name a 21

**Aprendizajes:**
- Compatibilidad hacia atrás de Java 21
- Actualización de configuración del IDE

---

#### Actividad: Mejora en Recolección de Frutas
**Horas trabajadas:** 2 horas

**Actividades realizadas:**
- Implementación de eliminación de frutas recolectadas
- Refactorización del loop de colisiones de coleccionables
- Cambio de parámetros de deletion

**Problemas encontrados:**
- Frutas no se eliminaban después de recolección
- Parámetros inconsistentes entre creación y eliminación

**Soluciones implementadas:**
- Cambio a loop con índice inverso para eliminación segura
- Método `deleteCollectible(int vineIdx, double y)` en Logic
- Método `handleDeleteFruit()` en App para comandos CLI
- Uso de mismos parámetros (vineIdx, y) para creación y eliminación

**Aprendizajes:**
- Iteración segura al eliminar de ArrayLists
- Consistencia de APIs
- Facilidad de uso en interfaces CLI

**Pendientes para siguiente sesión:**
- Testing de eliminación de frutas
- Validación de parámetros

---

## Resumen General del Proyecto

### Tecnologías y Librerías Utilizadas
- **Sockets de Java** - Comunicación cliente-servidor
- **BufferedReader/PrintWriter** - Manejo de I/O
- **ArrayList** - Gestión de colecciones
- **Rectangle (AWT)** - Detección de colisiones

### Desafíos Principales
1. **Comunicación en red confiable** - Sincronización entre cliente-servidor
2. **Gestión de múltiples instancias** - Dos juegos simultáneos
3. **Física y colisiones** - Detección precisa de intersecciones
4. **Patrón Factory** - Crear diferentes tipos de entidades dinámicamente

### Logros Destacados
1. **Sistema de sockets funcional** - Comunicación TCP establecida
2. **Lógica de juego completa** - Movimiento, colisiones, puntuación
3. **Patrón Factory implementado** - 6 subclases de enemigos y frutas
4. **Interfaz CLI para debugging** - Comandos para crear y eliminar entidades

### Conclusiones y Reflexiones
- La arquitectura cliente-servidor proporciona una base sólida para el juego multijugador
- El patrón Factory se ha demostrado muy útil para extensibilidad
- La física del juego es relativamente simple pero efectiva para Donkey Kong Jr
- La comunicación de red requiere manejo robusto de excepciones y desconexiones
- Java 21 mantiene excelente compatibilidad con el código existente

---

## Notas Adicionales
- Se han mantenido commits pequeños y descriptivos con prefijos [ADD], [UPDATE], [FIX]
- La rama kevin-develop se ha mantenido sincronizada con cambios progresivos
- El proyecto está bien estructurado en paquetes: `game`, `sockets`
- Se recomienda implementar logging más robusto para debugging futuro
