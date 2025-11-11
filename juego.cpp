#include "juego.h"
#include <iostream>

Juego crearJuego(const std::vector<Jugador>& jugadores, const Tablero& tablero, const Cartas_Chance& cartas_chance, const Cartas_Comunity& cartas_comunity){
    Juego juego;
    juego.jugadores = jugadores;
    juego.tablero = tablero;
    juego.cartas_chance = cartas_chance;
    juego.cartas_comunity = cartas_comunity;
    juego.turno = 0;
    juego.juego_activo = true;
    return juego;
}

std::pair<int, int> lanzardados(Juego& juego){
    int dado1 = rand() % 6 + 1;
    int dado2 = rand() % 6 + 1;
    return std::make_pair(dado1, dado2);
}

void moverJugador(Juego& juego, int indiceJugador, std::pair<int, int> pasos){
    int total_pasos = pasos.first + pasos.second;
    juego.jugadores[indiceJugador].posicion += total_pasos;
    if(juego.jugadores[indiceJugador].posicion > 40){
        juego.jugadores[indiceJugador].posicion -= 40;
        AgregarDinero(juego.jugadores[indiceJugador], 200);
    }
}

void aplicarCasilla(Juego& juego, int posicion, int indiceJugador){
    if(juego.tablero.casillas.at(posicion).funcion == "propiedad"){
        if(juego.tablero.casillas.at(posicion).propietario.empty()){
            mostrarCasilla(juego.tablero.casillas.at(posicion));
            std::string comando;
            std::cin >> comando;
            if(comando == "comprar"){
                ComprarPropiedad(juego.jugadores[indiceJugador], juego.tablero.casillas.at(posicion));
                mostrarCasilla(juego.tablero.casillas.at(posicion));
                pasarturno(juego);
            } else {
                pasarturno(juego);
            }
        } else {
            pasarturno(juego);
        }
    } else if(juego.tablero.casillas.at(posicion).funcion == "Community Chest"){
        sacarCartaComunity(juego, indiceJugador);
        pasarturno(juego);
    } else if(juego.tablero.casillas.at(posicion).funcion == "Chance"){
        sacarCartaChance(juego, indiceJugador);
        
        pasarturno(juego);
    } else if(juego.tablero.casillas.at(posicion).funcion == "Income Tax"){
        RetirarDinero(juego.jugadores[indiceJugador], 200);
        pasarturno(juego);
    } else if(juego.tablero.casillas.at(posicion).funcion == "estacion"){
        if(juego.tablero.casillas.at(posicion).propietario.empty()){
            mostrarCasilla(juego.tablero.casillas.at(posicion));
            std::string comando;
            std::cin >> comando;
            if(comando == "comprar"){
                ComprarPropiedad(juego.jugadores[indiceJugador], juego.tablero.casillas.at(posicion));
                mostrarCasilla(juego.tablero.casillas.at(posicion));
                pasarturno(juego);
            } else {
                pasarturno(juego);
            }
        } else {
            pasarturno(juego);
        }
    } else if(juego.tablero.casillas.at(posicion).funcion == "jail"){
        pasarturno(juego);
    } else if(juego.tablero.casillas.at(posicion).funcion == "Free Parking"){
        pasarturno(juego);
    } else if(juego.tablero.casillas.at(posicion).funcion == "Go To Jail"){
        juego.jugadores[indiceJugador].enCarcel = true;
        juego.jugadores[indiceJugador].turnosEnCarcel = 1;
        juego.jugadores[indiceJugador].posicion = 11;
        pasarturno(juego);
    } else if(juego.tablero.casillas.at(posicion).funcion == "Luxury Tax"){
        juego.jugadores[indiceJugador].saldo -= 100;
        pasarturno(juego);
    }
}

