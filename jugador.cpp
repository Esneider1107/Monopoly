#include "jugador.h"
#include "tablero.h"
#include <iostream>

//Funcion para crear un jugador
Jugador crearJugador(std::string nombre){
    Jugador jugador;
    jugador.nombre = nombre;
    jugador.saldo = 1500;
    jugador.posicion = 1;
    jugador.enCarcel = false;
    jugador.turnosEnCarcel = 0;
    jugador.tiene_salir_carcel = false;
    jugador.multiplicador_alquiler = 1;
    jugador.EnBancarrota = false;
    jugador.DadoPar = false;
    return jugador;
}
//Funcion para mostrar la informacion del jugador
void mostrarInfoJugador(const Tablero& tablero, const Jugador& jugador){
     std::cout << "\n========== JUGADOR: " << jugador.nombre << "==========\n\n";
     std:: cout << "Saldo: $" << jugador.saldo << "\n";
     std::cout << "Posicion: " << jugador.posicion << "\n";
     std::cout << "Propiedades:\n";
     for(const auto it : tablero.casillas){ // Itera sobre las casillas del tablero
        if(it.second.propietario == jugador.nombre){ // Busca las propiedades del jugador
            std::cout << it.second.nombre << "\n";
        }
     }
     std::cout << "\n=========================================\n";
}

//Funcion para agregar dinero al jugador
void AgregarDinero(Jugador& jugador, float monto){
    jugador.saldo += monto;
}
//Funcion para retirar dinero al jugador
void RetirarDinero( Jugador& jugador, float monto){
    jugador.saldo -= monto;
}
//Funcion para comprar una propiedad
void ComprarPropiedad(Jugador& jugador,  Casilla& propiedad){
    if(propiedad.propietario.empty()){ // Verifica que no tenga dueño
        if(jugador.saldo >= propiedad.precio){ // Verifica que tenga saldo suficiente
            jugador.saldo -= propiedad.precio;
            propiedad.propietario = jugador.nombre;
        } else {
            std::cout << "No tienes suficiente dinero para comprar esta propiedad.\n";
        }
    }
}
void ComprarCasa(Jugador& jugador, Casilla& propiedad){
    int costo_casa = propiedad.precio_casa;
    if(propiedad.propietario == jugador.nombre){
        if(propiedad.nivel_propiedad >= 0 && propiedad.nivel_propiedad < 4){ // Verifica que tenga menos de 4 casas
            if(jugador.saldo >= costo_casa){ // Verifica que tenga saldo suficiente
                jugador.saldo -= costo_casa;
                propiedad.nivel_propiedad += 1;
                std::cout << "Has comprado una casa en " << propiedad.nombre << ".\n";
            } else {
                std::cout << "No tienes suficiente dinero para comprar una casa en esta propiedad.\n";
            }
        } else {
            std::cout << "No puedes comprar mas casas en esta propiedad.\n";
        }
    } else {
        std::cout << "No eres el propietario de esta propiedad.\n";
    }
}

void ComprarHotel(Jugador& jugador, Casilla& propiedad){
    int costo_hotel = propiedad.precio_hotel;
    if(propiedad.propietario == jugador.nombre){
        if(propiedad.nivel_propiedad == 4){ // Verifica que tenga 4 casas
            if(jugador.saldo >= costo_hotel){ // Verifica que tenga saldo suficiente
                jugador.saldo -= costo_hotel;
                propiedad.nivel_propiedad = 5; // Nivel 5 representa un hotel
                std::cout << "Has comprado un hotel en " << propiedad.nombre << ".\n";
            } else {
                std::cout << "No tienes suficiente dinero para comprar un hotel en esta propiedad.\n";
            }
        } else {
            std::cout << "Necesitas tener 4 casas en esta propiedad para comprar un hotel.\n";
        }
    } else {
        std::cout << "No eres el propietario de esta propiedad.\n";
    }
}

//Funcion para vender una propiedad
void VenderPropiedad(Jugador& jugador, Casilla& propiedad){
    if(propiedad.propietario == jugador.nombre){ // Verifica que el jugador sea el propietario
        jugador.saldo += propiedad.precio / 2;
        propiedad.propietario.clear();
    } else {
        std::cout << "No eres el propietario de esta propiedad.\n";
    }
}

