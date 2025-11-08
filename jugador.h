#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include "tablero.h"

struct Jugador{
    std::string nombre;
    float saldo;
    int posicion;
    bool enCarcel;
    int turnosEnCarcel;
    bool tiene_salir_carcel; 
    int multiplicador_alquiler;
};

Jugador crearJugador(std::string nombre);

void mostrarInfoJugador(const Tablero& tablero, const Jugador& jugador);

void AgregarDinero(Jugador& jugador, float monto);

void RetirarDinero( Jugador& jugador, float monto);

void ComprarPropiedad(Jugador& jugador,  Casilla& propiedad);

void VenderPropiedad(Jugador& jugador, Casilla& propiedad);


#endif