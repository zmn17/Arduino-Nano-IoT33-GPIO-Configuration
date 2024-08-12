#include "TIMER_DEAKIN.h"

#define HIGH true
#define LOW false

class GPIO_DEAKIN {
  volatile PortGroup *portA = &PORT->Group[0];
  volatile PortGroup *portB = &PORT->Group[1];

public:
  bool Config_GPIO(char PortNum, char PinNum, String Mode) {
    if (PortNum == 'A') {
      if (Mode == "OUTPUT") {
        portA->DIR.reg |= (1 << PinNum);
        return true;
      } else {
        portA->DIR.reg &= ~(1 << PinNum);
        return false;
      }
    } else if (PortNum == 'B') {
      if (Mode == "OUTPUT") {
        portB->DIR.reg |= 1 << PinNum;
        return true;
      } else {
        portB->DIR.reg &= ~(1 << PinNum);
        return false;
      }
    }
    return false;
  }
  bool Write_GPIO(char PortNum, char PinNum, bool state) {
    if (PortNum == 'A') {
      if (state == HIGH) {
        portA->OUT.reg |= 1 << PinNum;
        return true;
      } else if (state == LOW) {
        portA->OUT.reg &= ~(1 << PinNum);
        return false;
      }
    } else if (PortNum == 'B') {
      if (state == HIGH) {
        portB->OUT.reg |= 1 << PinNum;
        return true;
      } else if (state == LOW) {
        portB->OUT.reg &= ~(1 << PinNum);
        return false;
      }
    }
    return false;
  }
  bool Read_GPIO(char PortNum, char PinNum) {
    uint32_t pinMask = (1 << PinNum);
    if (PortNum == 'A') {
      if (portA->IN.reg & pinMask)
        return true;
      else
        return false;
    } else if (PortNum == 'B') {
      if (portB->IN.reg & pinMask)
        return true;
      else
        return false;
    }
    return false;
  }
  void GPIO_Display_Pattern(char *PinArray, char GPIOPattern) {
    // 1. Set the DIRTGL register of each pin to toggle to OUTPUT
    int size = 6;
    for (int i = 0; i < size; i++) {
        portA->DIR.reg |= (1 << *(PinArray + i));
    }

    // 2. Toggle the OUTTGL register of the pin according to the pattern
    for (int i = 0; i < size; i++) {
        int bit = (GPIOPattern >> i) & 1;  // Correct bit extraction
        if (bit == 1) {
            portA->OUTTGL.reg |= (1 << *(PinArray + i));
        }
    }
  }
 void GPIO_ON_OFF(char *PinArray, float duration){
    TIMER_DEAKIN timer;
    int size = 6;
    // set the DIR registers
    for(int i = 0; i <= size - 1; i++){
      portA->DIR.reg |= (1 << *(PinArray + i));
    }

    // Turn on the LEDs sequentially
    for (int i = 0; i <= size - 1; i++) {
        portA->OUTTGL.reg |= (1 << *(PinArray + i));
        timer.wait(duration);
    }

    // Turn off the LEDs in reverse order
    for (int i = size - 1; i > 0; i--) {
        portA->OUTTGL.reg |= (1 << *(PinArray + i));
        timer.wait(duration);
    }
  }
};
