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
int pixel_color[3];
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
int color_num;
int animation_num;

void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  pixels.begin();             //pixel initialization

  color_num = random(0, 10); //randomly select first color 0-9
  animation_num = random(1, 7); //randomly select animation number 1-3
  for (int i = 0; i < 3; i++) {
    pixel_color[i] = ColorMatrix[color_num][i];
  }

  first_segment[0] = 0;     //initialization for spinny eyes
  first_segment[1] = 1;
  first_segment[2] = 2;
  first_segment[3] = 3;
  second_segment[0] = 8;
  second_segment[1] = 9;
  second_segment[2] = 10;
  second_segment[3] = 11;


}

void loop() {
  if (digitalRead(ButtonPin) == HIGH) {
    animation_num = random(1, 7); //generate random number 1-3 for which animation
    color_num = random(0, 10); //generate random number 0-9 for which color
    for (int i=0;i<16;i++){
      pixels.setPixelColor(i,pixels.Color(0,0,0));
    }
    pixels.show();
  }
  else {
    for (int m = 0; m < 3; m++) {
      pixel_color[m] = ColorMatrix[color_num][m];
    }
    switch (animation_num) {
      case 1:
        for (int i = 0; i < 16; i++) { //iterate over pixels
          if (second_segment[0] == i || second_segment[1] == i || second_segment[2] == i || second_segment[3] == i) {
            pixels.setPixelColor(i, pixels.Color(pixel_color[0], pixel_color[1], pixel_color[2]));
          }
          else if (first_segment[0] == i || first_segment[1] == i || first_segment[2] == i || first_segment[3] == i) {
            pixels.setPixelColor(i, pixels.Color(pixel_color[0], pixel_color[1], pixel_color[2]));
          }
          else {
            pixels.setPixelColor(i, pixels.Color(0, 0, 0));
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
          second_segment[3] = second_segment[2] + 1;
        }
        else if (second_segment[2] == 16) {
          first_segment[3] = first_segment[2] + 1;
          second_segment[3] = 0;
        }
        else {
          first_segment[3] = first_segment[2] + 1;
          second_segment[3] = second_segment[2] + 1;
        }
        
        break;
      case 2: { //random pixels, random colors
        int pixel_num=random(0,16);
        int onoff=random(0,2);
        if (onoff==1){
          pixels.setPixelColor(pixel_num, pixels.Color(random(0,256), random(0,256), random(0,256)));
        }
        else{
          pixels.setPixelColor(pixel_num, pixels.Color(0,0,0));
        }
        pixels.show();
        delay(40);
        break;
      }
      case 3: { //random pixels, random colors
        int pixel_num3=random(0,16);
        int onoff3=random(0,2);
        if (onoff3==1){
          pixels.setPixelColor(pixel_num3, pixels.Color(pixel_color[0], pixel_color[1], pixel_color[2]));
        }
        else{
          pixels.setPixelColor(pixel_num3, pixels.Color(0,0,0));
        }
        pixels.show();
        delay(40);
        break;
      } 
      case 4:{
        int dir=random(0,1); //o is forward 1 is backward
        for (int q=0;q<16;q++){
          pixels.setPixelColor(q, pixels.Color(pixel_color[0], pixel_color[1], pixel_color[2]));
          pixels.show();
          delay(50);
        }

        for (int p=0;p<16;p++){
          pixels.setPixelColor(p, pixels.Color(0,0,0));
          pixels.show();
          delay(50);
        }

        break;
      }
      case 5:{
        for (int j=0;j<16;j++){
          for (int i=0;i<16;i++){
            if (i==j){
              pixels.setPixelColor(i, pixels.Color(pixel_color[0], pixel_color[1], pixel_color[2]));
            }
            else{
              pixels.setPixelColor(i,pixels.Color(0,0,0));
            }
          }
          pixels.show();
          delay(40);
        }
        break;
      }
      case 6:{
        for (int j=0;j<16;j++){
          for (int i=0;i<16;i++){
            if (i==j){
              pixels.setPixelColor(i,pixels.Color(0,0,0));
            }
            else{
              pixels.setPixelColor(i, pixels.Color(pixel_color[0], pixel_color[1], pixel_color[2]));
            }
          }
          pixels.show();
          delay(40);
        }
        break;
      }
    }
  }
}



