//
// Created by catar on 17/12/2024.
//

#ifndef DESERTO_H
#define DESERTO_H
#include "Buffer.h"
#include <fstream>
#include <map>


struct position {
    int linha, coluna;
}typedef position;

class Deserto {
private:
    Buffer buffer;
    //int linhas, colunas;
    int moedas,instantes_entre_novos_itens,duração_item,max_itens,preço_venda_mercadoria,preço_compra_mercadoria,
    preço_caravana,instantes_entre_novos_barbaros,duração_barbaros;
    map<char,position> cidades;

public:
    Deserto(): buffer(){}

    void lerFicheiro(string &nome);
    bool lerComando(Deserto deserto, int &fase);
    void procuraCidade();
    void printCidade();


};



#endif //DESERTO_H
