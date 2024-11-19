#pragma once 

#include <iostream>
#include <string>
#include <unistd.h> //Para "sleep"

#include "Treinador.hpp"

using namespace std;

class Batalha{
  private:
    Treinador treinadores[2];
    int turno;
    int x;
    int opcaoTreinadorAtaque[2];
    int opcaoPokemonItem[2];
    int opcaoTreinador[2];
    int opcaoPokemon[2];
    int opcaoItem[2];
  
  public:
    Batalha(Treinador treinador1, Treinador treinador2):
    treinadores{treinador1, treinador2}, turno{0}, x{1}, opcaoTreinadorAtaque{0, 0}, opcaoPokemonItem{0, 0}, opcaoTreinador{0, 0}, opcaoPokemon{0, 0}, opcaoItem{0, 0}{}

    int getPokemonID(){
      return treinadores[turno].getPokemonID();
    }

    string getNome(){
      return treinadores[turno].getNome();
    }

    int getCurrentHp(){
      return treinadores[turno].getCurrentHp();
    }

    int getOpcaoTreinadorAtaque(){
      return opcaoTreinadorAtaque[turno];
    }

    int getOpcaoTreinador(){
      return opcaoTreinador[turno];
    }
    
    int getOpcaoPokemon(){
      return opcaoPokemon[turno];
    }
    
    int getOpcaoItem(){
      return opcaoItem[turno];
    }

    int getAtributoEspecial(int pokemonAtributo){
      return treinadores[pokemonAtributo].getAtributoEspecial();
    }
    
    int getAtributoFisico(int pokemonAtributo){
      return treinadores[pokemonAtributo].getAtributoFisico();
    }

    int Dano(int ataque, int rand, int pokemonAtaque, int pokemonDefesa){
        return treinadores[turno].Dano(ataque, rand, pokemonAtaque, pokemonDefesa);
    }

    void selecionarPokemon(int posicao){
      treinadores[turno].selecionarPokemon(posicao);
    }

    void setTurno(int turno){
      this->turno = turno-1;
    }

    string getAtributo(int ataque){
      return treinadores[turno].getAtributo(ataque);
    }

    int getTurno(){
      return turno;
    }

    void curarVida(int treinador, int pokemon){
      return treinadores[treinador].curarVida(pokemon);
    }

    void recuperarItens(int treinador, int numero, int quantidade){
      return treinadores[treinador].recuperarItens(numero, quantidade);
    }

    void escolherPokemons(Pokemon pokemon1, Pokemon pokemon2, Pokemon pokemon3){
      treinadores[turno].escolherPokemons(pokemon1, pokemon2, pokemon3);
    }

    int getPosicao(){
      return treinadores[1].getPosicao();
    }

    void VidaENomeDosPokemonsAtivos(){
      cout << "Treinador 1: ";
      cout << treinadores[0].getNome() << endl;
      cout << "Vida: ";
      cout << treinadores[0].getCurrentHp() << endl;

      cout << "Treinador 2: ";
      cout << treinadores[1].getNome() << endl;
      cout << "Vida: ";
      cout << treinadores[1].getCurrentHp() << endl;
    }

    void quantidadeDeItens(){
      cout << "1 - Poções de Cura: " << treinadores[turno].getQuantidade(0) << endl;
      cout << "2 - Poções de Cura max: " << treinadores[turno].getQuantidade(1) << endl;
      cout << "3 - Reviver: " << treinadores[turno].getQuantidade(2) << endl;
      cout << "4 - Reviver max: " << treinadores[turno].getQuantidade(3) << endl;
      cout << "5 - Voltar" << endl;
    }

    void pokemons(){
      cout << "1 - " << treinadores[turno].getNome1() << " Vida: " << treinadores[turno].getCurrentHpEspecifico(0) << endl;
      cout << "2 - " << treinadores[turno].getNome2() << " Vida: " << treinadores[turno].getCurrentHpEspecifico(1) << endl;
      cout << "3 - " << treinadores[turno].getNome3() << " Vida: " << treinadores[turno].getCurrentHpEspecifico(2) << endl;
    }

