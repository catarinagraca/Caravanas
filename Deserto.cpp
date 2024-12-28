//
// Created by catar on 17/12/2024.
//

#include "Deserto.h"

#include <algorithm>
#include <iosfwd>
#include <string.h>
#include <vector>

#include "Caravanas/CaravanaComercio.h"
#include "Caravanas/CaravanaMilitar.h"
#include "Caravanas/CaravanaSecreta.h"
#include "Caravana.h"
#include "Itens/ArcaTesouro.h"
#include "Itens/CaixaPandora.h"
#include "Itens/Jaula.h"
#include "Itens/Mina.h"
#include "Itens/Poco.h"
using namespace std;

void Deserto::lerFicheiro(string &nome) {
    ifstream file(nome);
    if (!file.is_open()) {
        cout << "Erro: o ficheiro nao foi aberto" << endl;
    }

    string espaco;
    int linhas, colunas;

    file >> espaco >> linhas;
    file >> espaco >> colunas;
    buffer.setDimensions(linhas, colunas);

    string linhaLida;

    for (int i = 0; i <= linhas; i++) {
        getline(file, linhaLida);
        for (int j = 0; j < colunas; j++) {
            buffer.setChar(i - 1, j, linhaLida[j]);
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
                cout << "Moedas:" << moedas << endl;
            } else if (name == "instantes_entre_novos_itens") {
                instantes_entre_novos_itens = value;
                cout << "Instante entre novos itens: " << instantes_entre_novos_itens << endl;
            } else if (name == "duração_item") {
                duração_item = value;
                cout << "Duracao item: " << duração_item << endl;
            } else if (name == "max_itens") {
                max_itens = value;
                cout << "Maximo de itens: " << max_itens << endl;
            } else if (name == "preço_venda_mercadoria") {
                preço_venda_mercadoria = value;
                cout << "Preco venda da mercadoria: " << preço_venda_mercadoria << endl;
            } else if (name == "preço_compra_mercadoria") {
                preço_compra_mercadoria = value;
                cout << "Preco compra da mercadoria: " << preço_compra_mercadoria << endl;
            } else if (name == "preço_caravana") {
                preço_caravana = value;
                cout << "Preco caravana: " << preço_caravana << endl;
            } else if (name == "instantes_entre_novos_barbaros") {
                instantes_entre_novos_barbaros = value;
                cout << "Instantes entre novos barbaros: " << instantes_entre_novos_itens << endl;
            } else if (name == "duração_barbaros") {
                duração_barbaros = value;
                cout << "Duracao de barbaros: " << duração_barbaros << endl;
            }
        }
    }
    procuraCaravana();
    procuraCidadeeAdicionaBuffer();
    procuraMontanha();
    procuraBarbaros();
}
bool Deserto::lerComando(int &fase) {
    string linha, comando;
    vector<string> argumentos;

    cout << "\nInsira comando:" << endl;

    getline(cin, linha);
    istringstream iss(linha);

    iss >> comando;

    // Lê as palavras restantes e armazena no array 'argumentos'
    string argumento;
    while (iss >> argumento) {
        argumentos.push_back(argumento);
    }

    if (comando.empty()) {
        return false;
    }

    if (fase == 1) {
        if (comando == "config") {
            if (argumentos.size() != 1) {
                cout << "Falta segundo argumento (exemplo config <nomeFicheiro>)" << endl;
                return false;
            }
            lerFicheiro(argumentos[0]);
            fase = 2;
            return true;
        } else if (comando == "sair") {
            fase = 0;
            return false;
        } else {
            cout << "Comando desconhecido" << endl;
            return false;
        }
    }

    if (fase == 2) {
        // Comando exec
        if (comando == "exec") {
            if (argumentos.size() != 1) {
                cout << "Falta argumento (exemplo exec <nomeFicheiro>)" << endl;
                return false;
            }

            string nomeFicheiro = argumentos[0];
            ifstream arquivo(nomeFicheiro);
            if (!arquivo.is_open()) {
                cout << "Erro ao abrir o arquivo " << nomeFicheiro << endl;
                return false;
            }

            // Ler o arquivo linha por linha e processar cada comando
            while (getline(arquivo, linha)) {
                // Ignorar linhas vazias ou comentários (caso haja)
                if (linha.empty() || linha[0] == '#') {
                    continue;
                }

                // Chamar a função para processar o comando
                if (!processaComando(linha, fase)) {
                    cout << "Erro ao processar o comando do arquivo: " << linha << endl;
                    return false;
                }
            }
            arquivo.close();
            return true;
        }

        // Para outros comandos digitados diretamente, utilizamos a mesma função
        if (!processaComando(linha, fase)) {
            return false;
        }
    }
    return false;
}

