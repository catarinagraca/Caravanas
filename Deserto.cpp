//
// Created by catar on 17/12/2024.
//

#include "Deserto.h"
using namespace std;

void Deserto::lerFicheiro(string &nome) {
    ifstream file(nome);
    if (!file.is_open()) {
        cerr<<"Erro: o ficheiro não foi aberto"<<endl;
    }

    string espaco;
    int linhas,colunas;

    file>>espaco>>linhas;
    file>>espaco>>colunas;
    buffer.setDimensions(linhas,colunas);

    string linhaLida;

    for (int i=0;i<=linhas;i++) {
        getline(file,linhaLida);
        for (int j=0;j<colunas;j++) {
            buffer.setChar(i,j,linhaLida[j]);
        }
    }
}


void Deserto::printDeserto() {
    buffer.render();
}