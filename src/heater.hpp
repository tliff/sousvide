#ifndef HEATER_HPP_0AF225F7
#define HEATER_HPP_0AF225F7

namespace SousVide {
  class Heater{
    int pin;    
    
  public:
    Heater(int pin){
      this->pin = pin;
      pinMode(this->pin, OUTPUT);
      disable();
    }
    
    void enable(){
      digitalWrite(pin, LOW);
    }
    
    void disable(){
      digitalWrite(pin, HIGH);
    }
    
  };
}

#endif /* end of include guard: HEATER_HPP_0AF225F7 */
