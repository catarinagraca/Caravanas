//
// Created by catar on 23/12/2024.
//

#ifndef ITENS_H
#define ITENS_H
#include "Caravana.h"
#include "Cidade.h"

class Deserto;//definição antecipada - existe uma classe qualquer chamada Deserto e quando compilar vai saber o que é
using namespace std;

class Itens {
private:
    position pos;
    int instantes;
public:
    Itens(position posicao,int duracao):pos(posicao),instantes(duracao){}
    position getPos();
    void instantesRestantes();
    int getInstantes();

    virtual void efeito(Caravana &caravana, Deserto &deserto)=0;

};



#endif //ITENS_H
