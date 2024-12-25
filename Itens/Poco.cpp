//
// Created by catar on 25/12/2024.
//

#include "Poco.h"

#include <iostream>
#include <ostream>



void Poco::efeito(Caravana &caravana, Deserto &deserto) {
    int novaAgua=caravana.getAgua()-caravana.getAguaAtual();
    caravana.alteraAgua(novaAgua);
    cout<<"A caravana passou por um poço! Ganhou "<<caravana.getAgua()<<"litros de água"<<endl;
}
