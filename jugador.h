#ifndef JUGADOR_H
#define JUGADOR_H

//libreriras necesarias
#include <string>
#include <vector>

//Declaracion adelantada de estructuras para no causar errores de dependencia circular
struct Tablero;
struct Casilla;

//Definicion estructura Jugador
struct Jugador{
    std::string nombre;
    float saldo;
    int posicion;
    bool enCarcel;
    int turnosEnCarcel;
    bool tiene_salir_carcel; 
    int multiplicador_alquiler;
    bool EnBancarrota;
    bool DadoPar;
};

//Funcion para crear un jugador
Jugador crearJugador(std::string nombre);
//Funcion para mostrar la informacion del jugador
void mostrarInfoJugador(const Tablero& tablero, const Jugador& jugador);
//Ffuncion para agregar dinero al jugador
void AgregarDinero(Jugador& jugador, float monto);
//Funcion para retirar dinero al jugador
void RetirarDinero( Jugador& jugador, float monto);
//Funcion para comprar una propiedad
void ComprarPropiedad(Jugador& jugador,  Casilla& propiedad);
//Funcion para vender una propiedad
void VenderPropiedad(Jugador& jugador, Casilla& propiedad);


#endif