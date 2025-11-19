# Monopoly en C++ - Proyecto Estructuras de Datos

**Integrantes:**  
Esneider Josue Veliz Guerrero  
Samuel Rodriguez Solarte  

**Profesor:**  
Gerardo Mauricio Sarria Montemiranda  

**Pontificia Universidad Javeriana Cali**

***Linea de comandos*** 
 - Jugar     -> Tirar dados y avanzar
 -  Info      -> Consultar su informacion
 -  Tablero   -> Ver el estado del tablero
 -  Deshacer  -> Revertir la ultima accion
 -  ComprarCasa  -> Comprar una casa en una propiedad
 -  ComprarHotel -> Comprar un hotel en una propiedad
 -  Hipotecar   -> Hipotecar una propiedad
 -  Deshipotecar-> Deshipotecar una propiedad


## Descripción general

Implementación completa y fiel al Monopoly clásico desarrollado en C++ como proyecto final de la asignatura **Estructuras de Datos**.  
El juego soporta múltiples jugadores, todas las reglas oficiales (monopolios, construcción pareja, hipotecas, cartas de Suerte y Carta de Comunidad, servicios públicos, estaciones, cárcel, bancarrota, etc.) y cuenta con un sistema completo de **deshacer movimientos**.

## Arquitectura del programa

El proyecto está dividido en cinco archivos principales claramente separados:

| Archivo          | Responsabilidad |
|------------------|--------------------|
| `main.cpp`       | Punto de entrada, menú interactivo por consola y bucle principal del juego |
| `juego.h / juego.cpp`   | Cerebro del juego: control de turnos, dados, historial (undo), lógica central |
| `tablero.h / tablero.cpp` | Representación del tablero y todas las casillas |
| `jugador.h / jugador.cpp` | Estructura y acciones de los jugadores (comprar, construir, hipotecar, etc.) |
| `cartaespecial.h / cartaespecial.cpp` | Gestión de los mazos de Suerte y Caja de Comunidad |

## Características principales

### 1. Tablero y casillas
- Cada casilla → estructura `Casilla` con todos los datos necesarios (precio, alquileres, color, etc.).
- El tablero se almacena en un `std::map<int, Casilla>` con claves del **1 al 40** (acceso directo O(1) y código más legible).
- **Todas las casillas se cargan desde un archivo TXT** (`casillas.txt`) → fácil modificación de precios, colores o alquileres sin recompilar.

### 2. Jugadores
- Saldo en `float` (para el 10 % de interés al deshipotecar).
- Posición, estado de cárcel, carta “Salir gratis”, multiplicadores temporales de alquiler, bandera de bancarrota, etc.
- Métodos completos para:
  - Comprar propiedades
  - Construir casas/hoteles (con regla de construcción pareja)
  - Vender casas/hoteles
  - Hipotecar/deshipotecar
  - Pagar alquileres (con forzamiento automático de ventas/hipotecas si no alcanza el dinero)

### 3. Cartas de Suerte y Cartas de Comunidad
- Estructura genérica `Carta` con campos que permiten definir cualquier efecto.
- **32 cartas cargadas desde archivos de texto** (`Cartas_Chance.txt` y `Cartas_comunity.txt`).
- Se usan `std::queue<Carta>` para simular mazos físicos (la carta sacada vuelve al fondo, excepto “Salir de la cárcel gratis”).
- Una única función `AplicarCarta()` interpreta más de **12 tipos de acciones diferentes** sin código hardcodeado por carta:
  - Mover a GO
  - Ir a casilla concreta (cobrando 200 si se pasa por GO)
  - Avanzar/retroceder N casillas
  - Ir a la estación/servicio más cercano
  - Reparaciones por casas/hoteles
  - Cobrar/pagar a otros jugadores
  - Salir de la cárcel gratis, etc.

### 4. Motor del juego (`TAD Juego`)
- Contiene jugadores, tablero, mazos, turno actual y una **pila (stack) con snapshots completos del estado** → deshacer ilimitado.
- Función principal `ejecutarTirada()` que sigue fielmente el flujo oficial:
  1. Guardar estado (para undo)
  2. Manejo de cárcel
  3. Lanzar dados
  4. Detectar 3 dobles seguidos → cárcel
  5. Mover y cobrar 200 al pasar por GO
  6. Aplicar efecto de la casilla
  7. Aplicar efectos encadenados de cartas
  8. Repetir si sacó dobles

### 5. Cálculo de alquileres (parte más compleja)
- Propiedades: alquiler según nivel de construcción + duplicado automático si hay monopolio sin casas.
- Estaciones: 25 → 50 → 100 → 200 según cantidad poseída.
- Servicios públicos: 4× dados (uno) o 10× dados (ambos). Respeta multiplicador ×10 de cartas.
- Si el jugador no puede pagar → hipoteca/venta automática respetando reglas de construcción pareja hasta pagar o bancarrota.

### 6. Menú interactivo (main.cpp)
Opciones disponibles en cualquier momento:
- Tirar dados (jugar turno)
- Ver información detallada del jugador actual
- Ver tablero completo
- **Deshacer última acción completa** (incluso movimientos con cartas)
- Construir casas/hoteles
- Hipotecar/deshipotecar propiedades

Al final de cada turno se verifica bancarrota y se declara ganador cuando solo queda un jugador.

## Principios de diseño aplicados
- **Separación clara de responsabilidades**.
- **Todo configurable externamente** (casillas y cartas en archivos de texto).
- Máxima fidelidad a las **reglas oficiales del Monopoly clásico**.
- Sistema de **deshacer completo** basado en copias profundas del estado.
- Código robusto con manejo de errores en lectura de archivos y entrada de usuario.

## Archivos de configuración incluidos
- `casillas.txt` → definición de las 40 casillas
- `Cartas_Chance.txt` → 16 cartas de Suerte
- `Cartas_comunity.txt` → 16 cartas de cartas de Comunidad

