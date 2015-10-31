// 16-pixexl NeoPixel ring display

#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
#include <avr/power.h>
#endif

#define PixelPin 6
#define ButtonPin 7

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, PixelPin);
int first_segment[4];
int second_segment[4];
int ColorA[3];
int ColorB[3];
int ColorMatrix[10][3] = {
  {72, 118, 255},
  {75, 0, 130},
  {255, 182, 193},
  {0, 245, 255},
  {0, 255, 127},
  {34, 139, 34},
  {255, 236, 139},
  {255, 165, 0},
  {205, 38, 38},
  {255, 255, 255}
};
//colors are blue, indigo, pink, turquoise, spring green, dark green, yellow, orange, red, bright white
int color_numA, color_numB;
void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels.setBrightness(60); // 1/3 brightness
  //randomly pick starting colors
  color_numA = random(0, 10); //generate random number 0 to 9
  color_numB = random(0, 10); //generate random number 0 to 9
  for (int m = 0; m < 3; m++) {
    ColorA[m] = ColorMatrix[color_numA][m];
    ColorB[m] = ColorMatrix[color_numB][m];
  }
  first_segment[0] =0;
  first_segment[1]=1;
  first_segment[2]=2;
  first_segment[3]=3;
  second_segment[0]=8;
  second_segment[1]=9;
  second_segment[2]=10;
  second_segment[3]=11;
}

void loop() {
  if (digitalRead(ButtonPin) == HIGH) {
    //randomly pick a new color for each segment
    color_numA = random(0, 10); //generate random number 0 to 9
    color_numB = random(0, 10); //generate random number 0 to 9
    for (int m = 0; m < 3; m++) {
      ColorA[m] = ColorMatrix[color_numA][m];
      ColorB[m] = ColorMatrix[color_numB][m];
    }
  }

  for (int i = 0; i < 16; i++) { //iterate over pixels
    if (second_segment[0]==i || second_segment[1]==i ||second_segment[2]==i||second_segment[3]==i){
      pixels.setPixelColor(i, pixels.Color(ColorA[0], ColorA[1], ColorA[2]));
    }
    else if (first_segment[0]==i || first_segment[1]==i ||first_segment[2]==i||first_segment[3]==i){
      pixels.setPixelColor(i, pixels.Color(ColorA[0], ColorA[1], ColorA[2]));
    }
    else{
      //pixels.setPixelColor(i, pixels.Color(ColorB[0], ColorB[1], ColorB[2]));
      pixels.setPixelColor(i, pixels.Color(0,0,0));
    }
  }
  pixels.show();
  delay(50);
  for (int k = 0; k < 3; k++) { //rotate segment arrays forward by one
    first_segment[k] = first_segment[k + 1];
    second_segment[k] = second_segment[k + 1];
  }

  if (first_segment[2] == 16) { //make sure that we loop back to one when we reach 16
    first_segment[3] = 0;
  }
  else {
    first_segment[3] = first_segment[2] + 1;
  }

  if (second_segment[2] == 16) { //make sure we loop back to 1 when we reach 16
    second_segment[3] = 0;
  }
  else {
    second_segment[3] = second_segment[2] + 1;
  }


}

