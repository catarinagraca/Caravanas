//
// Created by catar on 23/12/2024.
//

#ifndef ITENS_H
#define ITENS_H
#include "Caravana.h"
#include "Cidade.h"



class Itens {
private:
    position pos;
    int instantes;
public:
    Itens(position posicao,int duracao):pos(posicao),instantes(duracao){}
    position getPos();
    void instantesRestantes();
    virtual void efeito(Caravana &caravana)=0;
    int getInstantes();

};



#endif //ITENS_H
