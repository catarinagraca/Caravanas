//
// Created by catar on 23/12/2024.
//

#ifndef ARCATESOURO_H
#define ARCATESOURO_H
#include "../Itens.h"




class ArcaTesouro:public Itens{
public:
    ArcaTesouro(position pos,int duracao):Itens(pos,duracao){}

    void efeito(Caravana &caravana, Deserto &deserto) override;

};



#endif //ARCATESOURO_H
