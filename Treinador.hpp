#pragma once 

#include <iostream>
#include <string>

#include "Pokemon.hpp"

using namespace std;

class Treinador{
  private:
    string nome;
    int posicao;
    int pokemonsID[3];
    
  public:
    Treinador(int pokemon1, int pokemon2, int pokemon3):
pokemonsID{pokemon1, pokemon2, pokemon3}{}

    void selecionarPokemon(int posicao){
      this->posicao = posicao-1;
    }

    int getPokemonID(){
      return pokemonsID[posicao];
    }

};