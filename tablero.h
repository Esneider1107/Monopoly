#ifndef TABLERO_H
#define TABLERO_H

#include <string>
#include <vector>
#include <map>


struct Casilla {
    std::string nombre;
    std::string funcion;  
    int precio;
    std::map<int, int> alquiler;
    std::string propietario;
    std::string color;
    int nivel_propiedad;
};

struct Tablero {
    std::map<int, Casilla> casillas;
};

typedef struct Tablero Tablero;

typedef struct Casilla Casilla;

std::vector<Casilla> leerCasillasDesdeTxt(const std::string& nombreArchivo);
Tablero crearTablero(std::vector<Casilla> casillas);
void mostrarTablero(const Tablero& t);
Casilla obtenerCasilla(const Tablero& t, int pos);
void mostrarCasilla(const Casilla& c);


#endif