bool Deserto::processaComando(const string& linha, int &fase) {
    string comando;
    vector<string> argumentos;


    istringstream iss(linha);
    iss >> comando;


    string argumento;
    while (iss >> argumento) {
        argumentos.push_back(argumento);
    }

    if (comando == "config") {
        if (argumentos.size() != 1) {
            cout << "Falta segundo argumento (exemplo config <nomeFicheiro>)" << endl;
            return false;
        }
        lerFicheiro(argumentos[0]);
        fase = 2;
        return true;
    } else if (comando == "sair") {
        fase = 0;
        return false;
    } else if (comando == "precos") {
        if (argumentos.size() != 0) {
            cout << "Argumentos a mais!" << endl;
            return false;
        }
        listaPrecoMercadorias();
        return true;
    } else if (comando == "moedas") {
        if (argumentos.size() != 1) {
            cout << "Falta segundo argumento (exemplo moedas <valor>)" << endl;
            return false;
        }
        acrescentaMoedas(stoi(argumentos[0]));
        return true;
    } else if (comando == "caravana") {
        if (argumentos.size() != 1) {
            cout << "Falta segundo argumento (exemplo caravana <idCaravana>)" << endl;
            return false;
        }
        procuraCaravanaComId(stoi(argumentos[0]));
        return true;
    } else if (comando == "cidade") {
        if (argumentos.size() != 1) {
            cout << "Falta segundo argumento (exemplo cidade <letraCidade>)" << endl;
            return false;
        }
        listaCidade(argumentos[0][0]); // Acessa a primeira posição da string
        return true;
    } else if (comando == "comprac") {
        if (argumentos.size() != 2) {
            cout << "Falta argumentos (exemplo comprac <letraCidade> <tipoCaravana>)" << endl;
            return false;
        }
        compraCaravana(argumentos[0][0], argumentos[1][0]); // Acessa as primeiras posições
        return true;
    } else if (comando == "compra") {
        if (argumentos.size() != 2) {
            cout << "Falta argumentos (exemplo compra <idCaravana> <numToneladas>)" << endl;
            return false;
        }
        compraMercadoria(stoi(argumentos[0]), stoi(argumentos[1])); //stoi char to int
        return true;
    } else if (comando == "vende") {
        if (argumentos.size() != 1) {
            cout << "Falta argumentos (exemplo vende <idCaravana>)" << endl;
            return false;
        }
        vendeMercadoria(stoi(argumentos[0]));
        return true;
    } else if (comando == "tripul") {
        if (argumentos.size() != 2) {
            cout << "Falta argumentos (exemplo tripul <idCaravana> <numTripulantes>)" << endl;
            return false;
        }
        compraTripulantes(stoi(argumentos[0]), stoi(argumentos[1]));
        return true;
    } else if (comando == "move") {
        if (argumentos.size() != 2) {
            cout << "Falta argumentos (exemplo move <idCaravana> <direcao>)" << endl;
            return false;
        }
        moveCaravana(stoi(argumentos[0]), argumentos[1]);
        return true;
    } else if (comando == "terminar") {
        pontuacao();
        fase = 1;
        return true;
    } else if (comando == "areia") {
        if (argumentos.size() != 3) {
            cout << "Falta argumentos (exemplo areia <x> <y> <raio>)" << endl;
            return false;
        }
        tempestadeAreia(stoi(argumentos[0]), stoi(argumentos[1]), stoi(argumentos[2]));
        return true;
    } else if (comando == "barbaro") {
        if (argumentos.size() != 2) {
            cout << "Falta argumentos (exemplo barbaro <x> <y>)" << endl;
            return false;
        }
        adicionaBarbaros({stoi(argumentos[0]), stoi(argumentos[1])});
        atualizaBuffer();
        buffer.render();
        return true;
    } else if (comando == "auto") {
        if (argumentos.size() != 1) {
            cout << "Falta argumentos (exemplo auto <idCaravana>)" << endl;
            return false;
        }
        ativarAutomove(stoi(argumentos[0]));
        atualizaCaravana();
        return true;
    } else if (comando == "stop") {
        if (argumentos.size() != 1) {
            cout << "Falta argumentos (exemplo auto <idCaravana>)" << endl;
            return false;
        }
        desativarAutomove(stoi(argumentos[0]));
        atualizaCaravana();
        return true;
    } else if (comando == "prox") {
        if (argumentos.size() > 1) {
            cout << "argumentos a mais (exemplo prox <numInstantes>)" << endl;
            return false;
        }
        if (argumentos.empty()) porximoInstantes();
        else {
            porximoInstantes(stoi(argumentos[0]));
        }
        return true;
    } else if (comando == "saves") {
        if (argumentos.size() != 1) {
            cout << "Falta argumentos (exemplo saves <nomeSave>)" << endl;
            return false;
        }
        saveBuffer(argumentos[0]);
        return true;
    } else if (comando == "loads") {
        if (argumentos.size() != 1) {
            cout << "Falta argumentos (exemplo loads <nomeSave>)" << endl;
            return false;
        }
        loadBuffer(argumentos[0]);
        return true;
    } else if (comando == "lists") {
        if (argumentos.size() != 0) {
            cout << "Argumentos a mais" << endl;
            return false;
        }
        listaSaves();
        return true;
    } else if (comando == "dels") {
        if (argumentos.size() != 1) {
            cout << "Falta argumentos (exemplo dels <nomeSave>)" << endl;
            return false;
        }
        deleteSave(argumentos[0]);
        return true;
    }

    return false;
}

void Deserto::listaPrecoMercadorias() {
    cout << "Preco de venda de mercadoria: " << preço_venda_mercadoria << endl;
    cout << "Preco de compra de mercadoria: " << preço_compra_mercadoria << endl;
}

int Deserto::getMoedas() {
    return moedas;
}

