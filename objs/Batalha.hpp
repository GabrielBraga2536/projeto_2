#pragma once 

#include <iostream>
#include <string>

#include "Treinador.hpp"
#include "Ataque.hpp"

using namespace std;

class Batalha{
  private:
    Treinador treinador1, treinador2;
    Pokemon pokemon1, pokemon2;
  
  public:
    void executarTurno(Pokemon atacante, Pokemon defensor, int posicao){
      float vantagem = calcularVantagemTipo(atacante.getTipoPokemon(), defensor.getTipoPokemon());
      Ataque ataque_utilizado = atacante.getAtaque(posicao);
      int dano = static_cast<int>(ataque_utilizado.calcularDano() * vantagem);
      defensor.receberDano(dano);
    }
};