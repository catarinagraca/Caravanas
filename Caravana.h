//
// Created by catar on 18/12/2024.
//

#ifndef CARAVANA_H
#define CARAVANA_H



class Caravana {
private:
    int id;
    int numTripulantes;
    int numMercadoria;
    int agua;
    int mercadoriaMaxima;
    int tripulacaoMaxima;

    static int  idCaravana;//para incrementar

public:
    Caravana(int aguaa,int numTrip, int tripMax,int mercadoria,int mercMax);



};



#endif //CARAVANA_H
