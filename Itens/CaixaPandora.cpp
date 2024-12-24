//
// Created by catar on 23/12/2024.
//

#include "CaixaPandora.h"

#include <iostream>
#include <ostream>

#include "../Caravana.h"

void CaixaPandora::efeito(Caravana &caravana, Deserto &deserto) {

    caravana.removeTripulacao(caravana.getTripulacaoAtual()*0.2);
    cout << "Caixa de Pandora! 20% da tripulação foi dizimada." << endl;

}
