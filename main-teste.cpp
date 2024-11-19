#include <iostream>
#include <cstdlib> //Para número aleatório
#include <ctime> //Para número aleatório
#include <unistd.h> //Para "sleep"

#include "Pokemon.hpp"
#include "PokemonAgua.hpp"
#include "PokemonDragao.hpp"
#include "PokemonFantasma.hpp"
#include "PokemonFogo.hpp"
#include "PokemonPlanta.hpp"
#include "Treinador.hpp"
#include "Batalha.hpp"

using namespace std;

int x = 1;
int ID;
int dano;
int derrota[2];
int opcaoModo;
int opcaoContinuar = 0;
int turno;
int turno2;
int estiloDoJogo[2];
int estiloDaEscolha[2];
int pokemonInicial[2];
int pokemonsAleatorios[3];
int selecionarPokemons[3];
string tipo;
bool escolhas[2];
int escolhasComputador[2];

int main(){
  // colocar seed para time(0)
  srand(time(0));
  // gera número aleatório
  int random = rand();
  
  Ataque ataque1(120, 96, "Especial");
  Ataque ataque2(110, 102, "Especial");
  Ataque ataque3(100, 115, "Especial");
  Ataque ataque4(90, 127, "Especial");
  Ataque ataque5(120, 96, "Fisico");
  Ataque ataque6(110, 102, "Fisico");
  Ataque ataque7(100, 115, "Fisico");
  Ataque ataque8(90, 127, "Fisico");
  Ataque pularAtaque(0, -1, "Fisico");

  Itens pocaoDeCura(5);
  Itens pocaoDeCuraMax(2);
  Itens revive(5);
  Itens reviveMax(2);
  
  PokemonPlanta Serperior(1, "Serperior", 150, 150, 85, 85, 113, ataque1, ataque6, ataque3, ataque8, pularAtaque);
  PokemonFogo Emboar(2, "Emboar", 220, 220, 93, 82, 65, ataque5, ataque6, ataque7, ataque4, pularAtaque);
  PokemonAgua Samurott(3, "Samurott", 190, 190, 92, 89, 70, ataque5, ataque2, ataque7, ataque4, pularAtaque);
  PokemonFantasma Cofagrigus(4, "Cofagrigus", 116, 116, 97, 100, 30, ataque1, ataque6, ataque3, ataque8, pularAtaque);
  PokemonDragao Hydreigon(5, "Hydreigon", 184, 184, 97, 107, 98, ataque1, ataque2, ataque3, ataque8, pularAtaque);
  
  Treinador Treinador1(Serperior, Emboar, Samurott, pocaoDeCura, pocaoDeCuraMax, revive, reviveMax);
  Treinador Treinador2(Cofagrigus, Hydreigon, Serperior, pocaoDeCura, pocaoDeCuraMax, revive, reviveMax);

  Batalha batalha(Treinador1, Treinador2);
  
  Batalha *batalhar[1];
  batalhar[0] = &batalha;

  Treinador *treinador[2];
  treinador[0] = &Treinador1;
  treinador[1] = &Treinador2;

  Pokemon *pokemons[5];
  pokemons[0] = &Serperior;
  pokemons[1] = &Emboar;
  pokemons[2] = &Samurott;
  pokemons[3] = &Cofagrigus;
  pokemons[4] = &Hydreigon;

  cout << "Modos de jogo: " << endl;
  cout << "1 - 1 jogador: " << endl;
  cout << "2 - 2 jogadores: " << endl;
  cin >> opcaoModo;
  
    //Selecionar pokemons
  while(x == 1){
    if(batalhar[0]->getOpcaoTreinador() == 4){
      break;
    }
    if (opcaoModo == 2){
      if(opcaoContinuar == 2){
        return 0;
      }
      //Treinador 1
      while(x == 1){
        batalhar[0]->setTurno(1);
        cout << "Escolha seu primeiro pokemon: " << endl;
        cout << "1 - Serperior" << endl;
        cout << "2 - Emboar" << endl;
        cout << "3 - Samurott" << endl;
        cout << "4 - Cofagrigus" << endl;
        cout << "5 - Hydreigon" << endl;
        cin >> selecionarPokemons[0];
        selecionarPokemons[1] = selecionarPokemons[0];
        selecionarPokemons[2] = selecionarPokemons[0];
        if (selecionarPokemons[0] > 5 || selecionarPokemons[0] < 1){
          cout << "Fora do alcance" << endl;
        }
        else{
          cout << pokemons[selecionarPokemons[0]-1]->getNome() << " foi escolhido" << endl;
          while(x == 1){
            cout << "Escolha seu segundo pokemon: " << endl;
            cin >> selecionarPokemons[1];
              selecionarPokemons[2] = selecionarPokemons[1];
            if (selecionarPokemons[1] > 5 || selecionarPokemons[1] < 1){
              cout << "Fora do alcance" << endl;
            }
            else if (selecionarPokemons[1] == selecionarPokemons[0]){
              cout << "Esse pokemon foi previamente escolhido" << endl;
            }
            else{
              break;
            }
          }
          cout << pokemons[selecionarPokemons[1]-1]->getNome() << " foi escolhido" << endl;
          while(x == 1){
            cout << "Escolha seu terceiro pokemon: " << endl;
            cin >> selecionarPokemons[2];
            if (selecionarPokemons[2] > 5 || selecionarPokemons[2] < 1){
              cout << "Fora do alcance" << endl;
            }
            else if (selecionarPokemons[2] == selecionarPokemons[0] || selecionarPokemons[2] == selecionarPokemons[1]){
              cout << "Esse pokemon foi previamente escolhido" << endl;
            }
            else{
              cout << pokemons[selecionarPokemons[2]-1]->getNome() << " foi escolhido" << endl;
              break;
            }
          }
          break;
        }
      }
        batalhar[0]->escolherPokemons(*pokemons[selecionarPokemons[0]-1], *pokemons[selecionarPokemons[1]-1], *pokemons[selecionarPokemons[2]-1]);
        while(x == 1){
          cout << "Com qual pokemon deseja iniciar?" << endl;
          batalhar[0]->pokemons();
          cin >> pokemonInicial[0];
          if(pokemonInicial[0]>3 || pokemonInicial[0]<1){
            cout << "Fora do alcance" << endl;
          }
          else{
            batalhar[0]->selecionarPokemon(pokemonInicial[0]);
            break;
          }
        }
      //Treinador 2
      while(x == 1){
        batalhar[0]->setTurno(2);
        cout << "Escolha seu primeiro pokemon: " << endl;
        cout << "1 - Serperior" << endl;
        cout << "2 - Emboar" << endl;
        cout << "3 - Samurott" << endl;
        cout << "4 - Cofagrigus" << endl;
        cout << "5 - Hydreigon" << endl;
        cin >> selecionarPokemons[0];
        selecionarPokemons[1] = selecionarPokemons[0];
        selecionarPokemons[2] = selecionarPokemons[0];
        if (selecionarPokemons[0] > 5 || selecionarPokemons[0] < 1){
          cout << "Fora do alcance" << endl;
        }
        else{
          cout << pokemons[selecionarPokemons[0]-1]->getNome() << " foi escolhido" << endl;
          while(x == 1){
            cout << "Escolha seu segundo pokemon: " << endl;
            cin >> selecionarPokemons[1];
              selecionarPokemons[2] = selecionarPokemons[1];
            if (selecionarPokemons[1] > 5 || selecionarPokemons[1] < 1){
              cout << "Fora do alcance" << endl;
            }
            else if (selecionarPokemons[1] == selecionarPokemons[0]){
              cout << "Esse pokemon foi previamente escolhido" << endl;
            }
            else{
              break;
            }
          } 
          cout << pokemons[selecionarPokemons[1]-1]->getNome() << " foi escolhido" << endl;
          while(x == 1){
            cout << "Escolha seu terceiro pokemon: " << endl;
            cin >> selecionarPokemons[2];
            if (selecionarPokemons[2] > 5 || selecionarPokemons[2] < 1){
              cout << "Fora do alcance" << endl;
            }
            else if (selecionarPokemons[2] == selecionarPokemons[0] || selecionarPokemons[2] == selecionarPokemons[1]){
              cout << "Esse pokemon foi previamente escolhido" << endl;
            }
            else{
              cout << pokemons[selecionarPokemons[2]-1]->getNome() << " foi escolhido" << endl;
              break;
            }
          }
          break;
        }
      }
        batalhar[0]->escolherPokemons(*pokemons[selecionarPokemons[0]-1], *pokemons[selecionarPokemons[1]-1], *pokemons[selecionarPokemons[2]-1]);
        while(x == 1){
          cout << "Com qual pokemon deseja iniciar?" << endl;
          batalhar[0]->pokemons();
          cin >> pokemonInicial[1];
          if(pokemonInicial[1]>3 || pokemonInicial[1]<1){
            cout << "Fora do alcance" << endl;}
          else{
            batalhar[0]->selecionarPokemon(pokemonInicial[1]);
            break;
          }
        }
      while(x == 1){
        //Nome e vida
        batalhar[0]->VidaENomeDosPokemonsAtivos();
        
        batalhar[0]->setTurno(1);
        batalhar[0]->EscolhasDosTreinadores();
        if(batalhar[0]->getOpcaoTreinador() == 4){
          break;
        }
        batalhar[0]->setTurno(2);
        batalhar[0]->EscolhasDosTreinadores();
        if(batalhar[0]->getOpcaoTreinador() == 4){
          break;
        }
        
        turno = batalhar[0]->OrdemVelocidade(random);
        if (turno == 2){
          turno2 = 1;
        }
        else{
          turno2 = 2;
        }
        batalhar[0]->setTurno(turno);
        escolhas[0] = batalhar[0]->VerificarEscolhas();
        batalhar[0]->setTurno(turno2);
        escolhas[1] = batalhar[0]->VerificarEscolhas();
        
        if(escolhas[0] == 1){
          batalhar[0]->setTurno(turno);
          batalhar[0]->AtaqueDoTreinador();
          random = rand();
          tipo = pokemons[batalhar[0]->getPokemonID()-1]->getTipo();
          batalhar[0]->setTurno(turno2);
          ID = batalhar[0]->getPokemonID()-1;
          batalhar[0]->setTurno(turno);
          if (batalhar[0]->getAtributo(batalhar[0]->getOpcaoTreinadorAtaque()) == "Especial")
          dano = treinador[turno-1]->Dano(batalhar[0]->getOpcaoTreinadorAtaque(), random, batalhar[0]->getAtributoEspecial(turno-1), batalhar[0]->getAtributoEspecial(turno2-1))*pokemons[ID]->calculoDano(tipo);
          else{
            dano = treinador[turno-1]->Dano(batalhar[0]->getOpcaoTreinadorAtaque(), random, batalhar[0]->getAtributoFisico(turno-1), batalhar[0]->getAtributoFisico(turno2-1))*pokemons[ID]->calculoDano(tipo);
          }
          batalhar[0]->setTurno(turno);
          batalhar[0]->DanoDoTreinador(dano);
        }
    
        batalhar[0]->setTurno(turno2);
        if(escolhas[1] == 1 && batalhar[0]->getCurrentHp() > 0){
          batalhar[0]->AtaqueDoTreinador();
          random = rand();
          tipo = pokemons[batalhar[0]->getPokemonID()-1]->getTipo();
          batalhar[0]->setTurno(turno);
          ID = batalhar[0]->getPokemonID()-1;
          batalhar[0]->setTurno(turno);
          if (batalhar[0]->getAtributo(batalhar[0]->getOpcaoTreinadorAtaque()) == "Especial")
          dano = treinador[turno-1]->Dano(batalhar[0]->getOpcaoTreinadorAtaque(), random, batalhar[0]->getAtributoEspecial(turno2-1), batalhar[0]->getAtributoEspecial(turno-1))*pokemons[ID]->calculoDano(tipo);
          else{
            dano = treinador[turno-1]->Dano(batalhar[0]->getOpcaoTreinadorAtaque(), random, batalhar[0]->getAtributoFisico(turno2-1), batalhar[0]->getAtributoFisico(turno-1))*pokemons[ID]->calculoDano(tipo);
          }
          batalhar[0]->setTurno(turno2);
          batalhar[0]->DanoDoTreinador(dano);
        }
        if(batalhar[0]->getCurrentHp() <= 0){
          batalhar[0]->pokemonsKO();
        }
        batalhar[0]->setTurno(turno);
        if(batalhar[0]->getCurrentHp() <= 0){
          batalhar[0]->pokemonsKO();
        }
        derrota[0] = batalhar[0]->VerSeUmTreinadorPerdeu();
        batalhar[0]->setTurno(turno2);
        derrota[1] = batalhar[0]->VerSeUmTreinadorPerdeu();
        if (derrota[1] == 0 || derrota[0] == 0){
          batalhar[0]->curarVida(0, 0);
          batalhar[0]->curarVida(0, 1);
          batalhar[0]->curarVida(0, 2);
          batalhar[0]->curarVida(1, 0);
          batalhar[0]->curarVida(1, 1);
          batalhar[0]->curarVida(1, 2);
          batalhar[0]->recuperarItens(0, 0, 5);
          batalhar[0]->recuperarItens(0, 1, 2);
          batalhar[0]->recuperarItens(0, 2, 5);
          batalhar[0]->recuperarItens(0, 3, 2);
          batalhar[0]->recuperarItens(1, 0, 5);
          batalhar[0]->recuperarItens(1, 1, 2);
          batalhar[0]->recuperarItens(1, 2, 5);
          batalhar[0]->recuperarItens(1, 3, 2);
          cout << "Desejar continuar? " << endl;
          cout << "1 - Continuar" << endl;
          cout << "2 - Parar" << endl;
          cout << "3 - Trocar pokemons" << endl;
          cin >> opcaoContinuar;
          if (opcaoContinuar == 1){
            
            while(x == 1){
              cout << "Treinador 1 com qual pokemon deseja iniciar?" << endl;
              batalhar[0]->setTurno(1);
              batalhar[0]->pokemons();
              cin >> pokemonInicial[0];
              if(pokemonInicial[0]>3 || pokemonInicial[0]<1){
                cout << "Fora do alcance" << endl;}
              else{
                batalhar[0]->selecionarPokemon(pokemonInicial[0]);
                break;
              }
            }
            
            while(x == 1){
              cout << "Treinador 2 com qual pokemon deseja iniciar?" << endl;
              batalhar[0]->setTurno(2);
              batalhar[0]->pokemons();
              cin >> pokemonInicial[1];
              if(pokemonInicial[1]>3 || pokemonInicial[1]<1){
                cout << "Fora do alcance" << endl;}
              else{
                batalhar[0]->selecionarPokemon(pokemonInicial[1]);
                break;
              }
            }
          }
          else if (opcaoContinuar == 3){
            break;
          }
          else{
            x = 0;
          }
        }
      }
    }
    else{
      //Treinador 1
      while(x == 1){
          if(batalhar[0]->getOpcaoTreinador() == 4){
            break;
          }
        batalhar[0]->setTurno(1);
        cout << "Escolha seu primeiro pokemon: " << endl;
        cout << "1 - Serperior" << endl;
        cout << "2 - Emboar" << endl;
        cout << "3 - Samurott" << endl;
        cout << "4 - Cofagrigus" << endl;
        cout << "5 - Hydreigon" << endl;
        cin >> selecionarPokemons[0];
        selecionarPokemons[1] = selecionarPokemons[0];
        selecionarPokemons[2] = selecionarPokemons[0];
        if (selecionarPokemons[0] > 5 || selecionarPokemons[0] < 1){
          cout << "Fora do alcance" << endl;
        }
        else{
          cout << pokemons[selecionarPokemons[0]-1]->getNome() << " foi escolhido" << endl;
          while(x == 1){
            cout << "Escolha seu segundo pokemon: " << endl;
            cin >> selecionarPokemons[1];
              selecionarPokemons[2] = selecionarPokemons[1];
            if (selecionarPokemons[1] > 5 || selecionarPokemons[1] < 1){
              cout << "Fora do alcance" << endl;
            }
            else if (selecionarPokemons[1] == selecionarPokemons[0]){
              cout << "Esse pokemon foi previamente escolhido" << endl;
            }
            else{
              break;
            }
          }
          cout << pokemons[selecionarPokemons[1]-1]->getNome() << " foi escolhido" << endl;
          while(x == 1){
            cout << "Escolha seu terceiro pokemon: " << endl;
            cin >> selecionarPokemons[2];
            if (selecionarPokemons[2] > 5 || selecionarPokemons[2] < 1){
              cout << "Fora do alcance" << endl;
            }
            else if (selecionarPokemons[2] == selecionarPokemons[0] || selecionarPokemons[2] == selecionarPokemons[1]){
              cout << "Esse pokemon foi previamente escolhido" << endl;
            }
            else{
              cout << pokemons[selecionarPokemons[2]-1]->getNome() << " foi escolhido" << endl;
              break;
            }
          }
          break;
        }
      }
        batalhar[0]->escolherPokemons(*pokemons[selecionarPokemons[0]-1], *pokemons[selecionarPokemons[1]-1], *pokemons[selecionarPokemons[2]-1]);
        while(x == 1){
          cout << "Com qual pokemon deseja iniciar?" << endl;
          batalhar[0]->pokemons();
          cin >> pokemonInicial[0];
          if(pokemonInicial[0]>3 || pokemonInicial[0]<1){
            cout << "Fora do alcance" << endl;}
          else{
            batalhar[0]->selecionarPokemon(pokemonInicial[0]);
            break;
          }
        }
      //Computador
      while(x == 1){
        batalhar[0]->setTurno(2);
        random = rand()%5;
        pokemonsAleatorios[0] = random;
        pokemonsAleatorios[1] = random;
        pokemonsAleatorios[2] = random;
        while(pokemonsAleatorios[0] == pokemonsAleatorios[1]){
          random = rand()%5;
          pokemonsAleatorios[1] = random;
          pokemonsAleatorios[2] = random;
        }
        while(pokemonsAleatorios[0] == pokemonsAleatorios[2] || pokemonsAleatorios[1] == pokemonsAleatorios[2]){
          random = rand()%5;
          pokemonsAleatorios[1] = random;
        }
          batalhar[0]->escolherPokemons(*pokemons[pokemonsAleatorios[0]], *pokemons[pokemonsAleatorios[1]], *pokemons[pokemonsAleatorios[2]]);
          random = rand();
          pokemonInicial[1] = random%3;
          batalhar[0]->selecionarPokemon(pokemonInicial[1]+1);
          break;
      }
  
      while(x == 1){
        //Nome e vida
        batalhar[0]->VidaENomeDosPokemonsAtivos();
  
        batalhar[0]->setTurno(1);
        batalhar[0]->EscolhasDosTreinadores();
        if(batalhar[0]->getOpcaoTreinador() == 4){
          break;
        }
        batalhar[0]->setTurno(2);
        random = rand();
        escolhasComputador[0] = rand();
        escolhasComputador[1] = rand();
        batalhar[0]->EscolhaCompotador(random, escolhasComputador[0], escolhasComputador[1]);
  
        turno = batalhar[0]->OrdemVelocidade(random);
        if (turno == 2){
          turno2 = 1;
        }
        else{
          turno2 = 2;
        }
        batalhar[0]->setTurno(turno);
        escolhas[0] = batalhar[0]->VerificarEscolhas();
        batalhar[0]->setTurno(turno2);
        escolhas[1] = batalhar[0]->VerificarEscolhas();
  
        if(escolhas[0] == 1){
          batalhar[0]->setTurno(turno);
          batalhar[0]->AtaqueDoTreinador();
          random = rand();
          tipo = pokemons[batalhar[0]->getPokemonID()-1]->getTipo();
          batalhar[0]->setTurno(turno2);
          ID = batalhar[0]->getPokemonID()-1;
          batalhar[0]->setTurno(turno);
          if (batalhar[0]->getAtributo(batalhar[0]->getOpcaoTreinadorAtaque()) == "Especial")
          dano = treinador[turno-1]->Dano(batalhar[0]->getOpcaoTreinadorAtaque(), random, batalhar[0]->getAtributoEspecial(turno-1), batalhar[0]->getAtributoEspecial(turno2-1))*pokemons[ID]->calculoDano(tipo);
          else{
            dano = treinador[turno-1]->Dano(batalhar[0]->getOpcaoTreinadorAtaque(), random, batalhar[0]->getAtributoFisico(turno-1), batalhar[0]->getAtributoFisico(turno2-1))*pokemons[ID]->calculoDano(tipo);
          }
          batalhar[0]->setTurno(turno);
          batalhar[0]->DanoDoTreinador(dano);
        }
  
        batalhar[0]->setTurno(turno2);
        if(escolhas[1] == 1 && batalhar[0]->getCurrentHp() > 0){
          batalhar[0]->AtaqueDoTreinador();
          random = rand();
          tipo = pokemons[batalhar[0]->getPokemonID()-1]->getTipo();
          batalhar[0]->setTurno(turno);
          ID = batalhar[0]->getPokemonID()-1;
          batalhar[0]->setTurno(turno2);
          if (batalhar[0]->getAtributo(batalhar[0]->getOpcaoTreinadorAtaque()) == "Especial")
          dano = treinador[turno-1]->Dano(batalhar[0]->getOpcaoTreinadorAtaque(), random, batalhar[0]->getAtributoEspecial(turno2-1), batalhar[0]->getAtributoEspecial(turno-1))*pokemons[ID]->calculoDano(tipo);
          else{
            dano = treinador[turno-1]->Dano(batalhar[0]->getOpcaoTreinadorAtaque(), random, batalhar[0]->getAtributoFisico(turno2-1), batalhar[0]->getAtributoFisico(turno-1))*pokemons[ID]->calculoDano(tipo);
          }
          batalhar[0]->setTurno(turno2);
          batalhar[0]->DanoDoTreinador(dano);
        }
        random = rand();
        if(batalhar[0]->getCurrentHp() <= 0){
          if(turno2 == 1){
            batalhar[0]->pokemonsKO();
          }
          else{
            batalhar[0]->pokemonsKOComputador(random);
          }
        }
        batalhar[0]->setTurno(turno);
        if(batalhar[0]->getCurrentHp() <= 0){
          if(turno == 1){
            batalhar[0]->pokemonsKO();
          }
          else{
            batalhar[0]->pokemonsKOComputador(random);
          }
        }
        derrota[0] = batalhar[0]->VerSeUmTreinadorPerdeu();
        batalhar[0]->setTurno(turno2);
        derrota[1] = batalhar[0]->VerSeUmTreinadorPerdeu();
        if (derrota[1] == 0 || derrota[0] == 0){
          batalhar[0]->curarVida(0, 0);
          batalhar[0]->curarVida(0, 1);
          batalhar[0]->curarVida(0, 2);
          batalhar[0]->curarVida(1, 0);
          batalhar[0]->curarVida(1, 1);
          batalhar[0]->curarVida(1, 2);
          batalhar[0]->recuperarItens(0, 0, 5);
          batalhar[0]->recuperarItens(0, 1, 2);
          batalhar[0]->recuperarItens(0, 2, 5);
          batalhar[0]->recuperarItens(0, 3, 2);
          batalhar[0]->recuperarItens(1, 0, 5);
          batalhar[0]->recuperarItens(1, 1, 2);
          batalhar[0]->recuperarItens(1, 2, 5);
          batalhar[0]->recuperarItens(1, 3, 2);
          cout << "Desejar continuar? " << endl;
          cout << "1 - Continuar" << endl;
          cout << "2 - Parar" << endl;
          cin >> opcaoContinuar;
          
          if (opcaoContinuar == 1){
            batalhar[0]->setTurno(1);
            cout << "Com qual pokemon deseja iniciar?" << endl;
            batalhar[0]->pokemons();
            cin >> pokemonInicial[0];
            batalhar[0]->selecionarPokemon(pokemonInicial[0]);
            
            //Computador
            while(x == 1){
              batalhar[0]->setTurno(2);
              random = rand()%5;
              pokemonsAleatorios[0] = random;
              pokemonsAleatorios[1] = random;
              pokemonsAleatorios[2] = random;
              while(pokemonsAleatorios[0] == pokemonsAleatorios[1]){
                random = rand()%5;
                pokemonsAleatorios[1] = random;
                pokemonsAleatorios[2] = random;
              }
              while(pokemonsAleatorios[0] == pokemonsAleatorios[2] || pokemonsAleatorios[1] == pokemonsAleatorios[2]){
                random = rand()%5;
                pokemonsAleatorios[1] = random;
              }
              batalhar[0]->escolherPokemons(*pokemons[pokemonsAleatorios[0]], *pokemons[pokemonsAleatorios[1]], *pokemons[pokemonsAleatorios[2]]);
              batalhar[0]->selecionarPokemon(1);

                batalhar[0]->escolherPokemons(*pokemons[pokemonsAleatorios[0]], *pokemons[pokemonsAleatorios[1]], *pokemons[pokemonsAleatorios[2]]);
                random = rand();
                pokemonInicial[1] = random%3;
                batalhar[0]->selecionarPokemon(pokemonInicial[1]+1);
                break;
            }
        }
        else{
          x = 0;
        }
        }
      }
    }
  }
}