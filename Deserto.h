//
// Created by catar on 17/12/2024.
//

#ifndef DESERTO_H
#define DESERTO_H
#include "Buffer.h"
#include <fstream>
#include <map>
#include <vector>

#include "Caravana.h"
#include "Cidade.h"



class Deserto {
private:
    Buffer buffer;
    //int linhas, colunas;
    int moedas,instantes_entre_novos_itens,duração_item,max_itens,preço_venda_mercadoria,preço_compra_mercadoria,
    preço_caravana,instantes_entre_novos_barbaros,duração_barbaros;
    vector <Cidade> cidades;
    vector<Caravana> caravanas;

public:
    Deserto(): buffer(){}

    void lerFicheiro(string &nome);
    bool lerComando( int &fase);
    void procuraCidade();
    void adicionaCidade(char c,position pos);
    void printCidade();
    void listaPrecoMercadorias();
    void acrescentaMoedas(int N);
    void procuraCaravana();
    void adicionaCaravana(char c,position pos);
    void procuraCaravanaComId(int id);
    void compraCaravana();


};



#endif //DESERTO_H
