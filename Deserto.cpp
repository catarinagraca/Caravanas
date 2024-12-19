//
// Created by catar on 17/12/2024.
//

#include "Deserto.h"
#include <iosfwd>
#include <vector>

#include "Caravanas/CaravanaComercio.h"
#include "Caravanas/CaravanaMilitar.h"
#include "Caravanas/CaravanaSecreta.h"
#include "Caravana.h"
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
            buffer.setChar(i-1,j,linhaLida[j]);
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
    procuraCaravana();
    procuraCidade();
}

bool Deserto::lerComando(int &fase) {
    string linha, comando;
    vector<string> argumentos;

    cout<<"\nInsira comando:"<<endl;

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
            lerFicheiro(argumentos[0]);
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
        if (comando == "precos") {
            if (argumentos.size() != 0) {
                cout<<"Argumentos a mais!"<<endl;
                return false;
            }
            listaPrecoMercadorias();
            return true;
        }
        else if (comando == "moedas"){
            if (argumentos.size() != 1) {
                cout<<"Falta segundo argumento (exemplo moedas <valor>)"<<endl;
                return false;
            }
            acrescentaMoedas(stoi(argumentos[0]));
            return true;
        }
        else if (comando== "caravana") {
            if (argumentos.size() != 1) {
                cout<<"Falta segundo argumento (exemplo caravana <idCaravana>)"<<endl;
                return false;
            }
            procuraCaravanaComId(stoi(argumentos[0]));
            return true;

        }
    }


    return true;
}

void Deserto::listaPrecoMercadorias(){

    cout << "Preco de venda de mercadoria: " << preço_venda_mercadoria << endl;
    cout << "Preco de compra de mercadoria: " << preço_compra_mercadoria << endl;
}

void Deserto::acrescentaMoedas(int N){
    moedas  += N;

    if (moedas<=0) {
        cout<<"Sem moedas!"<<endl;
        moedas=0;
    }

    cout << "Moedas atualizadas: " << this->moedas << endl;
}
void Deserto::procuraCidade() {
    for (int i = 0; i < buffer.getlinhas(); i++) {
        for (int j = 0; j < buffer.getColunas(); j++) {
            if (islower(buffer.getChar(i,j))) {  // Verifica se é uma letra

                position posicao;
                posicao.linha=i;
                posicao.coluna=j;

                adicionaCidade(buffer.getChar(i,j),posicao);
                //cidades.insert(make_pair(buffer.getChar(i,j),posicao)); // Armazena a posição e letra
            }
        }
    }

}

void Deserto::printCidade() {
    for (auto cidade:cidades) {
        position pos=cidade.getPos();
        cout<<"Cidade "<<cidade.getChar()<<" posicao, linha:"<<pos.linha<<" ,coluna:"<<pos.coluna<<endl;
    }

}

void Deserto::adicionaCidade(char c,position pos) {
    Cidade temp=Cidade(c,pos);
    cidades.push_back(temp);
}



void Deserto::procuraCaravana() {
    for (int i = 0; i < buffer.getlinhas(); i++) {
        for (int j = 0; j < buffer.getColunas(); j++) {
            if (isdigit(buffer.getChar(i,j))) {  // Verifica se é uma letra

                position posicao;
                posicao.linha=i;
                posicao.coluna=j;
                //cout<<posicao.linha<<posicao.coluna<<endl;
                adicionaCaravana('C',posicao);

            }
        }
    }

}

void Deserto::adicionaCaravana(char c,position pos) {
    if (c == 'M') {
        CaravanaMilitar temp=CaravanaMilitar(pos);
        caravanas.push_back(temp);
    }
    if (c == 'C') {
        CaravanaComercio temp=CaravanaComercio(pos);
        caravanas.push_back(temp);
    }
    if (c == 'S') {
        CaravanaSecreta temp= CaravanaSecreta(pos);
        caravanas.push_back(temp);
    }
}


void Deserto::procuraCaravanaComId(int id) {
    for (auto caravana: caravanas) {
        if (caravana.getId()==id)
            caravana.printCaravana();
    }
}

void Deserto::compraCaravana() {

}



