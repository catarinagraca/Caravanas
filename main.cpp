#include <iostream>

#include "Deserto.h"
#include "Buffer.h"

int main()
{

    int fase=1;
    Deserto deserto;
    string nome="mapa.txt";
    //deserto.lerFicheiro(nome);

    while (fase) {
        deserto.lerComando(deserto,fase);
    }

    return 0;
}
