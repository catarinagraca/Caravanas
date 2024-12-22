//
// Created by catar on 18/12/2024.
//

#include "CaravanaMilitar.h"
void CaravanaMilitar::gastaAgua() {

    if (getTripulacaoAtual()<getTripulacaoMaxima()/2 || getTripulacaoAtual()==0) {
        alteraAgua(-1);
    }
    alteraAgua(-3);

}
void CaravanaMilitar::setMovimentos() {
    setMoves(3);
}
