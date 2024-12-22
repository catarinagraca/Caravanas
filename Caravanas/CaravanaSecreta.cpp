//
// Created by catar on 18/12/2024.
//

#include "CaravanaSecreta.h"


void CaravanaSecreta::gastaAgua() {

    if (getTripulacaoAtual()<getTripulacaoMaxima()/2 || getTripulacaoAtual()==0) {
        alteraAgua(-1);
    }
    alteraAgua(-3);

}