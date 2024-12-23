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
    bool combateEmAndamento;
    int numTurnosRestantes;

    static int idBarbaros;

public:
    Barbaros(position posicao):numBarbaros(40),pos(posicao),id(idBarbaros++) {
        combateEmAndamento=false;
        numTurnosRestantes=60;
    };

    int getBarbaros();
    position getPos();
    int getId();
    void setPos(position posicao);
    int removeTripulacao(int trip) ;
    void setComabte(bool combate);
    void setInstantes();
    int getInstantes();

};



#endif //BARBAROS_H
