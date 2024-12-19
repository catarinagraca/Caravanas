//
// Created by catar on 17/12/2024.
//

#include "Cidade.h"

#include <iostream>

char Cidade::getChar() const{
    return this->nome;
}

position Cidade::getPos() {
    return this->posicao;
}

void Cidade::conteudoCidade() {
    cout<<"Caravanas para Compra: "<<endl;
    for (auto caravana: caravanasParaCompra) {
        if (caravana.second == 0)
        cout<<"Tipo"<<caravana.first<<endl;
    }
    cout<<"Caravanas estacionadas: "<<endl;
    for (auto caravana: caravanasEstacionadas) {
        

    }



}

