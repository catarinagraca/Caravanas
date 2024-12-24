//
// Created by catar on 23/12/2024.
//

#include "ArcaTesouro.h"
#include "../Deserto.h" //definição completa
#include <iostream>

void ArcaTesouro::efeito(Caravana &caravana, Deserto &deserto) {
    deserto.acrescentaMoedas(deserto.getMoedas() * 0.1);
    cout << "Arca do Tesouro! 10% mais moedas para a caravana." << endl;
}
