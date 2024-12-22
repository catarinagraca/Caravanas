//
// Created by catar on 18/12/2024.
//

#ifndef CARAVANASECRETA_H
#define CARAVANASECRETA_H
#include "../Caravana.h"


class CaravanaSecreta :public Caravana{
public:
    CaravanaSecreta(position pos):Caravana(200,200,20,20,0,40,pos,'S'){};
    void gastaAgua() override;
};


#endif //CARAVANASECRETA_H
