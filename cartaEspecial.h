#ifndef CARTAESPECIAL   
#define CARTAESPECIAL   

//libreriras necesarias
#include <string>
#include <vector>
#include "tablero.h"
#include "jugador.h"
#include <queue>
#include <fstream>
#include <sstream>

//Estructura para representar una carta especial
struct Carta{
    std::string descripcion;
    std::string tipo;
    std::string accion;
    int monto;
    int monto_casa;
    int monto_hotel;
    int casilla_destino;        
    int multiplicador;          
    int casillas_movimiento;
};

typedef struct Carta Carta;

//Estructuras para las pilas de cartas comunity
struct Cartas_Comunity{
    std::queue<Carta> cartas_comunity;
};
//Estructuras para las pilas de cartas chance
struct Cartas_Chance{
    std::queue<Carta> cartas_chance;
};

//Funciones para leer las cartas comunity desde un archivo txt
std::vector<Carta> leerCartasComunidadDesdeTxt(const std::string& nombreArchivo);
//Funciones para leer las cartas chance desde un archivo txt
std::vector<Carta> leerCartasChanceDesdeTxt(const std::string& nombreArchivo);
//Funciones para crear las pilas de cartas comunity 
Cartas_Comunity crearCartasComunity(std::vector<Carta> cartas_comunity);
//Funciones para crear las pilas de cartas chance
Cartas_Chance crearCartasChance(std::vector<Carta> cartas_chance);
//Funciones para aplicar lo que haga diga la carta
void AplicarCarta(Tablero& tablero, Jugador& jugador, const Carta& carta, std::vector<Jugador>& jugadores);
//Funciones para obtener la carta superior de la pila comunity
Carta ObtenerCartaComunity(const Cartas_Comunity& cartas_comunity);
//Funciones para obtener la carta superior de la pila chance
Carta ObtenerCartaChance(const Cartas_Chance& cartas_chance);
//Funciones para colocar la carta al final de la pila comunity
void ColocarAlFinalCartasComunity(Cartas_Comunity& cartas_comunity, Carta carta);
//Funciones para colocar la carta al final de la pila chance
void ColocarAlFinalCartasChance(Cartas_Chance& cartas_chance, Carta carta);

void mostrarCarta(const Carta& carta);
#endif