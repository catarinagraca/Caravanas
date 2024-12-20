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
#include "Montanhas.h"


class Deserto {
private:
    Buffer buffer;
    //int linhas, colunas;
    int moedas,instantes_entre_novos_itens,duração_item,max_itens,preço_venda_mercadoria,preço_compra_mercadoria,
    preço_caravana,instantes_entre_novos_barbaros,duração_barbaros;
    vector <Cidade> cidades;
    vector<Caravana> caravanas;
    vector<Montanhas> montanhas;

public:
    Deserto(): buffer(){}

    void lerFicheiro(string &nome);
    bool lerComando( int &fase);
    void procuraCidadeeAdicionaBuffer();
    void adicionaCidade(char c,position pos);
    void listaPrecoMercadorias();
    void acrescentaMoedas(int N);
    void procuraCaravana();
    int adicionaCaravana(char c,position pos);
    void procuraCaravanaComId(int id);
    void compraCaravana(char c,char tipo);
    void listaCidade(char c);
    bool verificaCoordenadas(char cidade,int id) ;
    void compraMercadoria(int id, int toneladas);
    // bool caravanaEmCidade(int id) const;
    void vendeMercadoria(int id);
    void compraTripulantes(int numTripulantes,int id);
    void atualizaAgua(int id) /*const*/;
    void procuraMontanha();
    void adicionaMontanha(position pos);
    void moveCaravana(int id, char direcao);
    void atualizaBuffer();
    bool verificaMovimento(int linha,int coluna);   //true movimento válido



};



#endif //DESERTO_H
