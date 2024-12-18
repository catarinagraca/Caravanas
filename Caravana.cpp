//
// Created by catar on 18/12/2024.
//

#include "Caravana.h"

int Caravana:: idCaravana=1; //inicializa a ordem dos __cpp_deduction_guides

Caravana:: Caravana(int aguaa,int numTrip, int tripMax,int mercadoria,int mercMax) {
    id=idCaravana++;
    agua=aguaa;
    numTripulantes=numTrip;
    tripulacaoMaxima=tripMax;
    numMercadoria=mercadoria;
    mercadoriaMaxima=mercMax;
}