#ifndef SOUS_VIDE_HPP_8031BC2C
#define SOUS_VIDE_HPP_8031BC2C
#include <Arduino.h>
#include "temperature_sensor.hpp"
#include "heater.hpp"
#include "display.hpp"
#include "button.hpp"

#define ONE_WIRE_BUS 2
#define RELAY_PIN 12
#define DOWN_BUTTON 10
#define UP_BUTTON 11


namespace SousVide {
  class SousVide {
    TemperatureSensor* temperatureSensor;
    Display* display;
    Heater* heater;
    float targetTemperature = 60.0;
    Button* upButton;
    Button* downButton;
  public:
    SousVide(){
    }
    
    void setup(){
      Serial.begin(9600);
      heater = new Heater(RELAY_PIN);
      display = new Display();
      display->setContent("Initializing", "");
      temperatureSensor = new TemperatureSensor(ONE_WIRE_BUS);
      upButton = new Button(this, DOWN_BUTTON, PRESS_UP);
      downButton = new Button(this, UP_BUTTON, PRESS_DOWN);
    }
    
    void loop(){
      temperatureSensor->update();
      display->update();
      upButton->update();
      downButton->update();
      logic();
    }
    
    void up(){
      if(targetTemperature < 89.5){
        targetTemperature += 0.5;
      }
    }
    
    void send(Press press){
      switch(press){
        case PRESS_UP:
        up();
        break;
        case PRESS_DOWN:
        down();
        break;
        default:
        break;
      }
    }
    
    void down(){
      if(targetTemperature > 10.5){
        targetTemperature -= 0.5;
      }
    }

    void logic(){
      if(temperatureSensor->temperatureAvailable()){
        display->setContent(String(temperatureSensor->getFloating())+ "   " + String(targetTemperature), "On  Off Down Up ");
        if(temperatureSensor->getFloating() > targetTemperature){
          heater->disable();
        }
        else{
          heater->enable();
        }
      }
    }

  };
}

#endif /* end of include guard: SOUS_VIDE_HPP_8031BC2C */
