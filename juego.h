#ifndef HISTORIAL_H
#define HISTORIAL_H

#include <string>
#include <vector>
#include "tablero.h"
#include "jugador.h"
#include "cartaEspecial.h"
#include <queue>
#include <stack>


struct Historial{
    std::vector<Jugador> jugadores;
    Tablero tablero;
    Cartas_Chance cartas_chance;
    Cartas_Comunity cartas_comunity;
    int turno;
};

struct Juego{ 
    std::vector<Jugador> jugadores;
    Tablero tablero;
    Cartas_Chance cartas_chance;
    Cartas_Comunity cartas_comunity;
    int turno;
    std::stack<Historial> historial;
    bool juego_activo;
};

typedef struct Juego Juego;
typedef struct Historial Historial;

Juego crearJuego(const std::vector<Jugador>& jugadores, const Tablero& tablero, const Cartas_Chance& cartas_chance, const Cartas_Comunity& cartas_comunity);


std::pair<int, int> lanzardados(Juego& juego);
void moverJugador(Juego& juego, int indiceJugador, std::pair<int, int> pasos);
void pasarturno(Juego& juego);

void aplicarCasilla(Juego& juego, int posicion, int indiceJugador);
void cobraralquiler(Juego& juego, int indiceJugadorPropietario, int indiceJugadorQPaga, int posicion);

void sacarCartaChance(Juego& juego, int indiceJugador);
void sacarCartaComunity(Juego& juego, int indiceJugador);

void guardarEstadoHistorial(Juego& juego);

void turnoActual(Juego& juego);

void DeshacerUltimaAccion(Juego& juego);


#endif