void Deserto::acrescentaMoedas(int N) {
    moedas += N;

    if (moedas <= 0) {
        cout << "Sem moedas!" << endl;
        moedas = 0;
    }

    cout << "Moedas atualizadas: " << this->moedas << endl;
}

void Deserto::procuraCidadeeAdicionaBuffer() {
    for (int i = 0; i < buffer.getlinhas(); i++) {
        for (int j = 0; j < buffer.getColunas(); j++) {
            if (islower(buffer.getChar(i, j))) {
                // Verifica se é uma letra

                position posicao;
                posicao.linha = i;
                posicao.coluna = j;

                adicionaCidade(buffer.getChar(i, j), posicao);
            }
        }
    }
}

void Deserto::adicionaCidade(char c, position pos) {
    Cidade temp = Cidade(c, pos);
    cidades.push_back(temp);
}

void Deserto::procuraMontanha() {
    for (int i = 0; i < buffer.getlinhas(); i++) {
        for (int j = 0; j < buffer.getColunas(); j++) {
            if (buffer.getChar(i, j) == '+') {
                position posicao;
                posicao.linha = i;
                posicao.coluna = j;

                adicionaMontanha(posicao);
            }
        }
    }
}

void Deserto::adicionaMontanha(position pos) {
    Montanhas temp = Montanhas(pos);
    montanhas.push_back(temp);
}

void Deserto::procuraBarbaros() {
    for (int i = 0; i < buffer.getlinhas(); i++) {
        for (int j = 0; j < buffer.getColunas(); j++) {
            if (buffer.getChar(i, j) == '!') {
                position posicao;
                posicao.linha = i;
                posicao.coluna = j;

                adicionaBarbaros(posicao);
            }
        }
    }
}

void Deserto::adicionaBarbaros(position pos) {
    Barbaros temp = Barbaros(pos);
    caravanaBarbaros.push_back(temp);

}

void Deserto::procuraCaravana() {
    for (int i = 0; i < buffer.getlinhas(); i++) {
        for (int j = 0; j < buffer.getColunas(); j++) {
            if (isdigit(buffer.getChar(i, j))) {

                position posicao;
                posicao.linha = i;
                posicao.coluna = j;
                char tipo = "CM"[rand() % 2]; // Sorteia o tipo da caravana
                adicionaCaravana(tipo, posicao);
            }
        }
    }
}

int Deserto::adicionaCaravana(char c, position pos) {
   int id;
    if (c == 'M') {
        auto temp = make_unique<CaravanaMilitar>(pos);
        id = temp->getId();
        caravanas.emplace_back(move(temp));
    }
    if (c == 'C') {
        auto temp = make_unique<CaravanaComercio>(pos);
        id = temp->getId();
        
        caravanas.emplace_back(move(temp));
    }
    if (c == 'S') {
        auto temp = make_unique<CaravanaSecreta>(pos);
        id = temp->getId();
        caravanas.emplace_back(move(temp));
        //     CaravanaSecreta temp= CaravanaSecreta(pos);
        //     id = temp.getId();
        //     caravanas.emplace_back(make_unique<CaravanaSecreta>(pos));
    }
    return id;
}


void Deserto::procuraCaravanaComId(int id) {
    for (const auto &caravana: caravanas) {
        if (caravana->getId() == id)
            caravana->printCaravana();
    }
}

void Deserto::compraCaravana(char c, char tipo) {
    for (auto &cidade: cidades) {
        if (cidade.getChar() == c) {
            if (cidade.compraCaravana(tipo)) {
                int idCaravana = adicionaCaravana(toupper(tipo), cidade.getPos());
                acrescentaMoedas(-preço_caravana);
                atualizaAgua(idCaravana);
            }
        }
    }
}

void Deserto::listaCidade(char c) {
    for (auto cidade: cidades) {
        if (c == cidade.getChar()) {
            cidade.conteudoCidade();
        }
    }
    for (auto &caravana: caravanas) {
        if (verificaCoordenadas(c, caravana->getId())) {
            caravana->printCaravana();
        }
    }
}

bool Deserto::verificaCoordenadas(char c, int id) {
    position posCidade, posCaravana;
    for (auto cidade: cidades) {
        if (cidade.getChar() == c) {
            posCidade = cidade.getPos();
        }
    }
    for (auto &caravana: caravanas) {
        if (caravana->getId() == id) {
            posCaravana = caravana->getPos();
        }
    }

    if (posCaravana.coluna == posCidade.coluna && posCaravana.linha == posCidade.linha) {
        atualizaAgua(id);
        return true;
    }
    return false;
}

void Deserto::compraMercadoria(int id, int toneladas) {
    for (const auto &cidade: cidades) {
        if (verificaCoordenadas(cidade.getChar(), id)) {
            for (auto &caravana: caravanas) {
                if (caravana->getId() == id) {
                    if (caravana->getMercadoriaAtual() + toneladas <= caravana->getMercadoriaMaxima()) {
                        caravana->adicionaMercadoria(toneladas);
                        acrescentaMoedas(-(toneladas * preço_compra_mercadoria));
                    } else {
                        cout << "Nao pode adicionar mais mercadoria" << endl;
                    }
                    return;
                }
            }
        }
    }
    cout << "A caravana nao esta numa cidade" << endl;
}

