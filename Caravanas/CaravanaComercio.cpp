//
// Created by catar on 18/12/2024.
//

#include "CaravanaComercio.h"

void CaravanaComercio::gastaAgua()  {
    if (getAguaAtual()==0) {
            removeTripulacao(1);
            resetAgua();
    }else {
        if (getTripulacaoAtual()==0) {
            alteraAgua(0);

        }else if (getTripulacaoAtual()<getTripulacaoMaxima()/2) {
            alteraAgua(-1);
        }else {
            alteraAgua(-2);
        }
    }


}

void CaravanaComercio::setMovimentos() {
    setMoves(2);
}
