#include "matriz_braille.h"
#include <algorithm>

std::vector<std::vector<Par>> montarMatriz(const std::vector<String>& combinacaoFinal) {

  std::vector<Par> fileira1; // pontos (0,3)
  std::vector<Par> fileira2; // pontos (1,4)
  std::vector<Par> fileira3; // pontos (2,5)

  for (const String& caractere : combinacaoFinal) {
    
    bool bit5 = caractere[0] == '1';
    bool bit4 = caractere[1] == '1';
    bool bit3 = caractere[2] == '1';
    bool bit2 = caractere[3] == '1';
    bool bit1 = caractere[4] == '1';
    bool bit0 = caractere[5] == '1';

    fileira1.push_back({bit0, bit3});
    fileira2.push_back({bit1, bit4});
    fileira3.push_back({bit2, bit5});
  }

  std::vector<std::vector<Par>> matriz = { fileira1, fileira2, fileira3 };

  //espelhar as fileiras de índice ímpar

  for (size_t i = 0; i < matriz.size(); i++) {
    if (i % 2 == 1) {
      // inverte a ordem dos caracteres dentro da fileira
      std::reverse(matriz[i].begin(), matriz[i].end());

      // inverte também a ordem interna de cada par,
      for (Par& par : matriz[i]) {
        std::swap(par.a, par.b);
      }
    }
  }

  return matriz;
}
