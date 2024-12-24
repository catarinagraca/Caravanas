//
// Created by catar on 23/12/2024.
//

#ifndef JAULA_H
#define JAULA_H
#include "../Itens.h"


class Jaula :public Itens{
public:
    Jaula(position pos,int duracao):Itens(pos,duracao){}

    void efeito(Caravana &caravana, Deserto &deserto) override;


};



#endif //JAULA_H
