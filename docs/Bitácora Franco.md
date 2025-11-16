# Bitácora de Desarrollo - Franco
## Proyecto: DonCE-Kong-Jr

---

## Semana 1 - [15 de Noviembre - En curso]

### Tareas Asignadas
- [x] Configurar entorno de desarrollo con SDL3
- [x] Crear ventana básica del juego
- [x] Configurar CMake para MinGW-x64
- [ ] Implementar renderizado de sprites
- [ ] Diseñar arquitectura del cliente

### Progreso Diario

#### Viernes 15 de Noviembre, 2025
**Horas trabajadas:** ~3 horas

**Actividades realizadas:**
- Creación de la ventana del juego usando SDL3
- Inicialización del renderer con presentación lógica de 512x448 píxeles
- Implementación del game loop principal con manejo de eventos
- Configuración de límite de ~60 FPS con SDL_Delay(16)
- Corrección de configuración de CMake para trabajar con MinGW-x64
- Limpieza de archivos de build antiguos (configuraciones de Visual Studio)
- Actualización de tareas en CMakeLists.txt para compilador GCC

**Problemas encontrados:**
- CMake estaba configurado para Visual Studio en lugar de MinGW
- Archivos de build .vcxproj y configuraciones de MSVC causaban conflictos
- Múltiples archivos binarios antiguos (Debug/main.exe, .pdb, .dll) generaban confusión

**Soluciones implementadas:**
- Reconfiguración completa de CMake para usar MinGW Makefiles
- Eliminación de 70+ archivos relacionados con configuración de Visual Studio
- Actualización de compiler flags en CMakeLists.txt
- Generación exitosa de main.exe con MinGW-x64

**Aprendizajes:**
- SDL3 utiliza `SDL_CreateWindowAndRenderer()` para inicializar ambos componentes simultáneamente
- `SDL_SetRenderLogicalPresentation()` permite mantener aspecto ratio correcto con letterboxing
- CMake puede generar diferentes tipos de build systems (Visual Studio, MinGW, etc.)
- Importancia de limpiar archivos de build al cambiar de toolchain

**Pendientes para siguiente sesión:**
- Cargar y renderizar sprites/imágenes
- Implementar sistema de assets (imágenes, fuentes, sonidos)
- Crear estructura básica del personaje jugador
- Investigar manejo de input con SDL3

---

#### [Día/Fecha]
**Horas trabajadas:** X horas

**Actividades realizadas:**
- 

**Problemas encontrados:**
- 

**Soluciones implementadas:**
- 

**Aprendizajes:**
- 

**Pendientes para siguiente sesión:**
- 

---

## Semana 2 - [Fecha Inicio - Fecha Fin]

### Tareas Asignadas
- [ ] Tarea 1
- [ ] Tarea 2

### Progreso Diario

#### [Día/Fecha]
**Horas trabajadas:** X horas

**Actividades realizadas:**
- 

**Problemas encontrados:**
- 

**Soluciones implementadas:**
- 

**Aprendizajes:**
- 

**Pendientes para siguiente sesión:**
- 

---

## Resumen General del Proyecto

### Tecnologías y Librerías Utilizadas
- 
- 
- 

### Desafíos Principales
1. 
2. 
3. 

### Logros Destacados
1. 
2. 
3. 

### Conclusiones y Reflexiones
- 

---

## Notas Adicionales
- 
