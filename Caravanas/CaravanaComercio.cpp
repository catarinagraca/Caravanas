//
// Created by catar on 18/12/2024.
//

#include "CaravanaComercio.h"

void CaravanaComercio::gastaAgua()  {

    if (getTripulacaoAtual()<getTripulacaoMaxima()/2) {
        alteraAgua(-1);
    }else if (getTripulacaoAtual()==0) {
        alteraAgua(0);
    }
    alteraAgua(-2);

}

void CaravanaComercio::setMovimentos() {
    setMoves(2);
}
