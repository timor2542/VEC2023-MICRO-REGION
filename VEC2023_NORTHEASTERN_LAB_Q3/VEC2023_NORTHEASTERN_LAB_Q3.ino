
#include <Adafruit_NeoPixel.h>
#include <TFT_eSPI.h>  // Hardware-specific library

TFT_eSPI tft;  // Invoke custom library

#define PIN D0
#define NUMPIXELS 12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define WHITE pixels.Color(255, 255, 255)
#define RED pixels.Color(255, 0, 0)
#define YELLOW pixels.Color(255, 255, 0)
#define GREEN pixels.Color(0, 255, 0)
#define SKYBLUE pixels.Color(0, 255, 255)
#define BLUE pixels.Color(0, 0, 255)
#define PURPLE pixels.Color(255, 0, 255)
#define OFF pixels.Color(0, 0, 0)

int color_choice[7] = { WHITE, RED, YELLOW, GREEN, SKYBLUE, BLUE, PURPLE };
String direction[2] = { "CW", "CCW" };
String pattern[2] = { "DEFAULT", "INVERT" };
String text_color_choice[7] = { "WHITE", "RED", "YELLOW", "GREEN", "SKYBLUE", "BLUE", "PURPLE" };
int tft_text_color[7] = { TFT_WHITE, TFT_RED, TFT_YELLOW, TFT_GREEN, TFT_CYAN, TFT_BLUE, TFT_MAGENTA };

int i = 0;
int icolor = 0;
int isCCW = 0;
int invert_pattern = 0;

void setup() {

  pinMode(WIO_KEY_C, INPUT_PULLUP);
  pinMode(WIO_KEY_B, INPUT_PULLUP);
  pinMode(WIO_KEY_A, INPUT_PULLUP);

  tft.begin();
  tft.setRotation(3);
  tft.setTextSize(3);
  tft.fillScreen(TFT_BLACK);

  tft.drawString("DIRECTION:", 10, 50);
  tft.drawString("PATTERN:", 10, 100);
  tft.drawString("COLOR:", 10, 150);

  pixels.begin();  // This initializes the NeoPixel library.
  pixels.setBrightness(10);
  pixels.show();
}

void loop() {
  if (digitalRead(WIO_KEY_C) == LOW) {
    while (digitalRead(WIO_KEY_C) == LOW) { delay(200); }
    isCCW ^= 1;
  }

  if (digitalRead(WIO_KEY_B) == LOW) {
    while (digitalRead(WIO_KEY_B) == LOW) { delay(200); }
    invert_pattern ^= 1;
  }

  if (digitalRead(WIO_KEY_A) == LOW) {
    while (digitalRead(WIO_KEY_A) == LOW) { delay(200); }
    icolor++;
    if (icolor > 6) { icolor = 0; }
  }

  if (isCCW) {
    i--;
  } else {
    i++;
  }

  if (i < 0) { i = NUMPIXELS - 1; }
  if (i > NUMPIXELS - 1) { i = 0; }

  tft.drawString(String(direction[isCCW]) + "   ", 200, 50);
  tft.drawString(String(pattern[invert_pattern]) + "   ", 180, 100);

  tft.setTextColor(tft_text_color[icolor], TFT_BLACK); // (Text Color, Text Background Color)
  tft.drawString(String(text_color_choice[icolor]) + "   ", 180, 150);
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // (Text Color, Text Background Color)

  if (invert_pattern) {
    for (int j = 0; j < NUMPIXELS; j++) {
      pixels.setPixelColor(j, color_choice[icolor]);
    }
    pixels.setPixelColor(i, OFF);
    pixels.show();
  } else {
    for (int j = 0; j < NUMPIXELS; j++) {
      pixels.setPixelColor(j, OFF);
    }
    pixels.setPixelColor(i, color_choice[icolor]);
    pixels.show();
  }
  delay(150);
}
