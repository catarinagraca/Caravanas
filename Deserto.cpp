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
    procuraCidadeeAdicionaBuffer();
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
        else if (comando== "cidade") {
            if (argumentos.size() != 1) {
                cout<<"Falta segundo argumento (exemplo cidade <letraCidade>)"<<endl;
                return false;
            }
            listaCidade(argumentos[0][0]/*, cidades*/); //tenho q acedersó há primeira posição pq é uma string
            return true;

        }
        else if (comando == "comprac") {
            if (argumentos.size() != 2) {
                cout<<"Falta argumentos (exemplo comprac <letraCidade> <tipoCaravana>)"<<endl;
                return false;
            }
            compraCaravana(argumentos[0][0],argumentos[1][0]); //tenho q acedersó há primeira posição pq é uma string
            return true;
        }
        else if (comando == "compra") {
            if (argumentos.size() != 2) {
                cout<<"Falta argumentos (exemplo compra <idCaravana> <numToneladas>)"<<endl;
                return false;
            }
            compraMercadoria(stoi(argumentos[0]),stoi(argumentos[1]));
            return true;
        }

        else if (comando == "vende") {
            if (argumentos.size() != 1) {
                cout<<"Falta argumentos (exemplo vende <idCaravana>)"<<endl;
                return false;
            }
            vendeMercadoria(stoi(argumentos[0]));
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
void Deserto::procuraCidadeeAdicionaBuffer() {
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
        cout<<"Nao pode adicionar mais mercadoria"<<endl;
        if (caravana.getId()==id)
            caravana.printCaravana();
        // return;caravana
    }
}

void Deserto::compraCaravana(char c, char tipo) {
    for (auto &cidade: cidades) {
        if(cidade.getChar() == c) {
            if(cidade.compraCaravana(tipo)) {
                adicionaCaravana(toupper(tipo),cidade.getPos());
                acrescentaMoedas(-preço_caravana);

            }

        }
    }

}

void Deserto::listaCidade(char c) {
    for (auto cidade: cidades) {
        if (c==cidade.getChar()) {
            cidade.conteudoCidade();
        }

    }
    for (auto caravana: caravanas) {
        if (verificaCoordenadas(c,caravana.getId())) {
            caravana.printCaravana();
        }
    }

}

bool Deserto::verificaCoordenadas(char c,int id) const {
    position posCidade,posCaravana;
    for (auto cidade: cidades) {
        if(cidade.getChar()==c ) {
            posCidade=cidade.getPos();

        }
    }
    for (auto caravana: caravanas) {
        if(caravana.getId()==id ) {
            posCaravana=caravana.getPos();

        }
    }

    if (posCaravana.coluna==posCidade.coluna && posCaravana.linha==posCidade.linha) {
        return true;
    }
    return false;
}

void Deserto::compraMercadoria(int id, int toneladas) {
    for (const auto& cidade : cidades) {
        if (verificaCoordenadas(cidade.getChar(), id)) {
            for (auto &caravana: caravanas) {
                if (caravana.getId()==id) {
                    if (caravana.getMercadoriaAtual()+toneladas<=caravana.getMercadoriaMaxima()) {
                        caravana.adicionaMercadoria(toneladas);
                        acrescentaMoedas(-(toneladas * preço_compra_mercadoria));
                    }
                    else {
                        cout<<"Nao pode adicionar mais mercadoria"<<endl;
                    }
                    return;

                }
            }

        }
    }cout<<"A caravana nao esta numa cidade"<<endl;

}

void Deserto::vendeMercadoria(int id) {
    for (const auto& cidade : cidades) {
        if (verificaCoordenadas(cidade.getChar(), id)) {
            for (auto &caravana: caravanas) {
                if (caravana.getId()==id) {
                    int mercadoriaAtual = caravana.getMercadoriaAtual();
                    if (mercadoriaAtual > 0) {
                        caravana.adicionaMercadoria(-mercadoriaAtual); // Remove toda a mercadoria
                        acrescentaMoedas(mercadoriaAtual * preço_venda_mercadoria); // Calcula e adiciona as moedas
                        cout << "Mercadoria vendida com sucesso!" << endl;
                    } else {
                        cout << "A caravana não possui mercadoria para vender." << endl;
                    }
                    return;
                }
            }
        }
    }

    cout<<"A caravana nao esta numa cidade"<<endl;

}


