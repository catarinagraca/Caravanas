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

    for (auto caravana: caravanasParaCompra) {
        if (caravana.second == 0)
        cout<<"- Tipo: "<<caravana.first<<endl;

    }
     cout<<"\nCaravanas estacionadas: "<<endl;
    // for (auto caravana: caravanasEstacionadas) {
    //     cout<<caravana.second.getAgua();
    // }
}

bool Cidade::compraCaravana(char tipo) {
    for (auto &caravana: caravanasParaCompra){
        if (caravana.second == 0) {
            if(caravana.first==toupper(tipo)) {

                caravana.second=1;
                // caravanasDisponiveisParaVenda--;
                return true;
                //caravanasParaCompra.erase(caravana.first);
            }
        }
    }
    cout<<"A caravana ja nao esta disponivel"<<endl;
    return false;

}
