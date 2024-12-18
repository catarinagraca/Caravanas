//
// Created by catar on 17/12/2024.
//

#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <string>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>

using namespace std;

class Buffer {
private:
    char mapa[100][100];
    int linha, coluna;
public:

    Buffer() : linha(0), coluna(0) {}

    void setDimensions(int linhas, int colunas);
    void setChar(int row, int col, char c);
    void render() const;
    char getChar(int row, int col) const;
    int getlinhas();
    int getColunas();


};




#endif //BUFFER_H
