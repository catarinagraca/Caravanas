//
// Created by catar on 23/12/2024.
//

#include "Mina.h"

#include <iostream>
#include <ostream>

#include "../Deserto.h"

void Mina::efeito(Caravana &caravana, Deserto &deserto) {
        cout << "Mina! A caravana foi destruída!" << endl;
        deserto.removeCaravana(caravana.getId());

}
