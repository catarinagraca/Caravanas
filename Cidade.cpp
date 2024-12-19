//
// Created by catar on 17/12/2024.
//

#include "Cidade.h"

#include <iostream>

#include "Deserto.h"


char Cidade::getChar() const{
    return this->nome;
}

position Cidade::getPos() {
    return this->posicao;
}

void Cidade::conteudoCidade() {
    cout<<"Caravanas para Compra: "<<endl;
    int i=1;
    for (auto caravana: caravanasParaCompra) {
        if (caravana.second == 0)
        cout<<i<<"- Tipo: "<<caravana.first<<endl;
        i++;
    }
    // cout<<"Caravanas estacionadas: "<<endl;
    // for (auto caravana: caravanasEstacionadas) {
    //     cout<<caravana.second.getAgua();
    // }
}

void Cidade::compraCaravana(char tipo) {
    for (auto &caravana: caravanasParaCompra){
        if (caravana.second == 0) {
            if(caravana.first==toupper(tipo)) {

                caravana.second=1;
                return;
                //caravanasParaCompra.erase(caravana.first);
            }
        }
    }
    cout<<"A caravana ja nao esta disponivel"<<endl;

}