    int VerSeUmTreinadorPerdeu(){
      if(treinadores[turno].getCurrentHpEspecifico(0) <= 0 && treinadores[turno].getCurrentHpEspecifico(1) <= 0 && treinadores[turno].getCurrentHpEspecifico(2) <= 0){
        return 0;
      }
      else{
        return 1;
      }
    }

    void pokemonsKO(){
      cout << treinadores[turno].getNome() << " foi derrotado!" << endl;
      while(x == 1){
        if(treinadores[turno].getCurrentHpEspecifico(0) <= 0 && treinadores[turno].getCurrentHpEspecifico(1) <= 0 && treinadores[turno].getCurrentHpEspecifico(2) <= 0){
          cout << "O treinador " << turno+1 << " foi derrotado!" << endl;
          break;
        }
        else{
          cout << "1 - " << treinadores[turno].getNome1() << " Vida: " << treinadores[turno].getCurrentHpEspecifico(0) << endl;
          cout << "2 - " << treinadores[turno].getNome2() << " Vida: " << treinadores[turno].getCurrentHpEspecifico(1) << endl;
          cout << "3 - " << treinadores[turno].getNome3() << " Vida: " << treinadores[turno].getCurrentHpEspecifico(2) << endl;
          cin >> opcaoPokemon[turno];
          treinadores[turno].selecionarPokemon(opcaoPokemon[turno]);
          if(opcaoPokemon[turno] > 3 || opcaoPokemon[turno] < 1){}
          else{
            opcaoTreinadorAtaque[turno] = 5;
          if(treinadores[turno].getCurrentHpEspecifico(opcaoPokemon[turno]-1) <= 0){
              cout << "Escolha ilegal, vida do pokemon zerada " << endl;
            }
            else{
              break;
            }
          }
        }
      }
    }

void pokemonsKOComputador(int random){
  cout << treinadores[turno].getNome() << " foi derrotado!" << endl;
  while(x == 1){
    if(treinadores[turno].getCurrentHpEspecifico(0) <= 0 && treinadores[turno].getCurrentHpEspecifico(1) <= 0 && treinadores[turno].getCurrentHpEspecifico(2) <= 0){
      cout << "O treinador " << turno+1 << " foi derrotado!" << endl;
      break;
    }
    else{
      opcaoPokemon[turno] = random%3+1;
      treinadores[turno].selecionarPokemon(opcaoPokemon[turno]);
      if(opcaoPokemon[turno] > 3 || opcaoPokemon[turno] < 1){}
      else{
        opcaoTreinadorAtaque[turno] = 5;
      if(treinadores[turno].getCurrentHpEspecifico(opcaoPokemon[turno]-1) <= 0){
        random = random + 1;
        }
        else{
          break;
        }
      }
    }
  }
}

    void ataques(){
      cout << "1 - Força " << treinadores[turno].getPower(1) << " Chance: " << treinadores[turno].getChance(1) << "% Atributo: " << treinadores[turno].getAtributo(1)  << endl;
      cout << "2 - Força " << treinadores[turno].getPower(2) << " Chance: " << treinadores[turno].getChance(2) << "% Atributo: " << treinadores[turno].getAtributo(2)  << endl;
      cout << "3 - Força " << treinadores[turno].getPower(3) << " Chance: " << treinadores[turno].getChance(3) << "% Atributo: " << treinadores[turno].getAtributo(3)  << endl;
      cout << "4 - Força " << treinadores[turno].getPower(4) << " Chance: " << treinadores[turno].getChance(4) << "% Atributo: " << treinadores[turno].getAtributo(4)  << endl;
      cout << "5 - Voltar" << endl;
    }

