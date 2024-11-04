#pragma once 

#include <iostream>
#include <string>

#include "Pokemon.hpp"

using namespace std;

class Treinador: public Pokemon{
  private:
    string nome;
    Pokemon pokemons[3];
    
  public:
    Pokemon selecionarPokemon(int posicao){
      return pokemons[posicao];
    }
};