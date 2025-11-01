#include "tablero.h"
#include <iostream>

Tablero crearTablero(){
    std::map<int, Casilla> casillas;
    
    // Casilla 1
    casillas[1].nombre = "GO";
    casillas[1].funcion = "GO";

    // Casilla 2
    casillas[2].nombre = "Old Kent Road";
    casillas[2].precio = 60;
    casillas[2].color = "marron";

    // Casilla 3
    casillas[3].nombre = "Community Chest";
    casillas[3].funcion = "Community Chest";

    // Casilla 4
    casillas[4].nombre = "Whitechapel Road";
    casillas[4].precio = 60;
    casillas[4].color = "marron";

    // Casilla 5
    casillas[5].nombre = "Income Tax";
    casillas[5].alquiler = 200;

    // Casilla 6
    casillas[6].nombre = "Kings Cross Station";
    casillas[6].precio = 200;

    // Casilla 7
    casillas[7].nombre = "The Angel Islington";
    casillas[7].precio = 100;
    casillas[7].color = "celeste";

    // Casilla 8
    casillas[8].nombre = "Chance";
    casillas[8].funcion = "Chance";

    // Casilla 9
    casillas[9].nombre = "Euston Road";
    casillas[9].precio = 100;
    casillas[9].color = "celeste";

    // Casilla 10
    casillas[10].nombre = "Pentonville Road";
    casillas[10].precio = 120;
    casillas[10].color = "celeste";

    // Casilla 11
    casillas[11].nombre = "Just Visiting/Jail";
    casillas[11].funcion = "Jail";

    // Casilla 12
    casillas[12].nombre = "Pall Mall";
    casillas[12].precio = 140;
    casillas[12].color = "rosa";

    // Casilla 13
    casillas[13].nombre = "Electric Company";
    casillas[13].precio = 150;

    // Casilla 14
    casillas[14].nombre = "Whitehall";
    casillas[14].precio = 140;
    casillas[14].color = "rosa";

    // Casilla 15
    casillas[15].nombre = "Northumberland Avenue";
    casillas[15].precio = 160;
    casillas[15].color = "rosa";

    // Casilla 16
    casillas[16].nombre = "Marylebone Station";
    casillas[16].precio = 200;

    // Casilla 17
    casillas[17].nombre = "Bow Street";
    casillas[17].precio = 180;
    casillas[17].color = "naranja";

    // Casilla 18
    casillas[18].nombre = "Community Chest";
    casillas[18].funcion = "Community Chest";

    // Casilla 19
    casillas[19].nombre = "Marlborough Street";
    casillas[19].precio = 180;
    casillas[19].color = "naranja";

    // Casilla 20
    casillas[20].nombre = "Vine Street";
    casillas[20].precio = 200;
    casillas[20].color = "naranja";

    // Casilla 21
    casillas[21].nombre = "Free Parking";
    casillas[21].funcion = "Free Parking";

    // Casilla 22
    casillas[22].nombre = "Strand";
    casillas[22].precio = 220;
    casillas[22].color = "rojo";

    // Casilla 23
    casillas[23].nombre = "Chance";
    casillas[23].funcion = "Chance";

    // Casilla 24
    casillas[24].nombre = "Fleet Street";
    casillas[24].precio = 220;
    casillas[24].color = "rojo";

    // Casilla 25
    casillas[25].nombre = "Trafalgar Square";
    casillas[25].precio = 240;
    casillas[25].color = "rojo";

    // Casilla 26
    casillas[26].nombre = "Fenchurch St Station";
    casillas[26].precio = 200;

    // Casilla 27
    casillas[27].nombre = "Leicester Square";
    casillas[27].precio = 260;
    casillas[27].color = "amarillo";

    // Casilla 28
    casillas[28].nombre = "Coventry Street";
    casillas[28].precio = 260;
    casillas[28].color = "amarillo";

    // Casilla 29
    casillas[29].nombre = "Water Works";
    casillas[29].precio = 150;

    // Casilla 30
    casillas[30].nombre = "Piccadilly";
    casillas[30].precio = 280;
    casillas[30].color = "amarillo";

    // Casilla 31
    casillas[31].nombre = "Go To Jail";
    casillas[31].funcion = "Go To Jail";

    // Casilla 32
    casillas[32].nombre = "Regent Street";
    casillas[32].precio = 300;
    casillas[32].color = "verde";

    // Casilla 33
    casillas[33].nombre = "Oxford Street";
    casillas[33].precio = 300;
    casillas[33].color = "verde";

    // Casilla 34
    casillas[34].nombre = "Community Chest";
    casillas[34].funcion = "Community Chest";

    // Casilla 35
    casillas[35].nombre = "Bond Street";
    casillas[35].precio = 320;
    casillas[35].color = "verde";

    // Casilla 36
    casillas[36].nombre = "Liverpool Street Station";
    casillas[36].precio = 200;

    // Casilla 37
    casillas[37].nombre = "Chance";
    casillas[37].funcion = "Chance";

    // Casilla 38
    casillas[38].nombre = "Park Lane";
    casillas[38].precio = 350;
    casillas[38].color = "azul";

    // Casilla 39
    casillas[39].nombre = "Super Tax";
    casillas[39].alquiler = 100;

    // Casilla 40
    casillas[40].nombre = "Mayfair";
    casillas[40].precio = 400;
    casillas[40].color = "azul";

    Tablero tablero;
    tablero.casillas = casillas;
    return tablero;
}

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
        
        if (tablero.casillas.at(i).alquiler > 0) {
            std::cout << " - Pagar: $" << tablero.casillas.at(i).alquiler;
        }
        
        if (!tablero.casillas.at(i).funcion.empty()) {
            std::cout << " (" << tablero.casillas.at(i).funcion << ")";
        }
        
        std::cout << "\n";
    }
    
    std::cout << "\n=========================================\n";
}
