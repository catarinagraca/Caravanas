//
// Created by catar on 20/12/2024.
//

#include "Barbaros.h"

int Barbaros:: idBarbaros=1; //inicializa a ordem dos ids
int Barbaros::getBarbaros() {
    return numBarbaros;
}
position Barbaros::getPos() {
    return this->pos;
}
int Barbaros::getId() {
    return id;
}
void Barbaros::setPos(position posicao) {
    pos=posicao;

}

