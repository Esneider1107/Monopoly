#include "tablero.h"
#include "jugador.h"
#include <iostream>
#include <fstream>
#include <sstream>

//Funcion para crear el tablero con las casillas leidas
Tablero crearTablero(std::vector<Casilla> casillas){
    Tablero tablero;
    // Itero en el vector y voy asignando a cada casilla su posicion (1-40)
    for(size_t i = 0; i < casillas.size(); ++i){
        tablero.casillas[i + 1] = casillas[i];
    }
    return tablero;
};

//Funcion para obtener una casilla del tablero
Casilla obtenerCasilla(const Tablero& t, int pos){
    auto it =  t.casillas.find(pos); // Crea un iterador para buscar la casilla
    if(it != t.casillas.end()){
        return it->second; // Retorna la casilla encontrada
    } else {
        throw std::out_of_range("Casilla no encontrada"); // Manejo de error si no se encuentra la casilla
    }
}

//Funciones para mostrar el tablero y las casillas
void mostrarTablero(const Tablero& tablero, std::vector<Jugador>& jugadores) {
    std::cout << "\n========== TABLERO DE MONOPOLY ==========\n\n";
    // Mostrar cada casilla con su información básica
    for (int i = 1; i <= 40; i++) {
        std::cout << "Casilla " << i << ": ";
        
        std::cout << tablero.casillas.at(i).nombre;
        
        if (!tablero.casillas.at(i).color.empty()) {
            std::cout << " [" << tablero.casillas.at(i).color << "]";
        }
        
        if (tablero.casillas.at(i).precio > 0) {
            std::cout << " - Precio: $" << tablero.casillas.at(i).precio;
        }

        if(tablero.casillas.at(i).propietario != ""){
            std::cout << " - Propietario: " << tablero.casillas.at(i).propietario;
        }   
        for(auto jugador :jugadores){
            if(jugador.posicion == i){
                std::cout << " - Jugador: " << jugador.nombre;
            }
        }
        if (!tablero.casillas.at(i).funcion.empty()) {
            std::cout << " (" << tablero.casillas.at(i).funcion << ")";
        }
        
        std::cout << "\n";
    }
    
    std::cout << "\n=========================================\n";
}

//Funcion para mostrar una casilla y decir si lo compra
void mostrarCasilla(const Casilla& c){
    std::cout << "\n";
    if(c.funcion == "propiedad"){
        std::cout << "Nombre: " << c.nombre << "\n";
        std::cout << "Color: " << c.color << "\n";
        std::cout << "Precio: " << c.precio << "\n";
        std::cout << "Funcion: " << c.funcion << "\n";
        std::cout << "Propietario: " << c.propietario << "\n";
        std::cout << "Nivel Propiedad: " << c.nivel_propiedad << "\n";
        std::cout << "Alquileres: \n";
        for(auto it : c.alquiler){ // Itera sobre el mapa de alquileres
            std::cout << "Nivel: " << it.first << " - Valor: " << it.second << "\n";
        }
        if(c.propietario.empty()){
            std::cout << "No tiene dueño\n";
            std::cout << "Para comprar, escriba comprar:\n";
        } 
        std::cout << "\n";
    } else if (c.funcion == "estacion" || c.funcion == "utilidad"){
        std::cout << "Nombre: " << c.nombre << "\n";
        std::cout << "Precio: " << c.precio << "\n";
        std::cout << "Funcion: " << c.funcion << "\n";
        std::cout << "Propietario: " << c.propietario << "\n";
        std::cout << "Nivel Propiedad: " << c.nivel_propiedad << "\n";
        std::cout << "Alquileres: \n";
        for(auto it : c.alquiler){ // Itera sobre el mapa de alquileres
            std::cout << "Nivel: " << it.first << " - Valor: " << it.second << "\n";
        }
        if(c.propietario.empty()){ 
            std::cout << "No tiene dueño\n";
            std::cout << "Para comprar, escriba comprar:\n";
        } 

    }
    
}

//Funcion para recibir las casillas desde un archivo txt
std::vector<Casilla> leerCasillasDesdeTxt(const std::string& nombreArchivo) {
    std::vector<Casilla> casillas;
    std::ifstream archivo(nombreArchivo);
    std::string linea;
    //Itera sobre cada linea del archivo
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        Casilla c;
        std::string precioStr, alquileresStr;
        
        // Leer nombre
        std::getline(ss, c.nombre, ';');
        
        // Leer color
        std::getline(ss, c.color, ';');
        
        // Leer precio
        std::getline(ss, precioStr, ';');
        if (!precioStr.empty()) {
            c.precio = std::stoi(precioStr); // Convertir a entero los precios
        } else {
            c.precio = 0;
        }
        
        // Leer función
        std::getline(ss, c.funcion, ';');
        
        // Leer alquileres (formato: nivel1:valor1,nivel2:valor2,nivel3:valor3...)
        std::getline(ss, alquileresStr, ';');
        if (!alquileresStr.empty()) {
            std::stringstream ssAlquileres(alquileresStr);
            std::string parAlquiler;
            
            while (std::getline(ssAlquileres, parAlquiler, ',')) { // Separar los alquileres por nivel
                std::stringstream ssPar(parAlquiler);
                std::string nivelStr, valorStr;
                
                std::getline(ssPar, nivelStr, ':');
                std::getline(ssPar, valorStr, ':');
                
                if (!nivelStr.empty() && !valorStr.empty()) {
                    int nivel = std::stoi(nivelStr);
                    int valor = std::stoi(valorStr);
                    c.alquiler[nivel] = valor; // Se mete el nivel y el valor al mapa de alquileres
                }
            }
        }
        
        // Inicializar propietario vacío
        c.propietario = "";
        c.nivel_propiedad = 0;
        if(c.funcion == "estacion" || c.funcion == "utilidad"){
            c.nivel_propiedad = 1; // Las estaciones y utilidades empiezan con nivel 1
        }
        
        casillas.push_back(c); // Se mete al vector la casilla creada
    }
    
    archivo.close();
    return casillas;
}
