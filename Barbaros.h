//
// Created by catar on 20/12/2024.
//

#ifndef BARBAROS_H
#define BARBAROS_H
#include "Cidade.h"


class Barbaros{
private:
    int numBarbaros;
    position pos;

public:
    Barbaros(position posicao):numBarbaros(40),pos(posicao){};

    int getBarbaros();
    position getPos();

};



#endif //BARBAROS_H
