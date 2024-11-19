#pragma once 

#include <iostream>
#include <string>

using namespace std;

class Ataque{
  private:
    int power;

  public:
    Ataque(int power):
    power{power}{}

    int getPower(){
      return power;
    }
    
    int calcularDano(){
      //TODO codar a lógica para o dano do ataque sem considerar a vantagem do pokemon
      return power;
    }
};