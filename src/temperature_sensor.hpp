#ifndef TEMPERATURE_SENSOR_HPP_AB130C8B
#define TEMPERATURE_SENSOR_HPP_AB130C8B

#include <OneWire.h>
#include <DallasTemperature.h>


namespace SousVide {
  class TemperatureSensor {
    OneWire* oneWire;
 
    DallasTemperature* sensors;
    
    int samplesTaken = 0;
    int minSamples = 10;
    unsigned long lastSampleTakenAt = 0;
    
    float floatingTemp = 0;
    float rawTemp = 0;
  public:
    TemperatureSensor(int pin){
      oneWire = new OneWire(pin);
      sensors = new DallasTemperature(oneWire);
      sensors->begin();
    }
    
    bool temperatureAvailable(){
      return samplesTaken >= minSamples;
    }
    
    float getRaw(){
      return rawTemp;
    }
    
    float getFloating(){
      return floatingTemp;
    }
    
    void update(){
      if((unsigned long)(millis() - lastSampleTakenAt) >= 1000) {
        if(samplesTaken < minSamples)
          samplesTaken +=1;
        lastSampleTakenAt = millis();
        sensors->requestTemperatures(); // Send the command to get temperatures

        rawTemp = sensors->getTempCByIndex(0); 
        float delta = 0.9;
        floatingTemp = (rawTemp*(1-delta) + floatingTemp*delta); 
      }
    }
    
  };
}


#endif /* end of include guard: TEMPERATURE_SENSOR_H_AB130C8B */
