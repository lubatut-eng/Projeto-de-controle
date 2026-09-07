#ifndef IMPRESSAO_BRAILLE_H
#define IMPRESSAO_BRAILLE_H
 
#include <vector>
#include <Arduino.h>
#include <AccelStepper.h>
#include "matriz_braille.h"

// (mover para o config.h do projeto quando for integrar)

 
//Motor X
const int PIN_X_STEP         = 18;
const int PIN_X_DIR          = 19;
const int PIN_X_FIM_DE_CURSO = 34; // switch da posição inicial (esquerda)
 
const float VELOCIDADE_MAX_X   = 800;  // passos/segundo
const float ACELERACAO_X       = 400;  // passos/segundo²
const float VELOCIDADE_HOMING_X = 200; // passos/segundo, usada só no homing
 
//Motor Y 
//Verificar encoder
const int PIN_Y_IN1          = 25;
const int PIN_Y_IN2          = 26;
const int PIN_Y_FIM_DE_CURSO = 35; // switch da posição inicial (topo)
 
const int PIN_SOLENOIDE      = 27;
 
//AJUSTAR conforme protótipo real
const int PASSOS_INTRA_CELULA      = 20; 
const int PASSOS_ENTRE_CELULAS     = 48;  
const int TEMPO_CURSO_SOLENOIDE_MS = 80;  // tempo pro solenoide bater e recolher VERIFICARPLMDS
const int TEMPO_MOVER_LINHA_MS     = 300; // tempo estimado do motor Y descer uma linha (provisório até ter feedback melhor)
 

// Chamar uma vez no setup() da main

void impressao_iniciar();

void homing();
 
void imprimirMatriz(const std::vector<std::vector<Par>>& matriz);
 
void principal(const std::vector<String>& combinacaoFinal);
 
#endif
