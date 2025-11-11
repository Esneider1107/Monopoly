#include "cartaEspecial.h"
#include <iostream>


// Función auxiliar para convertir string a int de forma segura
int stringToIntSafe(const std::string& str) {
    if (str.empty()) {
        return 0;
    }
    // Eliminar espacios en blanco
    std::string trimmed = str;
    trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r\f\v"));
    trimmed.erase(trimmed.find_last_not_of(" \t\n\r\f\v") + 1);
    
    if (trimmed.empty()) {
        return 0;
    }
    
    try {
        return std::stoi(trimmed);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: No se pudo convertir '" << str << "' a entero" << std::endl;
        return 0;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Número fuera de rango '" << str << "'" << std::endl;
        return 0;
    }
}

std::vector<Carta> leerCartasDesdeTxt(const std::string& nombreArchivo) {
    std::vector<Carta> cartas;
    std::ifstream archivo(nombreArchivo);
    
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return cartas;
    }
    
    std::string linea;
    int numeroLinea = 0;

    while (std::getline(archivo, linea)) {
        numeroLinea++;
        
        // Ignorar líneas vacías
        if (linea.empty() || linea.find_first_not_of(" \t\n\r\f\v") == std::string::npos) {
            continue;
        }
        
        std::stringstream ss(linea);
        Carta c;
        std::string montoStr, montoCasaStr, montoHotelStr, casillaStr, multStr, movStr;

        try {
            std::getline(ss, c.descripcion, ';');
            std::getline(ss, c.tipo, ';');
            std::getline(ss, c.accion, ';');
            std::getline(ss, montoStr, ';');
            std::getline(ss, montoCasaStr, ';');
            std::getline(ss, montoHotelStr, ';');
            std::getline(ss, casillaStr, ';');
            std::getline(ss, multStr, ';');
            std::getline(ss, movStr, ';');

            c.monto = stringToIntSafe(montoStr);
            c.monto_casa = stringToIntSafe(montoCasaStr);
            c.monto_hotel = stringToIntSafe(montoHotelStr);
            c.casilla_destino = stringToIntSafe(casillaStr);
            c.multiplicador = stringToIntSafe(multStr);
            c.casillas_movimiento = stringToIntSafe(movStr);

            cartas.push_back(c);
        } catch (const std::exception& e) {
            std::cerr << "Error en línea " << numeroLinea << ": " << e.what() << std::endl;
            std::cerr << "Contenido: " << linea << std::endl;
        }
    }

    archivo.close();
    std::cout << "Se cargaron " << cartas.size() << " cartas desde " << nombreArchivo << std::endl;
    return cartas;
}

std::vector<Carta> leerCartasComunidadDesdeTxt(const std::string& nombreArchivo) {

    return leerCartasDesdeTxt(nombreArchivo);
}

std::vector<Carta> leerCartasChanceDesdeTxt(const std::string& nombreArchivo) {
    return leerCartasDesdeTxt(nombreArchivo);
}

Carta ObtenerCartaComunity(const Cartas_Comunity& cartas_comunity) {
    if (cartas_comunity.cartas_comunity.empty()) {
        std::cerr << "No hay cartas en la pila de Comunidad" << std::endl;
        return Carta();  // Retornar una carta vacía
    }

    Carta carta = cartas_comunity.cartas_comunity.front();
    return carta;
}

Carta ObtenerCartaChance(const Cartas_Chance& cartas_chance) {
    if (cartas_chance.cartas_chance.empty()) {
        std::cerr << "No hay cartas en la pila de Chance" << std::endl;
        return Carta();  // Retornar una carta vacía
    }

    Carta carta = cartas_chance.cartas_chance.front();
    return carta;
}
void ColocarAlFinalCartasComunity(Cartas_Comunity& cartas_comunity, Carta carta) {
    cartas_comunity.cartas_comunity.push(carta);
}

void ColocarAlFinalCartasChance(Cartas_Chance& cartas_chance, Carta carta) {
    cartas_chance.cartas_chance.push(carta);
}

