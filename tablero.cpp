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
        std::cout << "Precio por casa: $" << c.precio_casa << "\n";  
        std::cout << "Precio por hotel: $" << c.precio_hotel << "\n";
        std::cout << "Funcion: " << c.funcion << "\n";
        std::cout << "Propietario: " << c.propietario << "\n";
        std::cout << "Nivel Propiedad: " << c.nivel_propiedad << "\n";
        std::cout << "Alquileres: \n";
        for(auto it : c.alquiler){ // Itera sobre el mapa de alquileres
            std::cout << "Nivel: " << it.first << " - Valor: " << it.second << "\n";
        }
        if(c.propietario.empty()){
            std::cout << "No tiene propietario\n";
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
            std::cout << "No tiene propietario\n";
            std::cout << "Para comprar, escriba comprar:\n";
        } 

    }
    
}

//Funcion para recibir las casillas desde un archivo txt
std::vector<Casilla> leerCasillasDesdeTxt(const std::string& nombreArchivo) {
    std::vector<Casilla> casillas;
    std::ifstream archivo(nombreArchivo);
    
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return casillas;
    }
    
    std::string linea;
    int numeroLinea = 0;
    
    while (std::getline(archivo, linea)) {
        numeroLinea++;
        
        // Ignorar líneas vacías
        if (linea.empty()) {
            continue;
        }
        
        std::stringstream ss(linea);
        Casilla c;
        std::string precioStr, alquileresStr, precioCasaStr, precioHotelStr;
        
        try {
            // Leer nombre
            std::getline(ss, c.nombre, ';');
            
            // Leer color
            std::getline(ss, c.color, ';');
            
            // Leer precio
            std::getline(ss, precioStr, ';');
            c.precio = (!precioStr.empty() && precioStr.find_first_not_of(" \t") != std::string::npos) 
                       ? std::stoi(precioStr) : 0;
            
            // Leer función
            std::getline(ss, c.funcion, ';');
            
            // Leer alquileres
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
            
            // Leer precio de casa
            std::getline(ss, precioCasaStr, ';');
            c.precio_casa = (!precioCasaStr.empty() && precioCasaStr.find_first_not_of(" \t") != std::string::npos) 
                           ? std::stoi(precioCasaStr) : 0;
            
            // Leer precio de hotel
            std::getline(ss, precioHotelStr);  // 
            // Limpiar posible '\r' (retorno de carro en Windows)
            if (!precioHotelStr.empty() && precioHotelStr.back() == '\r') {
                precioHotelStr.pop_back();
            }
            c.precio_hotel = (!precioHotelStr.empty() && precioHotelStr.find_first_not_of(" \t") != std::string::npos) 
                            ? std::stoi(precioHotelStr) : 0;
            
            // Inicializar propietario vacío
            c.propietario = "";
            c.nivel_propiedad = 0;
            
            if(c.funcion == "estacion" || c.funcion == "utilidad"){
                c.nivel_propiedad = 1;
            }
            
            casillas.push_back(c);
            
        } catch (const std::exception& e) {
            std::cerr << "Error en línea " << numeroLinea << ": " << e.what() << std::endl;
            std::cerr << "Contenido: " << linea << std::endl;
        }
    }
    
    archivo.close();
    std::cout << "Se cargaron " << casillas.size() << " casillas desde " << nombreArchivo << std::endl;
    return casillas;
}