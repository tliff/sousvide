#ifndef DISPLAY_HPP_67B93B5A
#define DISPLAY_HPP_67B93B5A

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

namespace SousVide {
  class Display{
    LiquidCrystal_I2C* lcd;
    unsigned long lastUpdatedAt;
    unsigned char lines[2][17];
  public:
    Display(){
      lcd = new LiquidCrystal_I2C(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
      lcd->begin(16,2);
      lcd->backlight();
    }
    
    void setContent(String first, String second){
      first.getBytes(lines[0], 17);
      second.getBytes(lines[1], 17);
    }
        
    void update(){
      if((unsigned long)(millis() - lastUpdatedAt) >= 100) {
        lastUpdatedAt = millis();
        lcd->home();                   // go home
        lcd->print(String((char*)lines[0]));  
        lcd->setCursor ( 0, 1 );        // go to the next line
        lcd->print(String((char*)lines[1]));      
      }
    }
  };
  
}

#endif /* end of include guard: DISPLAY_HPP_67B93B5A */