void Deserto::vendeMercadoria(int id) {
    for (const auto &cidade: cidades) {
        if (verificaCoordenadas(cidade.getChar(), id)) {
            for (auto &caravana: caravanas) {
                if (caravana->getId() == id) {
                    int mercadoriaAtual = caravana->getMercadoriaAtual();
                    if (mercadoriaAtual > 0) {
                        caravana->adicionaMercadoria(-mercadoriaAtual); // Remove toda a mercadoria
                        acrescentaMoedas(mercadoriaAtual * preço_venda_mercadoria); // Calcula e adiciona as moedas
                        cout << "Mercadoria vendida com sucesso!" << endl;
                    } else {
                        cout << "A caravana nao possui mercadoria para vender." << endl;
                    }
                    return;
                }
            }
        }
    }

    cout << "A caravana nao esta numa cidade" << endl;
}

void Deserto::compraTripulantes(int id, int numTripulantes) {
    for (const auto &cidade: cidades) {
        if (verificaCoordenadas(cidade.getChar(), id)) {
            for (auto &caravana: caravanas) {
                if (caravana->getId() == id) {
                    int tripulacaoAtual = caravana->getTripulacaoAtual();
                    int tripulacaoMaxima = caravana->getTripulacaoMaxima();
                    if (tripulacaoAtual + numTripulantes <= tripulacaoMaxima) {
                        caravana->adicionaTripulacao(numTripulantes);
                        acrescentaMoedas(-(numTripulantes));
                    } else {
                        cout << "Nao pode adicionar mais tripulantes" << endl;
                    }
                    return;
                }
            }
        }
    }
    cout << "A caravana nao esta numa cidade" << endl;
}

void Deserto::atualizaAgua(int id) {
    for (auto &caravana: caravanas) {
        if (caravana->getId() == id) {
            caravana->reabasteceAgua();
        }
    }
}

void Deserto::moveCaravana(int id, string direcao) {
    for (auto &caravana: caravanas) {
        if (caravana->getId() == id) {
            position posAtual = caravana->getPos(); // Obtém a posição atual da caravana
            position novaPos = posAtual; // Cria uma nova posição para calcular o movimento


            if (direcao == "D") novaPos.coluna += 1; // Direita
            else if (direcao == "E") novaPos.coluna -= 1; // Esquerda
            else if (direcao == "C") novaPos.linha -= 1; // Cima
            else if (direcao == "B") novaPos.linha += 1; // Baixo
            else if (direcao == "CE") {
                novaPos.linha -= 1;
                novaPos.coluna -= 1;
            } // Cima-Esquerda
            else if (direcao == "CD") {
                novaPos.linha -= 1;
                novaPos.coluna += 1;
            } // Cima-Direita
            else if (direcao == "BE") {
                novaPos.linha += 1;
                novaPos.coluna -= 1;
            } // Baixo-Esquerda
            else if (direcao == "BD") {
                novaPos.linha += 1;
                novaPos.coluna += 1;
            } // Baixo-Direita
            else {
                cout << "Direcao invalida" << endl;
                return;
            }

            // Verifica se o movimento é válido
            if (verificaMovimento(novaPos.linha, novaPos.coluna)) {
                caravana->setPos(novaPos); // Atualiza a posição da caravana
                // cout << "Caravana " << id << " movida para (" << novaPos.linha << ", " << novaPos.coluna << ")." << endl;
                atualizaBuffer();

                for (auto &barbaro: caravanaBarbaros) {
                    if (!adjacente(barbaro.getPos(), novaPos)) {
                        barbaro.setComabte(false); // Reseta o combate
                    }
                }
            } else {
                cout << "Movimento invalido!" << endl;
            }
            return;
        }
    }

    cout << "Caravana com ID " << id << " nao encontrada!" << endl;
}


void Deserto::atualizaBuffer() {
    buffer.clearBuffer();
    for (auto montanha: montanhas) {
        buffer.setChar(montanha.getPos().linha, montanha.getPos().coluna, '+');
    }
    for (auto &caravana: caravanas) {
        buffer.setChar(caravana->getPos().linha, caravana->getPos().coluna, '0' + caravana->getId());
    }
    for (auto barbaro: caravanaBarbaros) {
        buffer.setChar(barbaro.getPos().linha, barbaro.getPos().coluna, '!');
    }
    for (auto cidade: cidades) {
        buffer.setChar(cidade.getPos().linha, cidade.getPos().coluna, cidade.getChar());
    }
    for (auto &item: itens) {
        buffer.setChar(item->getPos().linha, item->getPos().coluna, '?');
    }

}

bool Deserto::verificaMovimento(int linha, int coluna) {
    if (linha < 0 || coluna > buffer.getColunas() || coluna < 0 || linha >= buffer.getlinhas()) {
        return false;
    }
    for (auto montanha: montanhas) {
        if (montanha.getPos().linha == linha && montanha.getPos().coluna == coluna) return false;
    }
    for (auto cidade: cidades) {
        if (cidade.getPos().linha == linha && cidade.getPos().coluna == coluna) return true;
        // Permitir varias caravanas em cidades
    }
    for (auto &caravana: caravanas) {
        if (caravana->getPos().linha == linha && caravana->getPos().coluna == coluna) {
            // cout<<"vai contra outra caravana"<<endl;
            return false;
        }
    }
    return true;
}

