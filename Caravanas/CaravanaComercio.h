//
// Created by catar on 18/12/2024.
//

#ifndef CARAVANACOMERCIO_H
#define CARAVANACOMERCIO_H
#include "../Caravana.h"


class CaravanaComercio :public Caravana{

public:
CaravanaComercio(position pos):Caravana(200,200,20,20,0,40,pos,'C',2){};

    void gastaAgua() override;
    void setMovimentos() override;

};



#endif //CARAVANACOMERCIO_H
