#pragma once 

#include <iostream>
#include <string>

#include "Pokemon.hpp"
#include "Itens.hpp"

using namespace std;

class Treinador{
  private:
    int posicao;
    Pokemon pokemonsID[3];
    Itens itens[4];
    
  public:
    Treinador(Pokemon* pokemon1, Pokemon* pokemon2, Pokemon* pokemon3, Itens item1, Itens item2, Itens item3, Itens item4):
    posicao{0}, pokemonsID{*pokemon1, *pokemon2, *pokemon3}, itens{item1, item2, item3, item4}{}
    
    void selecionarPokemon(int posicao){
      this->posicao = posicao-1;
    }
    
    void escolherPokemons(Pokemon pokemon1, Pokemon pokemon2, Pokemon pokemon3){
      this->pokemonsID[0] = pokemon1;
      this->pokemonsID[1] = pokemon2;
      this->pokemonsID[2] = pokemon3;
    }
    
    int getPosicao(){
      return posicao;
    }
    
    int getPokemonID(){
      return pokemonsID[posicao].getID();
    }
    
    string getNome1(){
      return pokemonsID[0].getNome();
    }
    
    string getNome2(){
      return pokemonsID[1].getNome();
    }
    
    string getNome3(){
      return pokemonsID[2].getNome();
    }
    
    int getCurrentHpEspecifico(int escolha){
      return pokemonsID[escolha].getCurrentHp();
    }
    
  string getNome(){
    return pokemonsID[posicao].getNome();
  }
  
  int getMaxHp(){
    return pokemonsID[posicao].getMaxHp();
  }
  
  int getMaxHpEspecifico(int pokemonEscolha){
    return pokemonsID[pokemonEscolha].getMaxHp();
  }

  int getCurrentHp(){
    return pokemonsID[posicao].getCurrentHp();
  }
  
  int getAtributoFisico(){
    return pokemonsID[posicao].getAtributoFisico();
  }
  
  int getAtributoEspecial(){
    return pokemonsID[posicao].getAtributoEspecial();
  }
  
  int getVelocidade(){
    return pokemonsID[posicao].getVelocidade();
  }
  
  int getPower(int ataque){
    return pokemonsID[posicao].getPower(ataque);
  }
  
  int getChance(int ataque){
    return pokemonsID[posicao].getChance(ataque);
  }
  
  string getAtributo(int ataque){
    return pokemonsID[posicao].getAtributo(ataque);
  }
  
  void setCurrentHp(int currentHp){
    pokemonsID[posicao].setCurrentHp(currentHp);
  }
  
  void setAtributoFisico(int atributoFisico){
    pokemonsID[posicao].setAtributoFisico(atributoFisico);
  }
  
  void setAtributoEspecial(int atributoEspecial){
    pokemonsID[posicao].setAtributoEspecial(atributoEspecial);
  }
  
  void setVelocidade(int velocidade){
    pokemonsID[posicao].setVelocidade(velocidade);
  }
  
  void receberDano(int dano){
    pokemonsID[posicao].receberDano(dano);
  }
  
  string getTipo(){
    return pokemonsID[posicao].getTipo();
  }
  
  int getQuantidade(int item){
    return itens[item].getQuantidade();
  }
    
  void Curar(int cura, int pokemonItem){
    pokemonsID[pokemonItem].Curar(cura);
  }
  
  void Reviver(float porcentagem, int pokemonItem){
    pokemonsID[pokemonItem].Reviver(porcentagem);
  }
  
  void utilizarItem(int item){
    itens[item-1].utilizarItem();
  }
  
  int Dano(int ataque, int rand, int atributoAtaque, int atributoDefesa){
    return pokemonsID[posicao].Dano(ataque, rand, atributoAtaque, atributoDefesa);
  }
  
  void curarVida(int pokemon){
    return pokemonsID[pokemon].curarVida();
  }
  
  void recuperarItens(int numero, int quantidade){
    return itens[numero].recuperarItens(quantidade);
  }
  
};