void Deserto::ativarAutomove(int id) {
    for (auto &caravana: caravanas) {
        if (caravana->getId() == id) {
            caravana->changeAutoMoveTrue();
            std::cout << "Caravana " << id << " agora se move automaticamente: " << caravana->getAutomove() <<
                    std::endl;
            return;
        }
    }
}

void Deserto::desativarAutomove(int id) {
    for (auto &caravana: caravanas) {
        if (caravana->getId() == id) {
            caravana->changeAutoMoveFalse();
            std::cout << "Caravana " << id << " agora se move a seu pedido: " << caravana->getAutomove() << std::endl;
            return;
        }
    }
}

void Deserto::atualizaCaravana() {
    // vector<string> direcoes = {"D", "E", "C", "B", "CE", "CD", "BE", "BD"};
    for (auto it = caravanas.begin(); it != caravanas.end(); ++it){
    // for (auto &caravana: caravanas) {

        //comercial--procura outra caravana e apanha itens num raio de 2 posições
        if ((*it)->getAutomove() && (*it)->getTipo() == 'C') {
            position posCaravana = (*it)->getPos();
            bool moved = false;

            for (const auto &item : itens) {
                if (item) { // Verifica se o unique_ptr não é nulo
                    position posItem = item->getPos();
                    int distanciaLinha = abs(posItem.linha - posCaravana.linha);
                    int distanciaColuna = abs(posItem.coluna - posCaravana.coluna);

                    if (distanciaLinha <= 2 && distanciaColuna <= 2) {
                        if (posItem.linha > posCaravana.linha) {
                            moveCaravana((*it)->getId(), "B");
                        } else if (posItem.linha < posCaravana.linha) {
                            moveCaravana((*it)->getId(), "C");
                        } else if (posItem.coluna > posCaravana.coluna) {
                            moveCaravana((*it)->getId(), "D");
                        } else if (posItem.coluna < posCaravana.coluna) {
                            moveCaravana((*it)->getId(), "E");
                        }
                        moved = true;
                        break; // Sai do loop de itens após mover em direção a um item
                    }
                }
            }

            // Tenta se aproximar de outra caravana se não tiver movido para um item
            if (!moved) {
                for (const auto &outraCaravana : caravanas) {
                    if (outraCaravana->getId() != (*it)->getId()) {
                        position posOutraCaravana = outraCaravana->getPos();

                        if (adjacente(posCaravana, posOutraCaravana)) {
                            // Já está próximo; não é necessário mover
                            moved = true;
                            break;
                        }

                        // Move-se na direção da outra caravana
                        if (!moved) {
                            if (posOutraCaravana.linha > posCaravana.linha) {
                                moveCaravana((*it)->getId(), "B");
                                moved = true;
                            } else if (posOutraCaravana.linha < posCaravana.linha) {
                                moveCaravana((*it)->getId(), "C");
                                moved = true;
                            } else if (posOutraCaravana.coluna > posCaravana.coluna) {
                                moveCaravana((*it)->getId(), "D");
                                moved = true;
                            } else if (posOutraCaravana.coluna < posCaravana.coluna) {
                                moveCaravana((*it)->getId(), "E");
                                moved = true;
                            }
                        }
                    }
                }
            }
        }
        //militar -- procura uma barbara a 6 posições senão fica parada
        if ((*it)->getAutomove() && (*it)->getTipo() == 'M') {
            position posAtual = (*it)->getPos();
            position novaPos = posAtual;
            position alvoBarbaro;
            int distanciaMinima = 9999;
            bool encontrouBarbaro = false;

            // Procura pelo bárbaro mais próximo dentro do alcance
            for (auto &barbaro : caravanaBarbaros) {
                position posBarbaro = barbaro.getPos();
                int distanciaLinha = abs(posAtual.linha - posBarbaro.linha);
                int distanciaColuna = abs(posAtual.coluna - posBarbaro.coluna);

                if ((distanciaLinha <= 6 && distanciaColuna == 0) || (distanciaColuna <= 6 && distanciaLinha == 0)) {
                    int distanciaTotal = distanciaLinha + distanciaColuna;
                    if (distanciaTotal < distanciaMinima) {
                        alvoBarbaro = posBarbaro;
                        distanciaMinima = distanciaTotal;
                        encontrouBarbaro = true;
                    }
                }
            }

            // Movimento para perseguir o bárbaro
            if (encontrouBarbaro && distanciaMinima > 1) {
                if (posAtual.linha < alvoBarbaro.linha) {
                    novaPos.linha += 1; // Move para baixo
                } else if (posAtual.linha > alvoBarbaro.linha) {
                    novaPos.linha -= 1; // Move para cima
                } else if (posAtual.coluna < alvoBarbaro.coluna) {
                    novaPos.coluna += 1; // Move para a direita
                } else if (posAtual.coluna > alvoBarbaro.coluna) {
                    novaPos.coluna -= 1; // Move para a esquerda
                }

                if (verificaMovimento(novaPos.linha, novaPos.coluna)) {
                    (*it)->setPos(novaPos);
                    atualizaBuffer();
                }
            }
        }

        // caravana comercio(sem tripulantes)---move-se de forma aleatória e passados 5 instantes a caravana desaparece.
        if ((*it)->getTripulacaoAtual()==0 && (*it)->getTipo() == 'C' ) {
                int randomIndex = rand() % direcoes.size();
                moveCaravana((*it)->getId(), direcoes[randomIndex]);
                (*it)->alteraInstantes();
                if ((*it)->getInstantes()==0) removeCaravana((*it)->getId());

        }

        //caravana militar(sem tripulantes)---sempre na direçao do ultimo movimento e desaparece 7 instantes depois.
        if ((*it)->getTripulacaoAtual()==0 && (*it)->getTipo() == 'M' ) {
            (*it)->alteraInstantes();
            if ((*it)->getInstantes()==0) removeCaravana((*it)->getId());
        }



        (*it)->gastaAgua();
        (*it)->setMovimentos();
    }
    verificaTempestade();
    int randomIndex = rand() % direcoes.size();
    moveBarbaro(direcoes[randomIndex]);
}