void AplicarCarta(Tablero& tablero, Jugador& jugador, const Carta& carta, std::vector<Jugador>& jugadores){
    
    if(carta.accion == "mover_go"){
        jugador.posicion = 1;
        AgregarDinero(jugador, 200);
    }
    
    else if(carta.accion == "mover_casilla"){
        int posicionAnterior = jugador.posicion;
        jugador.posicion = carta.casilla_destino;
        
        if(jugador.posicion < posicionAnterior){
            AgregarDinero(jugador, 200);
        }
        
        if(carta.monto > 0){
            AgregarDinero(jugador, carta.monto);
        }
    }
    
    else if(carta.accion == "mover_estacion"){
        int posicionAnterior = jugador.posicion;
        
        if(jugador.posicion < 11){
            jugador.posicion = 6; 
        } else if(jugador.posicion < 21 && jugador.posicion >= 11){
            jugador.posicion = 16; 
        } else if(jugador.posicion < 31 && jugador.posicion >= 21){
            jugador.posicion = 26; 
        } else if(jugador.posicion <= 40 && jugador.posicion >= 31) {
            jugador.posicion = 36; 
        }
        
        // Si pasó por GO
        if(jugador.posicion < posicionAnterior){
            AgregarDinero(jugador, 200);
        }
        
        // Si tiene dueño, marca multiplicador
        if(!tablero.casillas.at(jugador.posicion).propietario.empty() && 
           tablero.casillas.at(jugador.posicion).propietario != jugador.nombre){
            jugador.multiplicador_alquiler = carta.multiplicador;
        }
    }
    
    // Mover a servicio cercano
    else if(carta.accion == "mover_servicio"){
        int posicionAnterior = jugador.posicion;
        
        if(jugador.posicion < 21 ){
            jugador.posicion = 13; // Electric Company
        } else if(jugador.posicion < 40 && jugador.posicion >= 21){
            jugador.posicion = 28; // Water Works
        }
        
        // Si pasó por GO
        if(jugador.posicion < posicionAnterior){
            AgregarDinero(jugador, 200);
        }
        
        // Si tiene dueño, marca multiplicador
        if(!tablero.casillas.at(jugador.posicion).propietario.empty() && 
           tablero.casillas.at(jugador.posicion).propietario != jugador.nombre){
            jugador.multiplicador_alquiler = carta.multiplicador;
        }
    }
    
    // Ir a la cárcel
    else if(carta.accion == "ir_carcel"){
        jugador.posicion = 11;
        jugador.enCarcel = true;
        jugador.turnosEnCarcel = 0;
    }
    
    // Retroceder
    else if(carta.accion == "retroceder"){
        jugador.posicion += carta.casillas_movimiento; // Ya es negativo
        if(jugador.posicion < 1){
            jugador.posicion += 40;
        }
    }
    
    // Recaudar dinero
    else if(carta.accion == "recaudar"){
        AgregarDinero(jugador, carta.monto);
    }
    
    // Pagar dinero
    else if(carta.accion == "pagar"){
        int montoPagar = abs(carta.monto);
        RetirarDinero(jugador, montoPagar);
    }
    
    // Pagar reparaciones
    else if(carta.accion == "pagar_reparaciones"){
        int totalReparaciones = 0;
        
        for(auto& casilla : tablero.casillas){
            if(casilla.second.propietario == jugador.nombre){
                if(casilla.second.nivel_propiedad >= 1 && casilla.second.nivel_propiedad <= 4){
                    totalReparaciones += carta.monto_casa * casilla.second.nivel_propiedad;
                } else if(casilla.second.nivel_propiedad == 5){
                    totalReparaciones += carta.monto_hotel;
                }
            }
        }
        RetirarDinero(jugador, totalReparaciones);
    }
    
    // Recaudar de jugadores
    else if(carta.accion == "recaudar_jugadores"){
        int totalRecaudado = 0;
        for(auto& otroJugador : jugadores){
            if(otroJugador.nombre != jugador.nombre){
                RetirarDinero(otroJugador, carta.monto);
                totalRecaudado += carta.monto;
            }
        }
        AgregarDinero(jugador, totalRecaudado);
    }
    
    // Pagar a jugadores
    else if(carta.accion == "pagar_jugadores"){
        int montoPorJugador = abs(carta.monto);
        for(auto& otroJugador : jugadores){
            if(otroJugador.nombre != jugador.nombre){
                RetirarDinero(jugador, montoPorJugador);
                AgregarDinero(otroJugador, montoPorJugador);
            }
        }
    }
    
    // Salir de la cárcel
    else if(carta.accion == "salir_carcel"){
        jugador.tiene_salir_carcel = true;
    }
}