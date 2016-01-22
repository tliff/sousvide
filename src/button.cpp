#include "button.hpp"
#include "sous_vide.hpp"

SousVide::Button::Button(SousVide* o, int pin, Press press){
  this->o = o;
  this->pin = pin;
  this->press = press;
  pinMode(pin, INPUT);
  o->send(press);
}

void SousVide::Button::update(){
  if(state == HIGH && digitalRead(this->pin) == LOW){
    o->send(press);
  }
  state = digitalRead(this->pin);
}