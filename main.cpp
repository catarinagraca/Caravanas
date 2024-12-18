#include <iostream>

#include "Deserto.h"
#include "Buffer.h"

int main()
{

    int fase=1;
    Deserto deserto;
    string nome="mapa.txt";
    deserto.lerFicheiro(nome);


   /*while (fase) {
       deserto.lerComando(deserto, fase);
   } */

    deserto.procuraCidade();
    deserto.printCidade();
    deserto.listaPrecoMercadorias();
    deserto.acrescentaMoedas(100);
    deserto.acrescentaMoedas(-210);

    /*while (fase) {
        deserto.lerComando(deserto,fase);
        //cout<<fase<<endl;
    }*/

    //deserto.procuraCidade();
    //deserto.printCidade();


    return 0;
}
