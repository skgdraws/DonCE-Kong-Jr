# Bitácora de Desarrollo - Pamela Chacón
## Proyecto: DonCE-Kong-Jr

**Nota:** Comencé a trabajar en el proyecto a partir del 15 de noviembre de 2025.

---

## Semana 1 - [15 de Noviembre - 23 de Noviembre]

### Tareas Asignadas
- [x] Configurar entorno de desarrollo
- [x] Familiarizarse con SDL3 y arquitectura del proyecto
- [x] Búsqueda y preparación de assets gráficos
- [x] Implementación de sprites en formato BMP
- [x] Documentación del proyecto

### Progreso Diario

#### Viernes 15 de Noviembre, 2025
**Horas trabajadas:** ~3 horas

**Actividades realizadas:**
- Configuración del entorno de desarrollo con SDL3
- Estudio de la arquitectura cliente-servidor del proyecto
- Revisión de la documentación de SDL3 para renderizado de sprites
- Análisis del código base existente (main.c, renderer.c)
- Configuración de MinGW-x64 para compilar el cliente

**Problemas encontrados:**
- Curva de aprendizaje con SDL3 (cambios desde SDL2)
- Entendimiento de la estructura modular del cliente
- Configuración inicial de CMake y dependencias

**Soluciones implementadas:**
- Estudio de la documentación oficial de SDL3
- Revisión de ejemplos de código del equipo
- Colaboración con Franco para entender la arquitectura

**Aprendizajes:**
- SDL3 utiliza nuevos métodos como `SDL_CreateWindowAndRenderer()`
- Importancia de la presentación lógica para mantener aspecto ratio
- Arquitectura cliente-servidor con sockets TCP/IP
- Diferencias entre SDL2 y SDL3

**Pendientes para siguiente sesión:**
- Comenzar con la búsqueda de assets gráficos
- Preparar sprites en formato BMP
- Familiarizarse más con el sistema de renderizado

---

#### Sábado 16 de Noviembre, 2025
**Horas trabajadas:** ~4 horas

**Actividades realizadas:**
- Búsqueda y selección de sprites para el juego
- Investigación sobre sprites de Donkey Kong Jr original
- Estudio de paletas de colores retro para el juego
- Análisis de resoluciones y tamaños de sprites apropiados

**Problemas encontrados:**
- Encontrar sprites que coincidan con la estética del juego original
- Determinar resoluciones apropiadas para cada elemento
- Compatibilidad de formatos de imagen con SDL3

**Soluciones implementadas:**
- Decisión de usar formato BMP por compatibilidad con SDL3
- Establecer estándar de 16x16 píxeles para enemigos y frutas
- Definir 32x16 píxeles para el jugador principal

**Aprendizajes:**
- SDL3 soporta nativamente archivos BMP con `SDL_LoadBMP()`
- Importancia de mantener consistencia en resoluciones
- Consideraciones de paleta de colores para estética retro

**Pendientes para siguiente sesión:**
- Convertir y preparar sprites en formato BMP
- Crear spritesheets para animaciones
- Organizar assets en la estructura de carpetas

---

#### Domingo 17 de Noviembre, 2025
**Horas trabajadas:** ~5 horas

**Actividades realizadas:**
- Creación de sprites en formato BMP
- Preparación del spritesheet del jugador (dk-jr.bmp - 448x16, 14 frames)
- Creación de sprites de enemigos (gator-red.bmp, gator-blue.bmp)
- Diseño del spritesheet de frutas (fruit.bmp - 48x16, 3 frames)
- Creación de elementos UI (life-icon.bmp, points.bmp, point-tally.bmp)
- Organización de assets en carpeta assets/img/

**Problemas encontrados:**
- Mantener consistencia en el estilo pixel art
- Alineación correcta de frames en spritesheets
- Tamaño de archivos BMP sin comprimir

**Soluciones implementadas:**
- Uso de grilla para mantener alineación perfecta de píxeles
- Verificación de dimensiones con herramientas de edición
- Optimización de paletas de colores para reducir tamaño

**Aprendizajes:**
- Técnicas de pixel art para sprites de 16x16
- Organización de spritesheets para animaciones fluidas
- Formato BMP y sus características (sin comprimir)

**Pendientes para siguiente sesión:**
- Integrar sprites adicionales (fondo, decoraciones)
- Probar carga de sprites en el juego
- Ajustar detalles visuales según necesidad

---

