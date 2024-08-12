#include "GPIO_DEAKIN.h"

// instance of GPIO_DEAKIN class
GPIO_DEAKIN gp;
float duration = 20000;
char pins[] = {2,4,5,6,7,18};
char pattern = 0b00100100;
void setup() {
}

void loop() {
  gp.GPIO_ON_OFF(pins, duration);
  // gp.GPIO_Display_Pattern(pins, pattern);
}
