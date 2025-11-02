#include "jugador.h"
#include "tablero.h"
#include <iostream>

Jugador crearJugador(std::string nombre){
    Jugador jugador;
    jugador.nombre = nombre;
    jugador.saldo = 1500;
    jugador.posicion = 1;
    return jugador;
}

void mostrarInfoJugador(const Tablero& tablero, const Jugador& jugador){
     std::cout << "\n========== JUGADOR: " << jugador.nombre << "==========\n\n";
     std:: cout << "Saldo: $" << jugador.saldo << "\n";
     std::cout << "Posicion: " << jugador.posicion << "\n";
     for(const auto it : tablero.casillas){
        if(it.second.propietario == jugador.nombre){
            std::cout << it.second.nombre << "\n";
        }
     }
     std::cout << "\n=========================================\n";
}

void AgregarDinero(Jugador& jugador, float monto){
    jugador.saldo += monto;
}

void RetirarDinero( Jugador& jugador, float monto){
    jugador.saldo -= monto;
}

void ComprarPropiedad(Jugador& jugador,  Casilla& propiedad){
    if(propiedad.propietario.empty()){
        if(jugador.saldo >= propiedad.precio){
            jugador.saldo -= propiedad.precio;
            propiedad.propietario = jugador.nombre;
        } else {
            std::cout << "No tienes suficiente dinero para comprar esta propiedad.\n";
        }
    }
}

void VenderPropiedad(Jugador& jugador, Casilla& propiedad){
    if(propiedad.propietario == jugador.nombre){
        jugador.saldo += propiedad.precio / 2;
        propiedad.propietario.clear();
    } else {
        std::cout << "No eres el propietario de esta propiedad.\n";
    }
}

