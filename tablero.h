#ifndef TABLERO_H
#define TABLERO_H

//libreriras necesarias
#include "jugador.h" 
#include <string>
#include <vector>
#include <map>

//Definicion de estructura Casilla
struct Casilla {
    std::string nombre;
    std::string funcion;  
    int precio;
    std::map<int, int> alquiler;
    std::string propietario;
    std::string color;
    int nivel_propiedad;
    int precio_casa;
    int precio_hotel;
    Casilla() : precio(0), nivel_propiedad(0), precio_casa(0), precio_hotel(0){}
};

//Defincion estructura Tablero
struct Tablero {
    std::map<int, Casilla> casillas;
};

typedef struct Tablero Tablero;

typedef struct Casilla Casilla;

//Funcion para recibir las casillas desde un archivo txt
std::vector<Casilla> leerCasillasDesdeTxt(const std::string& nombreArchivo); // Pre: Archivo con las casillas y estructura de Casilla -----> Post: vector de casillas
//Funcion para crear el tablero con las casillas leidas
Tablero crearTablero(std::vector<Casilla> casillas); // Pre: vector de casillas y estructura de tablero (mapa) -----> Post: vector de casillas
//Funciones para mostrar el tablero y las casillas
void mostrarTablero(const Tablero& t, std::vector<Jugador>& jugadores); // Pre: Tablero y jugadores -----> Post: Muestra todas las casillas, con su nombre, tipo, accion, propieatrio y si hay un jugador en esa posicion 
//funcion para mostrar una casilla y decir si lo compra
void mostrarCasilla(const Casilla& c); // Pre: Casilla -----> Post: Muestra la casilla si es propiedad, estacion o utilidad (servicio), da un mensaje para comprar si esta sin propietario 


#endif