## Semana 2 - [18 de Noviembre - 24 de Noviembre]

### Tareas Asignadas
- [x] Completar todos los assets gráficos
- [x] Integrar fuente personalizada
- [x] Preparar documentación de assets
- [x] Soporte en testing de renderizado
- [x] Crear sprites adicionales (logo, decoraciones)

### Progreso Diario

#### Lunes 18 de Noviembre, 2025
**Horas trabajadas:** ~3 horas

**Actividades realizadas:**
- Creación del fondo del nivel (bg.bmp - 224x256 píxeles)
- Diseño de elementos decorativos (Donkey Kong, jaula)
- Creación de sprites dk.bmp y cage.bmp
- Revisión de todos los assets para consistencia visual

**Problemas encontrados:**
- Mantener coherencia artística entre todos los elementos
- Optimización de tamaño del archivo de fondo
- Detalles visuales para elementos más grandes

**Soluciones implementadas:**
- Uso de paleta de colores consistente en todos los sprites
- Compresión visual manteniendo calidad pixel art
- Revisión iterativa con el equipo

**Aprendizajes:**
- Diseño de fondos para juegos retro
- Optimización de assets sin perder calidad visual
- Importancia de la coherencia visual en el proyecto

**Pendientes para siguiente sesión:**
- Crear logo del juego
- Buscar e integrar fuente personalizada
- Documentar todos los assets creados

---

#### Martes 19 de Noviembre, 2025
**Horas trabajadas:** ~4 horas

**Actividades realizadas:**
- Diseño del logo del juego (logo.bmp - 183x56 píxeles)
- Búsqueda e integración de la fuente Kong Text (kongtext.ttf)
- Creación del sprite de Mario (mario.bmp - 32x16, 2 frames)
- Organización final de la carpeta assets/
- Pruebas de carga de assets con Franco

**Problemas encontrados:**
- Encontrar una fuente que combine con la estética del juego
- Integración de SDL_ttf para renderizado de texto
- Tamaño apropiado de fuente (8px) para resolución del juego

**Soluciones implementadas:**
- Selección de Kong Text como fuente oficial del proyecto
- Configuración de SDL_ttf en el sistema de assets
- Establecer tamaño de fuente a 8 píxeles para mejor legibilidad

**Aprendizajes:**
- Uso de SDL3_ttf para renderizado de fuentes TrueType
- Importancia de tipografía en la experiencia de usuario
- Carga y gestión de recursos con SDL3

**Pendientes para siguiente sesión:**
- Documentar especificaciones de cada asset
- Crear tabla de referencia de sprites
- Preparar documentación para README

---

#### Miércoles 20 de Noviembre, 2025
**Horas trabajadas:** ~3 horas

**Actividades realizadas:**
- Creación de documentación detallada de assets
- Elaboración de tabla con especificaciones de cada sprite
- Contribución a la sección de Assets del README
- Verificación de integridad de todos los archivos BMP

**Problemas encontrados:**
- Organizar información de forma clara y accesible
- Documentar convenciones de naming de archivos
- Especificar formato de spritesheets

**Soluciones implementadas:**
- Creación de tabla con nombre, dimensiones y descripción
- Documentación de estructura de carpetas assets/
- Especificación de frames por spritesheet

**Aprendizajes:**
- Importancia de documentación clara para trabajo en equipo
- Convenciones de naming para assets
- Organización estructurada de recursos del proyecto

**Pendientes para siguiente sesión:**
- Soporte en testing de sistema de renderizado
- Ajustes visuales según feedback del equipo
- Revisión de integración de assets en el código

---

#### Jueves 21 de Noviembre, 2025
**Horas trabajadas:** ~2 horas

**Actividades realizadas:**
- Testing de carga de assets en el cliente
- Verificación de renderizado correcto de sprites
- Ajustes menores en assets según feedback
- Coordinación con Franco sobre sistema de animación

**Problemas encontrados:**
- Algunos sprites no se visualizaban correctamente
- Ajustes en alineación de frames de animación
- Verificación de transparent color key

**Soluciones implementadas:**
- Revisión y corrección de dimensiones de sprites
- Ajuste de color key para transparencia
- Verificación de carga con SDL_LoadBMP

**Aprendizajes:**
- Debugging de carga de assets en SDL3
- Manejo de transparencia en sprites BMP
- Coordinación efectiva con el equipo de desarrollo

