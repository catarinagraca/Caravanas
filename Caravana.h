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
    int mercadoriaMaxima;
    int tripulacaoMaxima;
    position posicao;
    char tipo;

    static int  idCaravana;//para incrementar

public:
    Caravana(int aguaa,int numTrip, int tripMax,int mercadoria,int mercMax,position pos, char tipo);
    position getPos();
    int getId();
    char getTipo();
    int getAgua();
    int getMercadoriaAtual();
    int getTripulacaoAtual();
    void printCaravana();
    int getMercadoriaMaxima();
    int adicionaMercadoria(int toneladas);



};



#endif //CARAVANA_H
