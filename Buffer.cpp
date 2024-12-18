//
// Created by catar on 17/12/2024.
//

#include "Buffer.h"
// Define as dimensões do buffer
  void Buffer::setDimensions(int linhas, int colunas) {
      linha = linhas;
      coluna = colunas;
  }

// Preenche o buffer com o conteúdo do mapa
void Buffer::setChar(int row, int col, char c) {
      if (row >= 0 && row <= linha && col >= 0 && col < coluna) {
          mapa[row][col] = c;  // Armazena o caractere na posição especificada
      }
  }

char Buffer::getChar(int row, int col) const {
      return mapa[row][col];
  }

// Renderiza o conteúdo do buffer no terminal
void Buffer::render() const {
      for (int i = 0; i < linha; ++i) {
          for (int j = 0; j < coluna; ++j) {
              cout << mapa[i][j];  // Exibe cada caractere
          }
          cout << '\n';
      }
  }


int Buffer::getlinhas() {
    return linha;
}
 int Buffer::getColunas() {
     return coluna;
 }
