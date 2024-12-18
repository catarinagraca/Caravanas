//
// Created by catar on 17/12/2024.
//

#ifndef CIDADE_H
#define CIDADE_H
#include <string>

using namespace std;
struct position {
    int linha, coluna;
}typedef position;

class Cidade {
private:
    position posicao;
    char nome;
    int numCaravanasExistentes;
    int caravanasDisponiveisParaVenda;

public:
    Cidade(char c,position pos):nome(c), posicao(pos){}
    char getChar() const;
    position getPos();




};



#endif //CIDADE_H
