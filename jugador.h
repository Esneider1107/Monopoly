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
Jugador crearJugador(std::string nombre); // Pre: estructura Jugador y un nombre -----> Post: Jugador
//Funcion para mostrar la informacion del jugador
void mostrarInfoJugador(const Tablero& tablero, const Jugador& jugador); // Pre: Tablero y un jugador -----> Post: Muestra el saldo, la posicion ylas propieaddes del jugador
//Ffuncion para agregar dinero al jugador
void AgregarDinero(Jugador& jugador, float monto); // Pre: Un jugador y el dinero a sumar -----> Post: Saldo actualizado (Tendra mas que antes)
//Funcion para retirar dinero al jugador
void RetirarDinero( Jugador& jugador, float monto);//  Pre: Un jugador y el dinero a restar -----> Post: saldo acturalizado (Tendra menos que antes)
//Funcion para comprar una propiedad
void ComprarPropiedad(Jugador& jugador,  Casilla& propiedad); //  Pre: Un jugador y la casilla de la propiedad -----> Post: La propiedad sera ahora del jugador y se le restara del saldo
//Funcion para comprar una casa
void ComprarCasa(Jugador& jugador, Casilla& propiedad);//  Pre: Un jugador y la casilla de la propiedad para la casa -----> Post: La propiedad subira de nivel y se le restara del saldo
//Funcion para comprar un hotel
void ComprarHotel(Jugador& jugador, Casilla& propiedad); //  Pre: Un jugador y la casilla de la propiedad para la hotel -----> Post: La propiedad subira de nivel y se le restara del saldo
//Funcion para vender una propiedad
bool VenderPropiedad(Jugador& jugador, Casilla& propiedad);//  Pre: Un jugador y la casilla de la propiedad a vender -----> Post: La propiedad ya no sera del jugador y se le sumara al saldo
//Funcion para vender casa
bool VenderCasa(Jugador& jugador, Casilla& propiedad); //Pre: Un jugador y la casilla de la propiedad con la casa a vender  -----> Post: La propeidad bajara de nivel y se le subira al saldo - true si vende / false si no
//Funcion para vender hotel
bool VenderHotel(Jugador& jugador, Casilla& propiedad); //Pre: Un jugador y la casilla de la propiedad con el hotel a vender -----> Post: La propiedad bajara de nivel y se le subira al saldo - true si vende / false si no



#endif