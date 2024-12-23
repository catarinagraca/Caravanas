//
// Created by catar on 23/12/2024.
//

#ifndef MINA_H
#define MINA_H
#include "../Itens.h"


class Mina:public  Itens{
public:
    Mina(position pos,int duracao):Itens(pos,duracao){}

    void efeito(Caravana &caravana) override;
};



#endif //MINA_H
