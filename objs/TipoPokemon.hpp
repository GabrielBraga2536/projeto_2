#pragma once 

#include <iostream>
#include <string>

using namespace std;

// Enumeração para TipoPokemon
enum class TipoPokemon {
  Fogo, Agua, Grama, Eletrico, Psiquico,
  Fantasma, Terra, Lutador, Voador, Normal,
  Sombrio, Dragao, Gelo, Pedra
};

// Função para converter TipoPokemon em string (para exibir na tela)
std::string tipoParaString(TipoPokemon tipo) {
  switch (tipo) {
    case TipoPokemon::Fogo: return "Fogo";
    case TipoPokemon::Agua: return "Água";
    case TipoPokemon::Grama: return "Grama";
    case TipoPokemon::Eletrico: return "Elétrico";
    case TipoPokemon::Psiquico: return "Psiquico";
    case TipoPokemon::Fantasma: return "Fantasma";
    case TipoPokemon::Terra: return "Terra";
    case TipoPokemon::Lutador: return "Lutador";
    case TipoPokemon::Voador: return "Voador";
    case TipoPokemon::Normal: return "Normal";
    case TipoPokemon::Sombrio: return "Sombrio";
    case TipoPokemon::Dragao: return "Dragão";
    case TipoPokemon::Gelo: return "Gelo";
    case TipoPokemon::Pedra: return "Pedra";
    default: return "Desconhecido";
  }
}

// Função que calcula a vantagem de tipo entre dois Tipos de Pokémon
// Retorna um multiplicador de dano com base nos tipos: 2.0 para vantagem, 0.5 para desvantagem, e 1.0 para neutro.
float calcularVantagemTipo(TipoPokemon atacante, TipoPokemon defensor) {
  // Casos de vantagem
  if (atacante == TipoPokemon::Fogo && (defensor == TipoPokemon::Grama || defensor == TipoPokemon::Gelo || defensor == TipoPokemon::Pedra)) return 2.0;
  if (atacante == TipoPokemon::Agua && (defensor == TipoPokemon::Fogo || defensor == TipoPokemon::Pedra || defensor == TipoPokemon::Terra)) return 2.0;
  if (atacante == TipoPokemon::Grama && (defensor == TipoPokemon::Agua || defensor == TipoPokemon::Pedra || defensor == TipoPokemon::Terra)) return 2.0;
  if (atacante == TipoPokemon::Eletrico && (defensor == TipoPokemon::Agua || defensor == TipoPokemon::Voador)) return 2.0;
  if (atacante == TipoPokemon::Psiquico && (defensor == TipoPokemon::Lutador || defensor == TipoPokemon::Sombrio)) return 2.0;
  if (atacante == TipoPokemon::Fantasma && (defensor == TipoPokemon::Psiquico || defensor == TipoPokemon::Fantasma)) return 2.0;
  if (atacante == TipoPokemon::Terra && (defensor == TipoPokemon::Fogo || defensor == TipoPokemon::Eletrico || defensor == TipoPokemon::Pedra)) return 2.0;
  if (atacante == TipoPokemon::Lutador && (defensor == TipoPokemon::Normal || defensor == TipoPokemon::Pedra || defensor == TipoPokemon::Gelo)) return 2.0;
  if (atacante == TipoPokemon::Voador && (defensor == TipoPokemon::Lutador || defensor == TipoPokemon::Grama)) return 2.0;
  if (atacante == TipoPokemon::Sombrio && defensor == TipoPokemon::Psiquico) return 2.0;
  if (atacante == TipoPokemon::Gelo && (defensor == TipoPokemon::Grama || defensor == TipoPokemon::Terra || defensor == TipoPokemon::Dragao)) return 2.0;
  if (atacante == TipoPokemon::Pedra && (defensor == TipoPokemon::Fogo || defensor == TipoPokemon::Gelo || defensor == TipoPokemon::Voador)) return 2.0;
  
  // Casos de desvantagem
  if (atacante == TipoPokemon::Fogo && (defensor == TipoPokemon::Agua || defensor == TipoPokemon::Pedra)) return 0.5;
  if (atacante == TipoPokemon::Agua && defensor == TipoPokemon::Grama) return 0.5;
  if (atacante == TipoPokemon::Grama && (defensor == TipoPokemon::Fogo || defensor == TipoPokemon::Voador)) return 0.5;
  if (atacante == TipoPokemon::Eletrico && defensor == TipoPokemon::Terra) return 0.5;
  if (atacante == TipoPokemon::Psiquico && defensor == TipoPokemon::Sombrio) return 0.5;
  if (atacante == TipoPokemon::Fantasma && defensor == TipoPokemon::Normal) return 0.5;
  if (atacante == TipoPokemon::Terra && defensor == TipoPokemon::Grama) return 0.5;
  if (atacante == TipoPokemon::Lutador && defensor == TipoPokemon::Voador) return 0.5;
  if (atacante == TipoPokemon::Gelo && defensor == TipoPokemon::Fogo) return 0.5;
  
  // Caso neutro (sem vantagem/desvantagem)
  return 1.0;
}