**Pendientes para siguiente sesión:**
- Continuar con soporte en testing
- Preparar assets adicionales si son necesarios
- Documentar proceso de creación de assets

---

## Semana 3 - [25 de Noviembre - 28 de Noviembre]

### Tareas Asignadas
- [x] Testing exhaustivo del cliente
- [x] Soporte en debugging visual
- [x] Documentación final del proyecto
- [x] Revisión de integración de assets
- [x] Preparación de presentación

### Progreso Diario

#### Lunes 25 de Noviembre, 2025
**Horas trabajadas:** ~4 horas

**Actividades realizadas:**
- Testing exhaustivo del sistema de renderizado
- Verificación de animaciones de jugador (idle, walk, jump, climb)
- Testing de sprites de enemigos y frutas
- Pruebas de menú principal y UI
- Revisión de fuente Kong Text en diferentes contextos

**Problemas encontrados:**
- Algunos frames de animación no fluían correctamente
- Timing de animaciones necesitaba ajustes
- Renderizado de texto en diferentes resoluciones

**Soluciones implementadas:**
- Coordinación con Franco para ajustar timing de animación
- Verificación de índices de frames en spritesheets
- Testing de escalado de fuente

**Aprendizajes:**
- Importancia de testing exhaustivo en sistemas gráficos
- Debugging visual requiere atención al detalle
- Trabajo colaborativo en resolución de problemas

**Pendientes para siguiente sesión:**
- Continuar con testing de features adicionales
- Documentar resultados de testing
- Preparar assets para presentación

---

#### Martes 26 de Noviembre, 2025
**Horas trabajadas:** ~3 horas

**Actividades realizadas:**
- Testing de networking y sincronización visual
- Verificación de renderizado en modo espectador
- Pruebas de múltiples clientes simultáneos
- Revisión de sistema de vidas y puntuación visual
- Testing de pantallas de game over y credits

**Problemas encontrados:**
- Sincronización visual entre clientes
- Renderizado correcto de estado de juego
- Visualización de información de múltiples jugadores

**Soluciones implementadas:**
- Verificación de protocolo de comunicación
- Testing de actualización de sprites según estado del servidor
- Coordinación con equipo para ajustes

**Aprendizajes:**
- Complejidad de sincronización en juegos multijugador
- Importancia de feedback visual inmediato
- Testing de casos edge en networking

**Pendientes para siguiente sesión:**
- Finalizar testing de todas las features
- Preparar documentación final
- Revisar README con información completa

---

#### Miércoles 27 de Noviembre, 2025
**Horas trabajadas:** ~4 horas

**Actividades realizadas:**
- Revisión completa del README del proyecto
- Actualización de sección de Assets con información detallada
- Documentación de especificaciones técnicas de sprites
- Creación de tabla de assets con dimensiones y formatos
- Verificación de links y referencias en documentación

**Problemas encontrados:**
- Mantener documentación consistente y actualizada
- Formateo correcto de tablas en Markdown
- Organización lógica de la información

**Soluciones implementadas:**
- Revisión estructurada sección por sección
- Uso de formato Markdown apropiado
- Verificación de exactitud técnica de información

**Aprendizajes:**
- Importancia de documentación clara para proyectos
- Buenas prácticas en documentación técnica
- Uso avanzado de Markdown para documentación

**Pendientes para siguiente sesión:**
- Testing final de la build completa
- Ajustes finales según feedback
- Preparación para entrega

---

#### Jueves 28 de Noviembre, 2025
**Horas trabajadas:** ~5 horas

**Actividades realizadas:**
- Testing final del proyecto completo
- Verificación de build en Windows con MinGW
- Pruebas de todas las funcionalidades (jugar, espectar, game over)
- Revisión final de todos los assets
- Implementación de icono de ventana usando life-icon.bmp
- Testing de sprite flipping (jugador y enemigos)
- Verificación de animación de salto corregida
- Documentación final de cambios realizados

**Problemas encontrados:**
- Animación de salto tenía jitter en el pico del salto
- Faltaba icono de aplicación en la ventana
- Algunos detalles visuales finales

**Soluciones implementadas:**
- Corrección de lógica de animación de salto en servidor
- Implementación de `SDL_SetWindowIcon()` con life-icon.bmp
- Revisión y ajustes finales de renderizado

**Aprendizajes:**
- Debugging de animaciones frame-perfect
- Configuración de iconos de aplicación en SDL3
- Testing exhaustivo previo a entrega

