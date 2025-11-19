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
std::vector<Carta> leerCartasComunidadDesdeTxt(const std::string& nombreArchivo); // Pre: Archivo y structura Casilla -----> Post: Vector de cartas
//Funciones para leer las cartas chance desde un archivo txt
std::vector<Carta> leerCartasChanceDesdeTxt(const std::string& nombreArchivo);// Pre: Archivo y structura Casilla -----> Post: Vector de cartas
//Funciones para crear las pilas de cartas comunity 
Cartas_Comunity crearCartasComunity(std::vector<Carta> cartas_comunity);// Pre: vector de casillas y structura Cartas comunity -----> Post: struc Cartas comunity (Cola)
//Funciones para crear las pilas de cartas chance
Cartas_Chance crearCartasChance(std::vector<Carta> cartas_chance); // Pre: vector de casillas y structura Cartas chance -----> Post: struc Cartas Chance (Cola)
//Funciones para aplicar lo que haga diga la carta
void AplicarCarta(Tablero& tablero, Jugador& jugador, const Carta& carta, std::vector<Jugador>& jugadores); // Pre: Carta - jugadores - tablero  -----> Post: Se hace lo que diga la carta obtenida
//Funciones para obtener la carta superior de la pila comunity
Carta ObtenerCartaComunity(const Cartas_Comunity& cartas_comunity); // Pre: estructura cartas comunity (Cola) -----> Post: Carta comunity
//Funciones para obtener la carta superior de la pila chance
Carta ObtenerCartaChance(const Cartas_Chance& cartas_chance);// Pre: estructura cartas chance (Cola) -----> Post: Carta chance
//Funciones para colocar la carta al final de la pila comunity
void ColocarAlFinalCartasComunity(Cartas_Comunity& cartas_comunity, Carta carta);// Pre: estructura cartas comunity (Cola) y Carta-----> Post: estructura Cartas comunity con la carta al final
//Funciones para colocar la carta al final de la pila chance
void ColocarAlFinalCartasChance(Cartas_Chance& cartas_chance, Carta carta);// Pre: estructura cartas chacnce (Cola) y Carta-----> Post: estructura Cartas chance con la carta al final
//Funcion para mostrar la carta
void mostrarCarta(const Carta& carta); // Pre: Carta ----->  Post: muestra loq que dice la carta
#endif