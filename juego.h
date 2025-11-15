#ifndef HISTORIAL_H
#define HISTORIAL_H
//libreriras necesarias
#include <string>
#include <vector>
#include "tablero.h"
#include "jugador.h"
#include "cartaEspecial.h"
#include <queue>
#include <stack>

//Definicion estructura Historial
struct Historial{
    std::vector<Jugador> jugadores;
    Tablero tablero;
    Cartas_Chance cartas_chance;
    Cartas_Comunity cartas_comunity;
    int turno;
};
//Definicion estructura Juego
struct Juego{ 
    std::vector<Jugador> jugadores;
    Tablero tablero;
    Cartas_Chance cartas_chance;
    Cartas_Comunity cartas_comunity;
    int turno;
    std::stack<Historial> historial;
    int ultimoValorDados;
    bool juego_activo;
    bool turno_en_progreso;  
    int tiradas_consecutivas;
};

typedef struct Juego Juego;
typedef struct Historial Historial;

//Funcion para crear el juego
Juego crearJuego(const std::vector<Jugador>& jugadores, const Tablero& tablero, const Cartas_Chance& cartas_chance, const Cartas_Comunity& cartas_comunity);

//Funciones para lanzar dados
std::pair<int, int> lanzardados();
//Funciones para mover al jugador
void moverJugador(Juego& juego, int indiceJugador, std::pair<int, int> pasos);
//Funcion para pasar el turno
void pasarturno(Juego& juego);
//Funcion para aplicar la casilla en la que cayó el jugador
void aplicarCasilla(Juego& juego, int posicion, int indiceJugador);
//Funcion para cobrar alquiler
void cobrarAlquiler(Juego& juego, int indiceJugadorPropietario, int indiceJugadorQPaga, int pos);
//Funcion para sacar carta chance
void sacarCartaChance(Juego& juego, int indiceJugador);
//Funcion para sacar carta comunity
void sacarCartaComunity(Juego& juego, int indiceJugador);
//Funcion para guardar el estado actual del juego en el historial
void guardarEstadoHistorial(Juego& juego);
//Funcion para deshacer la ultima accion
void DeshacerUltimaAccion(Juego& juego);
// Funcion para una tirada (jugada)
void ejecutarTirada(Juego& juego);
//Funcion para mostrar el historial
void mostrarHistorial(std::stack<Historial> historial);
//Funcion para comprar casa con usuario
void comprar_casa(Juego& juego, int indiceJugador);
//Funcion para comprar casa con usuario
void comprar_hotel(Juego& juego, int indiceJugador);


#endif