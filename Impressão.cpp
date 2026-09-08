#include "impressao_braille.h"

static AccelStepper motorX(AccelStepper::DRIVER, PIN_X_STEP, PIN_X_DIR);

static void ligarMotorY(bool direcaoDescer) {
  if (direcaoDescer) {
    digitalWrite(PIN_Y_IN1, HIGH);
    digitalWrite(PIN_Y_IN2, LOW);
  } else {
    digitalWrite(PIN_Y_IN1, LOW);
    digitalWrite(PIN_Y_IN2, HIGH);
  }
}

static void pararMotorY() {
  digitalWrite(PIN_Y_IN1, LOW);
  digitalWrite(PIN_Y_IN2, LOW);
}

//VERIFICAR SE O RELE QUE TEMOS FUNCIONA ASSIM
static void acionarSolenoide() {
  digitalWrite(PIN_SOLENOIDE, HIGH);
  delay(TEMPO_CURSO_SOLENOIDE_MS);
  digitalWrite(PIN_SOLENOIDE, LOW);
}

static void moverMotorXPassos(int quantidadePassos) {
  motorX.move(quantidadePassos); // define destino relativo
  while (motorX.distanceToGo() != 0) {
    motorX.run(); // avança um micro-passo por chamada, respeitando aceleração
  }
}


void impressao_iniciar() {
  pinMode(PIN_X_FIM_DE_CURSO, INPUT_PULLUP);
  pinMode(PIN_Y_FIM_DE_CURSO, INPUT_PULLUP);
  pinMode(PIN_Y_IN1, OUTPUT);
  pinMode(PIN_Y_IN2, OUTPUT);
  pinMode(PIN_SOLENOIDE, OUTPUT);

  digitalWrite(PIN_SOLENOIDE, LOW);
  pararMotorY();

  motorX.setMaxSpeed(VELOCIDADE_MAX_X);
  motorX.setAcceleration(ACELERACAO_X);
}


void homing() {
  ligarMotorY(false); 
  while (digitalRead(PIN_Y_FIM_DE_CURSO) == LOW) {
  }
  pararMotorY();
  
  motorX.setSpeed(-VELOCIDADE_HOMING_X);
  while (digitalRead(PIN_X_FIM_DE_CURSO) == LOW) {
    motorX.runSpeed(); 
  }

  motorX.setCurrentPosition(0);
}


void imprimirMatriz(const std::vector<std::vector<Par>>& matriz) {

  homing();

  for (size_t indiceFileira = 0; indiceFileira < matriz.size(); indiceFileira++) {

    if (indiceFileira > 0) {
      ligarMotorY(true);
      delay(TEMPO_MOVER_LINHA_MS); 
      pararMotorY();
    }

    const std::vector<Par>& fileiraAtual = matriz[indiceFileira];

    for (size_t indicePar = 0; indicePar < fileiraAtual.size(); indicePar++) {
      const Par& par = fileiraAtual[indicePar];

      if (par.a) {
        acionarSolenoide();
      }
      moverMotorXPassos(PASSOS_INTRA_CELULA);

      if (par.b) {
        acionarSolenoide();
      }

      bool temProximaCelula = (indicePar + 1) < fileiraAtual.size();
      if (temProximaCelula) {
        moverMotorXPassos(PASSOS_ENTRE_CELULAS);
      }
    }
  }

  homing(); // recolhe tudo pro início, pronto pra próxima impressão =)
}


void principal(const std::vector<String>& combinacaoFinal) {
  std::vector<std::vector<Par>> matriz = montarMatriz(combinacaoFinal);
  imprimirMatriz(matriz);
}