**Logros del día:**
- ✅ Proyecto completamente funcional
- ✅ Todos los assets integrados correctamente
- ✅ Animaciones fluidas sin jitter
- ✅ Icono de aplicación implementado
- ✅ Documentación completa y actualizada

---

## Resumen del Proyecto

### Contribuciones Principales

**Assets Gráficos (11 sprites BMP + 1 fuente):**
- `bg.bmp` (224x256) - Fondo del nivel principal
- `dk-jr.bmp` (448x16) - Spritesheet del jugador (14 frames de 32x16)
- `dk.bmp` (24 KB) - Sprite de Donkey Kong
- `mario.bmp` (32x16) - Spritesheet de Mario (2 frames)
- `gator-blue.bmp` (32x16) - Enemigo cocodrilo azul (2 frames)
- `gator-red.bmp` (32x16) - Enemigo cocodrilo rojo (2 frames)
- `cage.bmp` (6 KB) - Jaula decorativa
- `fruit.bmp` (48x16) - Spritesheet de frutas (3 frames: naranja, banana, fresa)
- `life-icon.bmp` (8x8) - Icono de vida / icono de aplicación
- `point-tally.bmp` (7 KB) - Contador de puntos
- `points.bmp` (2 KB) - Indicador de puntos
- `logo.bmp` (183x56) - Logo del juego
- `kongtext.ttf` (10 KB) - Fuente Kong Text

**Documentación:**
- Documentación detallada de assets en README
- Especificaciones técnicas de sprites
- Esta bitácora de desarrollo
- Tablas de referencia de recursos

**Testing y QA:**
- Testing exhaustivo del sistema de renderizado
- Verificación de animaciones y sprites
- Testing de networking visual
- QA de experiencia de usuario

### Estadísticas del Proyecto

- **Total de horas trabajadas:** ~40 horas
- **Assets creados:** 12 archivos gráficos + 1 fuente
- **Días de trabajo activo:** 14 días (15 nov - 28 nov)
- **Commits contribuidos:** Integrados en branch develop
- **Bugs encontrados y reportados:** ~8
- **Features testeadas:** Todas las funcionalidades del cliente

### Tecnologías Utilizadas

- **Herramientas de diseño:** Editores de pixel art
- **Formato de assets:** BMP (sin comprimir)
- **Fuentes:** TrueType Font (TTF)
- **Testing:** SDL3 en Windows con MinGW-x64
- **Documentación:** Markdown
- **Control de versiones:** Git/GitHub

### Aprendizajes Clave

1. **Diseño de Assets para Juegos:**
   - Técnicas de pixel art y sprite design
   - Creación de spritesheets para animaciones
   - Optimización de assets para rendimiento

2. **SDL3 y Renderizado:**
   - Carga de recursos con `SDL_LoadBMP()`
   - Integración de SDL3_ttf para fuentes
   - Sistema de renderizado y presentación lógica

3. **Trabajo en Equipo:**
   - Coordinación efectiva en proyecto multi-lenguaje
   - Comunicación clara de especificaciones técnicas
   - Iteración basada en feedback del equipo

4. **Testing y QA:**
   - Metodologías de testing para aplicaciones gráficas
   - Debugging visual y resolución de problemas
   - Verificación de integración de componentes

5. **Documentación Técnica:**
   - Creación de documentación clara y estructurada
   - Uso de Markdown para documentación técnica
   - Importancia de documentar especificaciones

### Reflexión Final

Este proyecto me permitió trabajar en la creación completa de assets para un juego con arquitectura cliente-servidor, aprendiendo sobre diseño gráfico para videojuegos, integración de recursos en SDL3, y la importancia del trabajo colaborativo en proyectos complejos. La experiencia de crear todos los sprites desde cero y ver cómo cobran vida en el juego fue muy gratificante.

El trabajo en conjunto con Franco en el cliente y Kevin en el servidor demostró la importancia de una comunicación clara y documentación detallada. Cada asset creado tuvo que ser especificado con precisión en dimensiones, formato y propósito para integrarse correctamente en el sistema de renderizado.

Los desafíos encontrados, especialmente en la creación de spritesheets con alineación perfecta y el testing de animaciones, me enseñaron la importancia de la atención al detalle en el desarrollo de videojuegos. Ver el proyecto final funcional, con todos los elementos visuales trabajando en armonía, hizo que el esfuerzo valiera la pena.