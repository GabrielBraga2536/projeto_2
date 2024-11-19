#pragma once 

#include <iostream>
#include "Pokemon.hpp"

using namespace std;

class PokemonFogo: public Pokemon{
private:
    string tipo;
public:
    PokemonFogo(int ID, string nome, int maxHp, int currentHp, int atributoFisico, int atributoEspecial, int velocidade, Ataque ataque1, Ataque ataque2,Ataque ataque3, Ataque ataque4):
Pokemon(ID, nome, maxHp, currentHp, atributoFisico, atributoEspecial, velocidade, ataque1, ataque2, ataque3, ataque4), tipo{"Fogo"}
{}

virtual string getTipo(){
  return tipo;
}

virtual void receberDano(int dano, string tipoAtacante){
    if(tipoAtacante == "Água")
    {
      setCurrentHp(getCurrentHp() - dano*2);
    }

    else if(tipoAtacante == "Fogo" || tipoAtacante == "Planta")
    {
      setCurrentHp(getCurrentHp() - dano/2);
    }

    else{
      setCurrentHp(getCurrentHp() - dano);
    }

}

};