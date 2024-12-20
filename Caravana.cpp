//
// Created by catar on 18/12/2024.
//
//
// Created by catar on 18/12/2024.
//

#include "Caravana.h"

#include <iostream>

#include "Cidade.h"

int Caravana:: idCaravana=1; //inicializa a ordem dos __cpp_deduction_guides

Caravana:: Caravana(int aguaa,int numTrip, int tripMax,int mercadoria,int mercMax, position pos,char c) {
    id=idCaravana++;
    agua=aguaa;
    numTripulantes=numTrip;
    tripulacaoMaxima=tripMax;
    numMercadoria=mercadoria;
    mercadoriaMaxima=mercMax;
    posicao=pos;
    tipo=c;
}


position Caravana::getPos() {
    return this->posicao;
}

int Caravana::getId() {
    return id;
}

char Caravana::getTipo(){
    return tipo;
}

int Caravana::getAgua() {
    return agua;
}

int Caravana::getMercadoriaAtual() {
    return  numMercadoria;
}

int Caravana::getTripulacaoAtual() {
    return numTripulantes;
}

void Caravana::printCaravana() {
        cout<<"->Caravana "<<id<<" do tipo "<<tipo<<endl;
        cout <<"Posicao, linha:"<<posicao.linha<<" ,coluna:"<<posicao.coluna<<endl;
        cout<<"Atributos: capacidade de agua "<<agua<<" ,tripulacao atual:"<<numTripulantes<<" ,mercadoria atual:"<<numMercadoria<<"toneladas."<<endl;
        cout<<endl;
    }

int Caravana::getMercadoriaMaxima() {
    return mercadoriaMaxima;
}
int Caravana::adicionaMercadoria(int toneladas) {
    return numMercadoria= toneladas+numMercadoria;
}

int Caravana::getTripulacaoMaxima() {
    return tripulacaoMaxima;
}

int Caravana::adicionaTripulacao(int trip) {
    return numTripulantes= trip+numTripulantes;
}