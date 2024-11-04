#pragma once 

#include <iostream>
#include <string>

#include "Pokemon.hpp"
#include "TipoPokemon.hpp"

using namespace std;

class Ataque: public Pokemon{
  private:
    TipoPokemon tipo;
    int power;

  public:
    int getPower(){
      return power;
    }
    
    TipoPokemon getTipoAtaque(){
      return tipo;
    }
    
    int calcularDano(){
      //TODO codar a lógica para o dano do ataque sem considerar a vantagem do pokemon
    }
};