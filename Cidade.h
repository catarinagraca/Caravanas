//
// Created by catar on 17/12/2024.
//

#ifndef CIDADE_H
#define CIDADE_H
#include <map>
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
    //map<int,Caravana> caravanasEstacionadas; //id de caravanas
    map<char,int> caravanasParaCompra;  //int = 1, vendida

public:
    Cidade(char c,position pos):nome(c), posicao(pos) {
        caravanasParaCompra={
        {'M',0},{'S',0},{'C',0}};
    }
    char getChar() const;
    position getPos();
    void conteudoCidade();
    void compraCaravana(char tipo);






};



#endif //CIDADE_H
