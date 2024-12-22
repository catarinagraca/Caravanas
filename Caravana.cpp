//
// Created by catar on 18/12/2024.
//
//
// Created by catar on 18/12/2024.
//

#include "Caravana.h"

#include <iostream>

#include "Cidade.h"

int Caravana:: idCaravana=1; //inicializa a ordem dos ids

Caravana:: Caravana(int aguaa,int capacidade,int numTrip, int tripMax,int mercadoria,int mercMax, position pos,char c, int moves) {
    id=idCaravana++;
    agua=aguaa;
    capacidadeAgua=capacidade;
    numTripulantes=numTrip;
    tripulacaoMaxima=tripMax;
    numMercadoria=mercadoria;
    mercadoriaMaxima=mercMax;
    posicao=pos;
    tipo=c;
    automove=false;         //0 n está ativado
    numMovimentos=moves;
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
    return capacidadeAgua;
}
int Caravana::getAguaAtual() {
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
        cout<<"Atributos: agua atual  "<<agua<<" ,tripulacao atual:"<<numTripulantes<<" ,mercadoria atual:"<<numMercadoria<<"toneladas, automovimento: "<<automove<<endl;
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
int Caravana::reabasteceAgua() {
    return agua=capacidadeAgua;
}

void Caravana::setPos(position pos) {
    if (numMovimentos>0) {
        posicao=pos;
        numMovimentos--;
        cout << "Caravana " << id << " movida para (" << pos.linha << ", " << pos.coluna << ")." << endl;
    }else {
        cout<<"Nao pode movimentar mais"<<endl;
    }

}

bool Caravana::getAutomove() {
    return automove;
}

void Caravana::changeAutoMoveTrue() {
    automove=true;
}
void Caravana::changeAutoMoveFalse() {
    automove=false;
}

void Caravana::alteraAgua(int valor) {
    agua=valor+agua;

}

int Caravana::setMoves(int movimentos) {
    return numMovimentos=movimentos;
}

