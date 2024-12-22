//
// Created by catar on 20/12/2024.
//

#ifndef BARBAROS_H
#define BARBAROS_H
#include "Cidade.h"


class Barbaros{
private:
    int id;
    int numBarbaros;
    position pos;

    static int idBarbaros;

public:
    Barbaros(position posicao):numBarbaros(40),pos(posicao),id(idBarbaros++){};

    int getBarbaros();
    position getPos();
    int getId();
    void setPos(position posicao);

};



#endif //BARBAROS_H
