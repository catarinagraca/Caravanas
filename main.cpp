#include <iostream>

#include "Deserto.h"
#include "Buffer.h"

int main()
{

    int fase=1;
    Deserto deserto;

    do {
        if (fase==1) {
            Caravana::resetID();  //como é static posso fazer isto
        }
        deserto.lerComando(fase);
    }while (fase !=0);




    return 0;
}
