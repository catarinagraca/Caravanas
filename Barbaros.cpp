//
// Created by catar on 20/12/2024.
//

#include "Barbaros.h"

int Barbaros::getBarbaros() {
    return numBarbaros;
}
position Barbaros::getPos() {
    return this->pos;
}

void Barbaros::setPos(position posicao) {
    if(!combateEmAndamento) pos=posicao;


}
int Barbaros::removeTripulacao(int trip) {
    return numBarbaros= numBarbaros-trip;
}

void Barbaros::setComabte(bool combate) {
    combateEmAndamento=combate;
}
void Barbaros::setInstantes() {
    numTurnosRestantes--;
}

int Barbaros::getInstantes() {
    return numTurnosRestantes;
}