void Deserto::moveBarbaro(string direcao) {
    for (auto &barbaro: caravanaBarbaros) {
        position posAtual = barbaro.getPos(); // Obtém a posição atual da caravana
        position novaPos = posAtual; // Cria uma nova posição para calcular o movimento

        position alvoCaravana;
        bool encontrouCaravana = false;
        int distanciaMinima = 99999;

        for (const auto &caravana: caravanas) {
            position posCaravana = caravana->getPos();
            int distanciaLinha = abs(posAtual.linha - posCaravana.linha);
            int distanciaColuna = abs(posAtual.coluna - posCaravana.coluna);

            int distanciaTotal = distanciaColuna + distanciaLinha;
            if (distanciaTotal <= 8) {
                if (distanciaTotal < distanciaMinima) {
                    alvoCaravana = posCaravana;
                    distanciaMinima = distanciaTotal;
                    encontrouCaravana = true;
                }
            }
        }
        if (distanciaMinima > 1) {
            if (encontrouCaravana) {
                // cout << "encontra caravana" << endl;
                if (posAtual.linha < alvoCaravana.linha) {
                    novaPos.linha += 1; // Move para baixo
                } else if (posAtual.linha > alvoCaravana.linha) {
                    novaPos.linha -= 1; // Move para cima
                } else if (posAtual.coluna < alvoCaravana.coluna) {
                    novaPos.coluna += 1; // Move para a direita
                } else if (posAtual.coluna > alvoCaravana.coluna) {
                    novaPos.coluna -= 1; // Move para a esquerda
                }
            } else {
                if (direcao == "D") novaPos.coluna += 1; // Direita
                else if (direcao == "E") novaPos.coluna -= 1; // Esquerda
                else if (direcao == "C") novaPos.linha -= 1; // Cima
                else if (direcao == "B") novaPos.linha += 1; // Baixo
                else if (direcao == "CE") {
                    novaPos.linha -= 1;
                    novaPos.coluna -= 1;
                } // Cima-Esquerda
                else if (direcao == "CD") {
                    novaPos.linha -= 1;
                    novaPos.coluna += 1;
                } // Cima-Direita
                else if (direcao == "BE") {
                    novaPos.linha += 1;
                    novaPos.coluna -= 1;
                } // Baixo-Esquerda
                else if (direcao == "BD") {
                    novaPos.linha += 1;
                    novaPos.coluna += 1;
                } // Baixo-Direita
                else {
                    cout << "Direacao invalida!" << endl;
                    return;
                }
            }
        }


        if ((verificaMovimento(novaPos.linha, novaPos.coluna))) {
            barbaro.setPos(novaPos);
            atualizaBuffer();
            for (const auto &caravana: caravanas) {
                if (adjacente(novaPos, caravana->getPos())) {
                    barbaro.setComabte(true);
                    combate(barbaro, *caravana);

                    // cout << "Barbaro esta adjacente a uma caravana!" << endl;

                    break;
                }
            }
        } else {
            for (auto monntanha: montanhas) { //se a montanha estiver á frente
                if (  posAtual.linha -1 == monntanha.getPos().linha && posAtual.coluna ==monntanha.getPos().coluna) {
                    novaPos.coluna += 1;
                    novaPos.linha=posAtual.linha;
                }
            }
            if (verificaMovimento(novaPos.linha, novaPos.coluna)) {
                barbaro.setPos(novaPos);
                atualizaBuffer();
            }


        }

        barbaro.setInstantes();
        if (barbaro.getInstantes() == 0) {
            removeBarbaro(barbaro);
        }
    }
}

void Deserto::porximoInstantes(int numInstantes) {
    instantes = instantes + numInstantes;
    if (instantes%instantes_entre_novos_barbaros==0) {
        adicionaBarbaros(posAleatoria());
    }
    if (instantes%instantes_entre_novos_itens==0 && itens.size()<5) {
        adicionarItem();
    }
    if (numInstantes > 1) {
        for (int i = 0; i < numInstantes; i++) {
            atualizaCaravana();
            atualizaBuffer();
            buffer.render();
            verificarItens();
            atualizarItens();
            gameOver();
        }

    }else {
        atualizaCaravana();
        atualizaBuffer();
        verificarItens();
        atualizarItens();
        buffer.render();
        gameOver();
    }

    cout <<"instante: "<< instantes << endl;
}

