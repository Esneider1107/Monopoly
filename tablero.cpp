#include "tablero.h"
#include <iostream>
#include <fstream>
#include <sstream>

Tablero crearTablero(std::vector<Casilla> casillas){
    Tablero tablero;
    for(size_t i = 0; i < casillas.size(); ++i){
        tablero.casillas[i + 1] = casillas[i];
    }
    return tablero;
};

Casilla obtenerCasilla(const Tablero& t, int pos){
    auto it =  t.casillas.find(pos);
    if(it != t.casillas.end()){
        return it->second;
    } else {
        throw std::out_of_range("Casilla no encontrada");
    }
}

void mostrarTablero(const Tablero& tablero) {
    std::cout << "\n========== TABLERO DE MONOPOLY ==========\n\n";
    
    for (int i = 1; i <= 40; i++) {
        std::cout << "Casilla " << i << ": ";
        
        std::cout << tablero.casillas.at(i).nombre;
        
        if (!tablero.casillas.at(i).color.empty()) {
            std::cout << " [" << tablero.casillas.at(i).color << "]";
        }
        
        if (tablero.casillas.at(i).precio > 0) {
            std::cout << " - Precio: $" << tablero.casillas.at(i).precio;
        }
        
        
        
        if (!tablero.casillas.at(i).funcion.empty()) {
            std::cout << " (" << tablero.casillas.at(i).funcion << ")";
        }
        
        std::cout << "\n";
    }
    
    std::cout << "\n=========================================\n";
}


void mostrarCasilla(const Casilla& c){
    if(c.funcion == "propiedad"){
        std::cout << "Nombre: " << c.nombre << "\n";
        std::cout << "Color: " << c.color << "\n";
        std::cout << "Precio: " << c.precio << "\n";
        std::cout << "Funcion: " << c.funcion << "\n";
        std::cout << "Propietario: " << c.propietario << "\n";
        std::cout << "Nivel Propiedad: " << c.nivel_propiedad << "\n";
        std::cout << "Alquileres: \n";
        for(auto it : c.alquiler){
            std::cout << "Nivel: " << it.first << " - Valor: " << it.second << "\n";
        }
        if(c.propietario.empty()){
            std::cout << "No tiene dueño\n";
            std::cout << "Si desea comprar, escriba comprar\n";
        } 
        std::cout << "\n";
    } else if (c.funcion == "estacion" || c.funcion == "utilidad"){
        std::cout << "Nombre: " << c.nombre << "\n";
        std::cout << "Precio: " << c.precio << "\n";
        std::cout << "Funcion: " << c.funcion << "\n";
        std::cout << "Propietario: " << c.propietario << "\n";
        std::cout << "Nivel Propiedad: " << c.nivel_propiedad << "\n";
        std::cout << "Alquileres: \n";
        for(auto it : c.alquiler){
            std::cout << "Nivel: " << it.first << " - Valor: " << it.second << "\n";
        }
        if(c.propietario.empty()){
            std::cout << "No tiene dueño\n";
            std::cout << "Si desea comprar, escriba comprar\n";
        } 

    }
    
}

std::vector<Casilla> leerCasillasDesdeTxt(const std::string& nombreArchivo) {
    std::vector<Casilla> casillas;
    std::ifstream archivo(nombreArchivo);
    std::string linea;
    
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
            c.precio = std::stoi(precioStr);
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
            
            while (std::getline(ssAlquileres, parAlquiler, ',')) {
                std::stringstream ssPar(parAlquiler);
                std::string nivelStr, valorStr;
                
                std::getline(ssPar, nivelStr, ':');
                std::getline(ssPar, valorStr, ':');
                
                if (!nivelStr.empty() && !valorStr.empty()) {
                    int nivel = std::stoi(nivelStr);
                    int valor = std::stoi(valorStr);
                    c.alquiler[nivel] = valor;
                }
            }
        }
        
        // Inicializar propietario vacío
        c.propietario = "";
        
        casillas.push_back(c);
    }
    
    archivo.close();
    return casillas;
}