    void EscolhasDosTreinadores(){
        while (x == 1){
          //Exemplo de Batalha
          cout << "Treinador " << turno+1 <<  ": Atacar(1), Trocar pokemon(2), Item(3), Correr(4)" << endl;
          cin >> opcaoTreinador[turno];
          if (opcaoTreinador[turno] == 1){
            cout << "Treinador " << turno+1 <<  " escolha o ataque" << endl;
            ataques();
            cin >> opcaoTreinadorAtaque[turno];
            if(opcaoTreinadorAtaque[turno] > 4 || opcaoTreinadorAtaque[turno] < 1){}
            else{
              break;
            }
          }
          else if (opcaoTreinador[turno] == 2){
            cout << "Qual pokemon?" << endl;
            pokemons();
            cout << "4 - Voltar" << endl;
            cin >> opcaoPokemon[turno];
            if(opcaoPokemon[turno] > 3 || opcaoPokemon[turno] < 1){}
            else if((opcaoPokemon[turno]-1) == treinadores[turno].getPosicao()){
              cout << "Escolha ilegal, selecione um pokemon fora da luta" << endl;
            }
            else{
              opcaoTreinadorAtaque[turno] = 5;
            if(treinadores[turno].getCurrentHpEspecifico(opcaoPokemon[turno]-1) <= 0){
                cout << "Escolha ilegal, vida do pokemon zerada" << endl;
              }
              else{
                break;
              }
            }
          }
          else if (opcaoTreinador[turno] == 3){
            cout << "Qual item?" << endl;
            quantidadeDeItens();
            cin >> opcaoItem[turno];
            if(opcaoItem[turno] > 4 || opcaoItem[turno] < 1){}
            else if(treinadores[turno].getQuantidade(opcaoItem[turno]-1) <= 0){
                cout << "Escolha ilegal, sem mais usos do item" << endl;
              }
            else{
              cout << "Qual pokemon?" << endl;
              pokemons();
              cout << "4 - Voltar" << endl;
              cin >> opcaoPokemonItem[turno];
              opcaoPokemonItem[turno] -= 1;
              if (opcaoPokemonItem[turno] > 2 || opcaoPokemonItem[turno] < 0){}
              else if(opcaoItem[turno] >= 3 && treinadores[turno].getCurrentHpEspecifico(opcaoPokemonItem[turno]) > 0){                                                      cout << "Escolha ilegal, o pokemon ainda possui pontos de vida" << endl;
              }
              else if(opcaoItem[turno] <= 2 && treinadores[turno].getCurrentHpEspecifico(opcaoPokemonItem[turno]) < 0){                                                  cout << "Escolha ilegal, o pokemon foi atordoado" << endl;
              }
              else{
                opcaoTreinadorAtaque[turno] = 5;
                opcaoPokemon[turno] = 0;
                break;
              }
            }
          }
          else if (opcaoTreinador[turno] == 4){
            break;
          }
          else{
            cout << "Escolha ilegal, fora das alternativas" << endl;
          }
        }
        if (opcaoTreinador[turno] == 4){
          cout << "Treinador " << turno+1 << " escolheu correr!" << endl;
        }
    }

    void EscolhaCompotador(int random, int random2, int random3){
      int pokemons;
        while (x == 1){
          random = random+1;
          random2 = random2+1;
          random3 = random3+1;
          //Exemplo de Batalha

          if(((treinadores[turno].getCurrentHpEspecifico(1) <= 0 && treinadores[turno].getCurrentHpEspecifico(2) <= 0)) || ((treinadores[turno].getCurrentHpEspecifico(1) <= 0 && treinadores[turno].getCurrentHpEspecifico(0) <= 0)) || ((treinadores[turno].getCurrentHpEspecifico(0) <= 0 && treinadores[turno].getCurrentHpEspecifico(2) <= 0))){
            pokemons = 0;
          }
          else{
            pokemons = 1;
          }

          opcaoTreinador[turno] = random%100;
          if (opcaoTreinador[turno] <= 75){
            opcaoTreinadorAtaque[turno] = random2%4+1;
              break;
          }

          else if (opcaoTreinador[turno] > 75 && pokemons == 1){
            opcaoPokemon[turno] = random3%3+1;
            if((opcaoPokemon[turno]-1) == treinadores[turno].getPosicao()){
            }
            else{
              opcaoTreinadorAtaque[turno] = 5;
            if(treinadores[turno].getCurrentHpEspecifico(opcaoPokemon[turno]-1) <= 0){
            }
              else{
                break;
              }
            }
          }
          else if (opcaoTreinador[turno] > 75 && (treinadores[turno].getQuantidade(0) >= 0 || treinadores[turno].getQuantidade(1) >= 0 || treinadores[turno].getQuantidade(2) >= 0 || treinadores[turno].getQuantidade(3) >= 0)){
            opcaoItem[turno] = random3%4+1; if(treinadores[turno].getQuantidade(opcaoItem[turno]-1) <= 0){
              }
            else{
              opcaoPokemonItem[turno] = random2%3+1;
              opcaoPokemonItem[turno] -= 1;
              if (opcaoPokemonItem[turno] > 2 || opcaoPokemonItem[turno] < 0){}
              else if(opcaoItem[turno] >= 3 && treinadores[turno].getCurrentHpEspecifico(opcaoPokemonItem[turno]) > 0){}
              else if(opcaoItem[turno] <= 2 && treinadores[turno].getCurrentHpEspecifico(opcaoPokemonItem[turno]) < 0){}
              else{
                opcaoTreinadorAtaque[turno] = 5;
                opcaoPokemon[turno] = 0;
                break;
              }
            }
          }
          else{
            ataques();
            opcaoTreinadorAtaque[turno] = random2%4+1;
          }
        }
    }

