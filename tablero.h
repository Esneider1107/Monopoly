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
std::vector<Casilla> leerCasillasDesdeTxt(const std::string& nombreArchivo);
//Funcion para crear el tablero con las casillas leidas
Tablero crearTablero(std::vector<Casilla> casillas);
//Funciones para mostrar el tablero y las casillas
void mostrarTablero(const Tablero& t, std::vector<Jugador>& jugadores);
//funcion para obtener una casilla del tablero
Casilla obtenerCasilla(const Tablero& t, int pos);
//funcion para mostrar una casilla y decir si lo compra
void mostrarCasilla(const Casilla& c);


#endif
