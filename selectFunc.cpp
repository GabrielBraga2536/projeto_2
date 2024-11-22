#include <iostream>
#include <vector>
#include <algorithm>

#include "Pokemon.hpp"
#include "Treinador.hpp"
#include "Itens.hpp"
#include "PokemonAgua.hpp"
#include "PokemonDragao.hpp"
#include "PokemonFantasma.hpp"
#include "PokemonFogo.hpp"
#include "PokemonPlanta.hpp"

using namespace std;

void selectPokemon(Pokemon* pokemons[5], vector<Pokemon*>& pokemonsEscolhidos, int escolha){
  if(escolha == 0){
    if(pokemonsEscolhidos[escolha] == NULL){
      pokemonsEscolhidos[escolha] = pokemons[0];
    }
    else if(pokemonsEscolhidos[escolha+1] == NULL && pokemonsEscolhidos[escolha] != NULL){
      pokemonsEscolhidos[escolha+1] = pokemons[0];
    }
    else if(pokemonsEscolhidos[escolha+2] == NULL && pokemonsEscolhidos[escolha+1] != NULL && pokemonsEscolhidos[escolha] != NULL){
      pokemonsEscolhidos[escolha+2] = pokemons[0];
    }
  }
  else if(escolha == 1){
    if(pokemonsEscolhidos[escolha] == NULL){
      pokemonsEscolhidos[escolha] = pokemons[1];
    }
    else if(pokemonsEscolhidos[escolha+1] == NULL && pokemonsEscolhidos[escolha] != NULL){
      pokemonsEscolhidos[escolha+1] = pokemons[1];
    }
    else if(pokemonsEscolhidos[escolha+2] == NULL){
      pokemonsEscolhidos[escolha+2] = pokemons[1];
    }
  }
}