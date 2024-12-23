//
// Created by catar on 23/12/2024.
//

#ifndef CAIXAPANDORA_H
#define CAIXAPANDORA_H
#include "../Itens.h"


class Caravana;

class CaixaPandora :public Itens{
public:
    CaixaPandora(position pos,int duracao):Itens(pos,duracao){}

    void efeito(Caravana &caravana) override;

};



#endif //CAIXAPANDORA_H
