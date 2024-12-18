//
// Created by catar on 17/12/2024.
//

#ifndef CIDADE_H
#define CIDADE_H
#include <string>

#include "Deserto.h"
using namespace std;


class Cidade {
private:
    position posicao;
    char nome;
    int numCaravanasExistentes;
    int caravanasDisponiveisParaVenda;

public:
    Cidade(char c,position pos):nome(c), posicao(pos){}



};



#endif //CIDADE_H
