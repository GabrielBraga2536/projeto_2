#pragma once 

#include <iostream>
#include <string>

#include "Treinador.hpp"
#include "Ataque.hpp"

using namespace std;

class Batalha{
  private:
    int treinadores[2];
    int turno;
  
  public:
    Batalha(int treinador1, int treinador2):
    treinadores{treinador1, treinador2}, turno{0}{}

    void executarTurno(Pokemon atacante, Pokemon defensor, int posicao){
      this->turno = turno + 1;
    }

    int getPokemonID(){
      return treinadores[turno];
    }
};