//
// Created by catar on 18/12/2024.
//

#ifndef CARAVANA_H
#define CARAVANA_H
#include "Cidade.h"


class Caravana {
private:
    int id;
    int numTripulantes;
    int numMercadoria;
    int agua;
    int capacidadeAgua;
    int mercadoriaMaxima;
    int tripulacaoMaxima;
    position posicao;
    char tipo;
    bool automove;

    static int  idCaravana;//para incrementar

public:
    Caravana(int aguaa,int capacidade,int numTrip, int tripMax,int mercadoria,int mercMax,position pos, char tipo);
    position getPos();
    int getId();
    char getTipo();
    int getAgua();
    int getAguaAtual();
    int getMercadoriaAtual();
    int getTripulacaoAtual();
    void printCaravana();
    int getMercadoriaMaxima();
    int adicionaMercadoria(int toneladas);
    int getTripulacaoMaxima() ;
    int adicionaTripulacao(int trip);
    int reabasteceAgua();
    void setPos(position pos);
    bool getAutomove();
    void changeAutoMoveTrue();
    void changeAutoMoveFalse();


};



#endif //CARAVANA_H