int Deserto::instantes = 0;

bool Deserto::adjacente(position pos1, position pos2) {
    int distanciaLinha = abs(pos1.linha - pos2.linha);
    int distanciaColuna = abs(pos1.coluna - pos2.coluna);

    return (distanciaLinha == 1 && distanciaColuna == 0) ||
           (distanciaLinha == 0 && distanciaColuna == 1);
}

void Deserto::combate(Barbaros &barbaro, Caravana &caravana) {
    int sorteioBarbaro = rand() % barbaro.getBarbaros();
    int sorteioCaravana = rand() % caravana.getTripulacaoAtual();

    if (sorteioBarbaro > sorteioCaravana) {
        // Bárbaro vence
        cout << "O Barbaro venceu" << endl;
        int perdaBarbaro = barbaro.getBarbaros() * 0.2;
        int perdaCaravana = perdaBarbaro * 2;

        barbaro.removeTripulacao(perdaBarbaro);
        caravana.removeTripulacao(perdaCaravana);

        if (caravana.getTripulacaoAtual() <= 0) {
            removeCaravana(caravana.getId());
            barbaro.setComabte(false);
            cout << "A caravana foi destruida. Sua agua foi transferida para o barbaro." << endl;
        }
    }
    if (sorteioBarbaro < sorteioCaravana) {
        cout << "A Caravana venceu" << endl;
        combatesVencidos++;
        int perdaCaravana = caravana.getTripulacaoAtual() * 0.2;
        int perdaBarbaro = perdaCaravana * 2;

        caravana.removeTripulacao(perdaCaravana);
        barbaro.removeTripulacao(perdaBarbaro);

        if (barbaro.getBarbaros() <= 0) {
            removeBarbaro(barbaro);
            barbaro.setComabte(false);
            cout << "o barbaro foi destruido. Sua agua foi transferida para a caravana." << endl;
        }
    }
}

void Deserto::removeCaravana(int id) {
    auto it = std::remove_if(caravanas.begin(), caravanas.end(),
                             [id](const std::unique_ptr<Caravana> &ptr) {
                                 return ptr->getId() == id; // Compara o ID
                             });

    // Remove o elemento do vetor
    if (it != caravanas.end()) {
        caravanas.erase(it, caravanas.end());
        cout << "Caravana com ID " << id << " removida do deserto." << endl;
    } else {
        cout << "Caravana com ID " << id << " nao encontrada para remocao." << endl;
    }

}

void Deserto::removeBarbaro(Barbaros &barbaro) {
    for (auto it = caravanaBarbaros.begin(); it != caravanaBarbaros.end(); ++it) {
        if (&(*it) == &barbaro) {
            // Verifica se os endereços coincidem (mesmo objeto)
            caravanaBarbaros.erase(it);
            std::cout << "Barbaro removido com sucesso." << std::endl;
            return;
        }
    }
    std::cout << "Barbaro nao encontrado na lista." << std::endl;
}


void Deserto::saveBuffer(string &nome) {
    if (bufferGuardados.find(nome)!=bufferGuardados.end()) {
        cout<<"ja existe uma copia com esse nome"<<endl;
    }
    bufferGuardados.insert(make_pair(nome,buffer));
    cout<<"copia guardada"<<endl;

}

void Deserto::loadBuffer(string &nome) {
    auto it = bufferGuardados.find(nome);
    if (it == bufferGuardados.end()) {
        cout << " Nao existe nenhuma copia com esse nome " <<endl;
    }
    Buffer temp = it->second;

    temp.render();
}

void Deserto::listaSaves() {
    if (bufferGuardados.empty()) {
        cout<<"Nao existem copias guardadas"<<endl;
    }
    else {
        cout<<"Lista de Saves----------"<<endl;
        for (auto save: bufferGuardados) {
            cout<<save.first<<endl;

        }
    }
}

void Deserto::deleteSave(string &nome) {
    if (bufferGuardados.erase(nome)) {
        cout<<"Copia apagada"<<endl;
    }else{
    cout<<"Nao existe nenhuma copia com esse nome"<<endl;
    }
}



void Deserto::pontuacao() {
    cout << "Pontuacao final:" << endl;
    cout<<"Numero de instantes decorridos: "<<instantes<<endl;
    cout<<"Numero de combates vencidos: "<<combatesVencidos<<endl;
    cout<<"Numero de moedas que sobram: "<<moedas<<endl;
    cout << "Regresso a fase 1\n";
    instantes=0;
    combatesVencidos=0;
    cidades.clear();
    montanhas.clear();
    bufferGuardados.clear();
    posTempestadeAreia.clear();
    itens.clear();
    caravanaBarbaros.clear();
    caravanas.clear();
}


void Deserto::tempestadeAreia(int linha, int coluna, int raio) {
    posTempestadeAreia.clear(); //limpar posições de outras tempestades

    for (int i = linha - raio; i <= linha + raio; ++i) {
        for (int j = coluna - raio; j <= coluna + raio; ++j) {
            posTempestadeAreia.push_back({i, j});
        }
    }
}


