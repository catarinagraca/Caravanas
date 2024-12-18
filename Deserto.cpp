//
// Created by catar on 17/12/2024.
//

#include "Deserto.h"
#include <iosfwd>
#include <vector>
using namespace std;

void Deserto::lerFicheiro(string &nome) {
    ifstream file(nome);
    if (!file.is_open()) {
        cout<<"Erro: o ficheiro não foi aberto"<<endl;
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
    buffer.render();

    // Lê os parâmetros configuráveis (como moedas)
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string name;
        int value;
        if (iss >> name >> value) {
            if (name == "moedas") {
                moedas = value;
                cout<<"Moedas:"<<moedas<<endl;
            } else if (name == "instantes_entre_novos_itens") {
                instantes_entre_novos_itens = value;
                cout<<"Instante entre novos itens: "<<instantes_entre_novos_itens<<endl;
            } else if (name == "duração_item") {
                duração_item = value;
                cout<<"Duracao item: "<<duração_item<<endl;
            } else if (name == "max_itens") {
                max_itens = value;
                cout<<"Maximo de itens: "<<max_itens<<endl;
            } else if (name == "preço_venda_mercadoria") {
                preço_venda_mercadoria = value;
                cout<<"Preco venda da mercadoria: "<<preço_venda_mercadoria<<endl;
            } else if (name == "preço_compra_mercadoria") {
                preço_compra_mercadoria = value;
                cout<<"Preco compra da mercadoria: "<<preço_compra_mercadoria<<endl;
            } else if (name == "preço_caravana") {
                preço_caravana = value;
                cout<<"Preco caravana: "<<preço_caravana<<endl;
            } else if (name == "instantes_entre_novos_barbaros") {
                instantes_entre_novos_barbaros = value;
                cout<<"Instantes entre novos barbaros: "<<instantes_entre_novos_itens<<endl;
            } else if (name == "duração_barbaros") {
                duração_barbaros = value;
                cout<<"Duracao de barbaros: "<<duração_barbaros<<endl;
            }
        }
    }
}

bool Deserto::lerComando(Deserto deserto,int &fase) {
    string linha, comando;
    vector<string> argumentos;

    cout<<"Insira comando:"<<endl;

    getline(cin,linha);
    istringstream iss(linha);

    iss>>comando;

    // Lê as palavras restantes e armazena no array 'argumentos'
    string argumento;
    while (iss >> argumento) {
        argumentos.push_back(argumento);
    }
    if (comando.empty()) {
        //cout<<"Insira comando novamente:"<<endl;
        return false;
    }
    if (fase==1) {
        if (comando=="config") {
            if (argumentos.size() != 1) {
                cout<<"Falta segundo argumento (exemplo config <nomeFicheiro>)"<<endl;
                return false;
            }
            deserto.lerFicheiro(argumentos[0]);
            fase=2;
            return true;
        }else if (comando == "sair") {
            fase = 0;
            return false;
        }
        else {
            cout<<"Comando desconhecido"<<endl;
            return false;
        }
    }
    if (fase==2) {

    }
    return true;
}

void Deserto::procuraCidade() {
    for (int i = 0; i < buffer.getlinhas(); i++) {
        for (int j = 0; j < buffer.getColunas(); j++) {
            cout<<"lol"<<endl;
            if (isalpha(buffer.getChar(i,j))) {  // Verifica se é uma letra

                position posicao;
                posicao.linha=i;
                posicao.coluna=j;
                cidades.insert(make_pair(buffer.getChar(i,j),posicao)); // Armazena a posição e letra
            }
        }
    }

}

void Deserto::printCidade() {
    for (auto cidade:cidades) {
        cout<<"Cidade "<<cidade.first<<" posicao, linha:"<<cidade.second.linha<<" ,coluna:"<<cidade.second.coluna<<endl;
    }

}