    int OrdemVelocidade(int rand){
      if(treinadores[0].getVelocidade() > treinadores[1].getVelocidade()){
        return 1;
      }
      else if(treinadores[0].getVelocidade() < treinadores[1].getVelocidade()){
        return 2;
      }
      else{
        if(rand%2 == 0){
          return 1;
        }
        else{
          return 2;
        }
      }
    }

    void AtaqueDoTreinador(){
      if(turno == 1){
      cout << "Treinado 2: " << treinadores[1].getNome() << " usou o ataque " << treinadores[1].getAtributo(opcaoTreinadorAtaque[1]) << " de " << treinadores[1].getPower(opcaoTreinadorAtaque[1]) << " de poder" << endl;
      sleep(1);
      }
      else{
        cout << "Treinador 1: " << treinadores[0].getNome() << " usou o ataque " << treinadores[0].getAtributo(opcaoTreinadorAtaque[0]) << " de " << treinadores[0].getPower(opcaoTreinadorAtaque[0]) << " de poder" << endl;
        sleep(1);
      }
    }

    void DanoDoTreinador(int dano){
      if(turno == 1){
        treinadores[0].receberDano(dano);
      }
      else{
        treinadores[1].receberDano(dano);
      }
    }
    bool VerificarEscolhas(){
      if(opcaoTreinadorAtaque[turno] == 5){
        if(opcaoPokemon[turno] <= 3 && opcaoPokemon[turno] >= 1){
          treinadores[turno].selecionarPokemon(opcaoPokemon[turno]);
          cout << "O treinador " << turno+1 << " trocou para " << treinadores[turno].getNome() << endl;
          sleep(1);
          return 0;
        }
        else if(opcaoItem[turno] == 1){
          cout << "O treinador " << turno+1 << " utilizou Elixir de cura" << endl;
          treinadores[turno].Curar(20, opcaoPokemonItem[turno]);
          treinadores[turno].utilizarItem(1);
          sleep(1);
          return 0;
        }
        else if(opcaoItem[turno] == 2){
          cout << "O treinador " << turno+1 << " utilizou Elixir de cura max" << endl;
          treinadores[turno].Curar(treinadores[turno].getMaxHpEspecifico(opcaoPokemonItem[turno]), opcaoPokemonItem[turno]);
          treinadores[turno].utilizarItem(2);
          sleep(1);
          return 0;
        }
        else if(opcaoItem[turno] == 3){
          cout << "O treinador " << turno+1 << " utilizou Reviver" << endl;
          treinadores[turno].Reviver(0.5, opcaoPokemonItem[turno]);
          treinadores[turno].utilizarItem(3);
          sleep(1);
          return 0;
        } 
        else{
          cout << "O treinador " << turno+1 << " utilizou Reviver max" << endl;
          treinadores[turno].Reviver(1, opcaoPokemonItem[turno]);
          treinadores[turno].utilizarItem(4);
          sleep(1);
          return 0;
        }
      }
      else{
        return 1;
      }
      
    }
    
};