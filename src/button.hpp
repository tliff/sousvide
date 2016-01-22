#ifndef BUTTON_HPP_1D33BE5C
#define BUTTON_HPP_1D33BE5C
#include <Arduino.h>


enum Press {
  PRESS_UP,
  PRESS_DOWN,
  PRESS_ON,
  PRESS_OFF
};

namespace SousVide {
  class SousVide;
  class Button {
    int pin;
    Press press;
    SousVide* o;
    int state = HIGH;
  public:
    Button(SousVide* o, int pin, Press press);
    void update();
  };  
  
}


#endif /* end of include guard: BUTTON_HPP_1D33BE5C */
