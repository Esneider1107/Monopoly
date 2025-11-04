#ifndef TABLERO_H
#define TABLERO_H

#include <string>
#include <vector>
#include <map>


struct Casilla {
    std::string nombre;
    std::string funcion;  
    int precio;
    int alquiler;
    std::string propietario;
    std::string color;
};

struct Tablero {
    std::map<int, Casilla> casillas;
};


Tablero crearTablero();
void mostrarTablero(const Tablero& t);
Casilla obtenerCasilla(const Tablero& t, int pos);

#endif
