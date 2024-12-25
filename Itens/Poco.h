//
// Created by catar on 25/12/2024.
//

#ifndef POCO_H
#define POCO_H
#include "../Itens.h"


class Poco :public Itens{
public:
    Poco(position pos,int duracao):Itens(pos,duracao){};
    void efeito(Caravana &caravana, Deserto &deserto) override;

};



#endif //POCO_H
