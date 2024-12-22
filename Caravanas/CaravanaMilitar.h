//
// Created by catar on 18/12/2024.
//

#ifndef CARAVANAMILITAR_H
#define CARAVANAMILITAR_H
#include "../Caravana.h"


class CaravanaMilitar :public Caravana{
public:
    CaravanaMilitar(position pos):Caravana(400,400,40,40,0,5,pos,'M',3){};
     void gastaAgua() override ;
    void setMovimentos() override;
};



#endif //CARAVANAMILITAR_H
