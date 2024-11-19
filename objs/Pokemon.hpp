#pragma once 

#include <iostream>
#include <string>

#include "Ataque.hpp"

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
    Ataque moveset[5];
    string tipo;
    
  public:
    Pokemon(int ID, string nome, int maxHp, int currentHp, int atributoFisico, int atributoEspecial, int velocidade, Ataque ataque1, Ataque ataque2,Ataque ataque3, Ataque ataque4, Ataque pularAtaque):
    ID{ID}, nome{nome}, maxHp{maxHp}, currentHp{currentHp}, atributoFisico{atributoFisico}, atributoEspecial{atributoEspecial}, velocidade{velocidade}, moveset{ataque1, ataque2, ataque3, ataque4, pularAtaque}
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

    virtual string getTipo(){
      return "tipo";
    }
    
    void setCurrentHp(int currentHp){
      this->currentHp = currentHp;
    }

    void curarVida(){
      currentHp = maxHp;
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
    
    void receberDano(int dano){
      currentHp -= dano;
    }

    virtual float calculoDano(string tipoAtacante){
      return 0;
    }

    void Curar(int cura){
      currentHp += cura;
      if (currentHp > maxHp){
        currentHp = maxHp;
      }
    }

    void Reviver(float cura){
      currentHp = cura*maxHp;
    }

    int Dano(int ataque, int rand, int atributoAtaque, int atributoDefesa){
      return moveset[ataque-1].Dano(rand, atributoAtaque, atributoDefesa);
    }

    int getPower(int ataque){
      return moveset[ataque-1].getPower();
    }
    
    int getChance(int ataque){
      return moveset[ataque-1].getChance();
    }

    string getAtributo(int ataque){
      return moveset[ataque-1].getAtributo();
    }
};