#pragma once 

#include <iostream>
#include "Pokemon.hpp"

using namespace std;

class PokemonFantasma: public Pokemon{
private:
    string tipo;
public:
    PokemonFantasma(int ID, string nome, int maxHp, int currentHp, int atributoFisico, int atributoEspecial, int velocidade, Ataque ataque1, Ataque ataque2,Ataque ataque3, Ataque ataque4, Ataque pularAtaque):
Pokemon(ID, nome, maxHp, currentHp, atributoFisico, atributoEspecial, velocidade, ataque1, ataque2, ataque3, ataque4, pularAtaque), tipo{"Fantasma"}
{}

virtual string getTipo(){
  return tipo;
}

virtual float calculoDano(string tipoAtacante){
    if(tipoAtacante == "Fantasma")
    {
      return 2;
    }

    else{
      return 1;
    }

}

};