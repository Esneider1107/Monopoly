#include "cartaEspecial.h"
#include <iostream>




Cartas_Comunity crearCartasComunity(std::vector<Carta> cartas_vector){
    Cartas_Comunity cartas_comunity;
    for(const auto& carta : cartas_vector){
        cartas_comunity.cartas_comunity.push(carta);
    }
    return cartas_comunity;
}


Cartas_Chance crearCartasChance(std::vector<Carta> cartas_vector){
    Cartas_Chance cartas_chance;
    for(const auto& carta : cartas_vector){
        cartas_chance.cartas_chance.push(carta);
    }
    return cartas_chance;
}