//teho q usar um iterador explicito pois da outra maneira não atualiza o ponteiro e tenta acessar a memoria invalida (quando apago caravanas...)
void Deserto::verificaTempestade() {
    for (auto it = caravanas.begin(); it != caravanas.end(); ++it) {
        position posCaravana = (*it)->getPos();


        for (const auto &pos : posTempestadeAreia) {
            if (posCaravana.coluna == pos.coluna && posCaravana.linha == pos.linha) {
                danoTempestade(**it);
            }
        }
    }
    for (auto itB = caravanaBarbaros.begin(); itB != caravanaBarbaros.end(); ++itB) {
        position posCaravana = (*itB).getPos();


        for (const auto &pos : posTempestadeAreia) {
            if (posCaravana.coluna == pos.coluna && posCaravana.linha == pos.linha) {
                danoTempestadeB(*itB);
            }
        }
    }
    posTempestadeAreia.clear();
}
void Deserto::danoTempestadeB(Barbaros &barbaro) {
    int chanceSobreviver=75;
    int random=rand()%100+1;
    if (random>chanceSobreviver) {
        cout<<"A caravana de barbaros foi destruida por uma tempestade"<<endl;
        removeBarbaro(barbaro);
    }else {
        int perdeTrip=barbaro.getBarbaros()* 0.10;
        barbaro.removeTripulacao(perdeTrip);
        cout<<"A caravana de barbaros sobreviveu mas so sobra "<<barbaro.getBarbaros()<<" tripulantes"<<endl;
    }

}
void Deserto::danoTempestade(Caravana &caravana) {
    if (caravana.getTipo()=='C') {
        int cargaMaxima=caravana.getMercadoriaMaxima();
        int cargaOcupada=caravana.getMercadoriaAtual();

        float percentagemOcupada =(float)cargaOcupada/cargaMaxima*100;
        int chanceSobreviver;
        if (percentagemOcupada>50) {
            chanceSobreviver=50;
        }
        else {
            chanceSobreviver=75;
        }
        int random=rand()%100+1;
        if (random>chanceSobreviver) {
            cout<<"A caravana "<<caravana.getId()<<" foi destruida por uma tempestade"<<endl;
            removeCaravana(caravana.getId());
        } else {
            int perdeCarga=cargaOcupada* 0.25;
            caravana.adicionaMercadoria(-perdeCarga);
            cout<<"A caravana "<<caravana.getId()<< " sobreviveu mas so sobra "<<caravana.getMercadoriaAtual()<<" toneladas de mercadoria"<<endl;
        }
    }else if (caravana.getTipo()=='M') {
        int chanceSobreviver=66;
        int random=rand()%100+1;
        if (random>chanceSobreviver) {
            cout<<"A caravana "<<caravana.getId()<<" foi destruida por uma tempestade"<<endl;
            removeCaravana(caravana.getId());
        }else {
            int perdeTrip=caravana.getTripulacaoAtual()* 0.10;
            caravana.removeTripulacao(perdeTrip);
            cout<<"A caravana "<<caravana.getId()<< " sobreviveu mas so sobra "<<caravana.getTripulacaoAtual()<<" tripulantes"<<endl;
        }
    }

}

position Deserto::posAleatoria() {
    position posAleatoria;

    do {

        posAleatoria.linha = rand() % buffer.getlinhas();
        posAleatoria.coluna = rand() % buffer.getColunas();
    } while (!verificaMovimento(posAleatoria.linha, posAleatoria.coluna));  // Verifica se a posição é válida


    return posAleatoria;
}

void Deserto::adicionarItem() {
    if (itens.size() >= 5) return; // Não adiciona mais de 5 itens

    position pos=posAleatoria();


    int tipo = rand() % 4; // Sorteia o tipo do item
     // int tipo=3;
    switch (tipo) {
        case 0: {
            auto temp = make_unique<CaixaPandora>(pos,20);
            itens.emplace_back(move(temp));
            break;
        }
        case 1: {
            auto temp = make_unique<ArcaTesouro>(pos,20);
            itens.emplace_back(move(temp));
            break;
        }
        case 2: {
            auto temp = make_unique<Jaula>(pos,20);
            itens.emplace_back(move(temp));
            break;
        }
        case 3: {
            auto temp = make_unique<Mina>(pos,20);
            itens.emplace_back(move(temp));
            break;
        }
        case 4: {
            auto temp = make_unique<Poco>(pos,20);
            itens.emplace_back(move(temp));
            break;
        }
    }
}

void Deserto::verificarItens() {
    for (auto itC = caravanas.begin(); itC != caravanas.end(); ++itC) {
        position posCaravana = (*itC)->getPos();
        for (auto itI = itens.begin(); itI != itens.end(); ) {
            if (adjacente(posCaravana, (*itI)->getPos())) {
                (*itI)->efeito(**itC,*this); // Aplica o efeito do item
                itI = itens.erase(itI); // Remove o item após ser apanhado
            } else {
                ++itI;
            }
        }
    }
}

void Deserto::atualizarItens() {
    for (auto it = itens.begin(); it != itens.end(); ) {
        (*it)->instantesRestantes();

        if ((*it)->getInstantes() == 0) {
            it = itens.erase(it); // Remove itens expirados
        } else {
            ++it;
        }
    }
}

void Deserto::gameOver() {
    if (caravanas.empty() && moedas<preço_caravana) {
        cout<<"Ficou sem caravanas e sem dinheiro para comprar mais!!!\n"<<endl;
        pontuacao();

    }
}
