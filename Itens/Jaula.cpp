//
// Created by catar on 23/12/2024.
//

#include "Jaula.h"

#include <iostream>

void Jaula::efeito(Caravana &caravana, Deserto &deserto) {

    int novosTripulantes =caravana.getTripulacaoMaxima() - caravana.getTripulacaoAtual();
    caravana.adicionaTripulacao(novosTripulantes);
    cout << "Jaula! " << novosTripulantes << " prisioneiros se juntaram a tripulacao." << endl;
}
