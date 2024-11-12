#pragma once 

#include <iostream>
#include <string>

#include "Ataque.hpp"
#include "TipoPokemon.hpp"

using namespace std;

class Pokemon{
  private:
    int ID;
    string nome;
    int maxHp;
    int currentHp;
    int atributoFisico;
    int atributoEspecial;
    int velocidade;
    Ataque moveset[4];
    string tipo;
    
  public:
    Pokemon(int ID, string nome, int maxHp, int currentHp, int atributoFisico, int atributoEspecial, int velocidade, Ataque ataque1, Ataque ataque2,Ataque ataque3, Ataque ataque4):
    ID{ID}, nome{nome}, maxHp{maxHp}, currentHp{currentHp}, atributoFisico{atributoFisico}, atributoEspecial{atributoEspecial}, velocidade{velocidade}, moveset{ataque1, ataque2, ataque3, ataque4}
    {}

    int getID()
    {
      return ID;
    }

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
    
    void setCurrentHp(int currentHp){
      this->currentHp = currentHp;
    }
    
    void setAtributoFisico(int atributoFisico){
      this->atributoFisico = atributoFisico;
    }
    
    void setAtributoEspecial(int atributoEspecial){
      this->atributoEspecial = atributoEspecial;
    }
    
    void setVelocidade(int velocidade){
      this->velocidade = velocidade;
    }
    
    virtual void receberDano(int dano, string tipoAtacante){
      currentHp -= dano;
    }

    virtual string getTipo(){
      return tipo;
    }

    int calcularDano(int ataque){
      return moveset[ataque-1].calcularDano();
    }
};