#ifndef MATRIZ_BRAILLE_H
#define MATRIZ_BRAILLE_H
 
#include <vector>
#include <Arduino.h> 
struct Par {
  bool a;
  bool b;
};

std::vector<std::vector<Par>> montarMatriz(const std::vector<String>& combinacaoFinal);
 
#endif
 
