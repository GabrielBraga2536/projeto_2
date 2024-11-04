#pragma once 

#include <iostream>
#include <string>

#include "Ataque.hpp"
#include "TipoPokemon.hpp"

using namespace std;

class Pokemon{
  private:
    string nome;
    int maxHp;
    int currentHp;
    int atributoFisico;
    int atributoEspecial;
    int velocidade;
    Ataque *moveset[4];
    TipoPokemon tipo;
    
  public:
    string getNome(){
      return nome;
    }
    
    int getMaxHp(){
      return maxHp;
    }
    
    int getCurrentHp(){
      return currentHp;
    }
    
    int getAtributoFisico(){
      return atributoFisico;
    }
    
    int getAtributoEspecial(){
      return atributoEspecial;
    }
    
    int getVelocidade(){
      return velocidade;
    }
    
    //*A variável posição tem que estar no range de 0 até 3; moveset é um vetor de tamanho 4
    Ataque getAtaque(int posicao){
      moveset[posicao]->getTipoAtaque();
    }
    
    TipoPokemon getTipoPokemon(){
      return tipo;
    }
    
    void setCurrentHp(int currentHp){
      this->currentHp = currentHp;
    }
    
    void getAtributoFisico(int atributoFisico){
      this->atributoFisico = atributoFisico;
    }
    
    void getAtributoEspecial(int atributoEspecial){
      this->atributoEspecial = atributoEspecial;
    }
    
    void getVelocidade(int velocidade){
      this->velocidade = velocidade;
    }
    
    void receberDano(int dano){
      currentHp -= dano;
    }
};