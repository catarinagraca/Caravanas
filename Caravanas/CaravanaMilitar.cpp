//
// Created by catar on 18/12/2024.
//

#include "CaravanaMilitar.h"
void CaravanaMilitar::gastaAgua() {
    if (getAguaAtual()==0) {
        removeTripulacao(1);
        resetAgua();
    }else {
        if (getTripulacaoAtual()<getTripulacaoMaxima()/2 || getTripulacaoAtual()==0) {
            alteraAgua(-1);
        }
        alteraAgua(-3);
        if (getAgua()==0) {
            removeTripulacao(1);
            resetAgua();
        }
    }
}
void CaravanaMilitar::setMovimentos() {
    setMoves(3);
}
