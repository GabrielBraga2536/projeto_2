#include <iostream>
#include "Pokemon.hpp"
#include "PokemonAgua.hpp"
#include "PokemonDragao.hpp"
#include "PokemonFantasma.hpp"
#include "PokemonFogo.hpp"
#include "PokemonPlanta.hpp"
#include "Treinador.hpp"
#include "Batalha.hpp"

using namespace std;


int main(){
  Ataque ataque1(120);
  Ataque ataque2(110);
  Ataque ataque3(100);
  Ataque ataque4(1222);
  PokemonPlanta Serperior(1, "Serperior", 96, 100, 2, 4, 12, ataque1, ataque2, ataque3, ataque4);
  PokemonFogo Emboar(2, "Emboar", 97, 100, 2, 16, 11, ataque1, ataque2, ataque3, ataque4);
  PokemonAgua Samurott(3, "Samurott", 100, 100, 2, 4, 12, ataque1, ataque2, ataque3, ataque4);
  PokemonFantasma Cofagrigus(4, "Cofagrigus", 98, 100, 2, 4, 12, ataque1, ataque2, ataque3, ataque4);
  PokemonDragao Hydreigon(5, "Hydreigon", 99, 100, 2, 16, 11, ataque1, ataque2, ataque3, ataque4);

  //Escolha da Equipe pelos IDs
  Treinador Treinador1(1, 2, 3);
  Treinador Treinador2(4, 5, 1);

  Treinador *treinador[2];
  treinador[0] = &Treinador1;
  treinador[1] = &Treinador2;

  Pokemon *pokemons[5];
  pokemons[0] = &Serperior;
  pokemons[1] = &Emboar;
  pokemons[2] = &Samurott;
  pokemons[3] = &Cofagrigus;
  pokemons[4] = &Hydreigon;

  //Exemplo de selecionar pokemons
  treinador[0]->selecionarPokemon(2);
  treinador[1]->selecionarPokemon(3);

  //Exemplo de Ataque
  cout << pokemons[treinador[1]->getPokemonID()-1]->getCurrentHp() << endl;
  pokemons[treinador[1]->getPokemonID()-1]->receberDano(pokemons[treinador[0]->getPokemonID()-1]->calcularDano(3), pokemons[treinador[0]->getPokemonID()-1]->getTipo());
  cout << pokemons[treinador[1]->getPokemonID()-1]->getCurrentHp() << endl;
}