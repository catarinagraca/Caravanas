#include <iostream>

#include "Deserto.h"
#include "Buffer.h"

int main()
{

    int fase=1;
    Deserto deserto;
    // string nome="mapa.txt";
    // deserto.lerFicheiro(nome);


    //deserto.printCidade();
    /*deserto.listaPrecoMercadorias();
    deserto.acrescentaMoedas(100);
    deserto.acrescentaMoedas(-210);*/

    while (fase) {
        deserto.lerComando(fase);
        //cout<<fase<<endl;
    }


    // deserto.procuraCaravana();
    //
    // deserto.procuraCaravanaComId(3);


    return 0;
}
