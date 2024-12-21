//
// Created by catar on 17/12/2024.
//

#ifndef DESERTO_H
#define DESERTO_H
#include "Buffer.h"
#include <fstream>
#include <map>
#include <vector>

#include "Barbaros.h"
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
    vector<position> posTempestadeAreia;
    vector<Barbaros> caravanaBarbaros;  //talvez usar map para terem uma chave???
    vector<string> direcoes = {"D", "E", "C", "B", "CE", "CD", "BE", "BD"};

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
    void moveCaravana(int id, string direcao);
    void atualizaBuffer();
    bool verificaMovimento(int linha,int coluna);   //true movimento válido
    void pontuacao();
    void tempestadeAreia(int linha,int coluna, int raio);
    void procuraBarbaros();
    void adicionaBarbaros(position pos);
    void ativarAutomove(int id);
    void desativarAutomove(int id);
    void atualizaCaravana();
    void moverCaravanaBárbaro();

};



#endif //DESERTO_H