void cobrarAlquiler(Juego& juego, int indiceJugador, int indiceQJugador, int pos){
    
    // Obtenemos las referencias a los jugadores
    Jugador& propietario = juego.jugadores[indiceJugador];
    Jugador& jugadorQuePaga = juego.jugadores[indiceQJugador];
  
    // Obtenemos las casillas correspondientes
    Casilla& propiedad = juego.tablero.casillas[pos];

    int nivel = propiedad.nivel_propiedad;
    int montoBase = 0;
    //Verificacion de las casillas tenga propietario

    if(propiedad.propietario.empty() || propiedad.propietario != propietario.nombre){
        std::cout << "Esta casilla no es de este jugador" << std::endl;
        return;
    }
        //Obtenemos el nivel de propiedad 
        int nivel = propiedad.nivel_propiedad;
        int montoBase = 0;

        
    if(propiedad.alquiler.find(nivel)!= propiedad.alquiler.end()){
            montoBase = propiedad.alquiler[nivel];
        }
        else{
            std::cout << "No se encontro un valor de alquiler para este nivel"<<std::endl;
            return;
        }

    // Aplicamos multiplicadores si el propietario tiene ventajas 
    int multiplicador = 1;

    if (!propiedad.color.empty()) {
        int total_color = 0;
        int total_propietario = 0;

        for (auto& c : juego.tablero.casillas) {
            if (c.second.color == propiedad.color) {
                total_color++;
                if (c.second.nombre == propietario.nombre)
                    total_propietario++;
            }
        }

        if (total_color > 1 && total_color == total_propietario)
            multiplicador = 2;
    }

    int montoFinal= montoBase * multiplicador;
    
    //Verificamos si el jugador tiene dinero
    if (jugadorQuePaga.saldo < montoFinal) {
        std::cout << jugadorQuePaga.nombre << " no tiene suficiente dinero para pagar el alquiler.\n";
        jugadorQuePaga.saldo = 0; // Podrias marcar bancarrota mas adelante
    } else {
        jugadorQuePaga.saldo -= montoFinal;
        propietario.saldo += montoFinal;
    }

    std::cout << jugadorQuePaga.nombre << " pagó $" << montoFinal
              << " de alquiler a " << propietario.nombre
              << " por caer en " << propiedad.nombre << ".\n";
}
    
 

void sacarCartaChance(Juego& juego, int indiceJugador){
    Carta carta = ObtenerCartaChance(juego.cartas_chance);
    AplicarCarta(juego.tablero, juego.jugadores[indiceJugador], carta, juego.jugadores);
    ColocarAlFinalCartasChance(juego.cartas_chance, carta);
}

void sacarCartaComunity(Juego& juego, int indiceJugador){
    Carta carta = ObtenerCartaComunity(juego.cartas_comunity);
    AplicarCarta(juego.tablero, juego.jugadores[indiceJugador], carta, juego.jugadores);
    ColocarAlFinalCartasComunity(juego.cartas_comunity, carta);
}

void guardarEstadoHistorial(Juego& juego){
    Historial historial;
    historial.jugadores = juego.jugadores;
    historial.tablero = juego.tablero;
    historial.cartas_chance = juego.cartas_chance;
    historial.cartas_comunity = juego.cartas_comunity;
    historial.turno = juego.turno;
    juego.historial.push(historial);
}


void DeshacerUltimaAccion(Juego& juego){
    if(!juego.historial.empty()){
        Historial historial = juego.historial.top();
        juego.jugadores = historial.jugadores;
        juego.tablero = historial.tablero;
        juego.cartas_chance = historial.cartas_chance;
        juego.cartas_comunity = historial.cartas_comunity;
        juego.turno = historial.turno;
        juego.historial.pop();
    } else {
        std::cout << "No hay acciones para deshacer" << std::endl;
    }
}

void pasarturno(Juego& juego){
    juego.turno++;
    if(juego.turno >= juego.jugadores.size()){
        juego.turno = 0;
    }
}

void turnoActual(Juego& juego){
    int indiceJugador = juego.turno;
    lanzardados(juego);
    moverJugador(juego, indiceJugador, lanzardados(juego));
    aplicarCasilla(juego, juego.jugadores[indiceJugador].posicion, indiceJugador);
    guardarEstadoHistorial(juego);
    pasarturno(juego);
}

