#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

// Quantidade de colunas (baseada na largura da tela)
#define COLS 40

int y[COLS];
int speed[COLS];

void setup() {
  pinMode(4, OUTPUT);      // backlight
  digitalWrite(4, HIGH);   // liga a tela

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextSize(1);

  randomSeed(analogRead(0));

  // Inicializa colunas
  for (int i = 0; i < COLS; i++) {
    y[i] = random(-100, 0);
    speed[i] = random(2, 8);
  }
}

void loop() {
  // efeito de "fade" (rastro)
  tft.fillScreen(TFT_BLACK);

  int colWidth = tft.width() / COLS;

  for (int i = 0; i < COLS; i++) {
    int x = i * colWidth + colWidth / 2;

    // desenha pontinho
    tft.fillCircle(x, y[i], 2, TFT_GREEN);

    // move para baixo
    y[i] += speed[i];

    // reinicia quando sai da tela
    if (y[i] > tft.height()) {
      y[i] = random(-50, 0);
      speed[i] = random(2, 8);
    }
  }

  delay(30); // controla velocidade geral
}
