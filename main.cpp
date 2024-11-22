#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Pokemon.hpp"
#include "Batalha.hpp"
#include "Ataque.hpp"
#include "Treinador.hpp"
#include "Itens.hpp"
#include "PokemonAgua.hpp"
#include "PokemonDragao.hpp"
#include "PokemonFantasma.hpp"
#include "PokemonFogo.hpp"
#include "PokemonPlanta.hpp"

#include "debug.cpp"

using namespace std; // Utiliza o namespace std para não precisar escrever std:: antes de funções como cout e endl

#define window_width 720 // Largura da janela do jogo
#define window_height 480 // Altura da janela do jogo

#define position_choosed_x1 100 // Posição x do primeiro pokemon escolhido
#define position_choosed_x2 200 // Posição x do segundo pokemon escolhido
#define position_choosed_x3 300 // Posição x do terceiro pokemon escolhido
#define position_choosed_y 5 // Posição y do pokemon escolhido (padrão 5 para qualquer pokemon escohlido)

int main(int argc, char** argv){
  SDL_Init(SDL_INIT_EVERYTHING); // Inicializa toda a SDL2
  TTF_Init(); // Inicializa a SDL2_ttf para carregar os arquivos de fonte para o texto
  
  // Cria os ataques que serão utilizados pelos pokemons
  Ataque ataque1(120, 96, "Especial");
  Ataque ataque2(110, 102, "Especial");
  Ataque ataque3(100, 115, "Especial");
  Ataque ataque4(90, 127, "Especial");
  Ataque ataque5(120, 96, "Fisico");
  Ataque ataque6(110, 102, "Fisico");
  Ataque ataque7(100, 115, "Fisico");
  Ataque ataque8(90, 127, "Fisico");
  Ataque pularAtaque(0, -1, "Fisico"); // Ataque que não causa dano e é utilizado para pular o turno
  
  Pokemon* pokemons[5];
  pokemons[0] = new PokemonPlanta(0, "Serperior", 150, 150, 85, 85, 113, ataque1, ataque6, ataque3, ataque8, pularAtaque);
  pokemons[1] = new PokemonFogo(1, "Emboar", 220, 220, 93, 82, 65, ataque5, ataque6, ataque7, ataque4, pularAtaque);
  pokemons[2] = new PokemonAgua(2, "Samurott", 190, 190, 92, 89, 70, ataque5, ataque2, ataque7, ataque4, pularAtaque);
  pokemons[3] = new PokemonFantasma(3, "Cofagrigus", 116, 116, 97, 100, 30, ataque1, ataque6, ataque3, ataque8, pularAtaque);
  pokemons[4] = new PokemonDragao(4, "Haxorus", 184, 184, 97, 107, 98, ataque1, ataque2, ataque3, ataque8, pularAtaque);
  
  vector<Pokemon*> pokemonsEscolhidos; // Vetor que armazena os pokemons escolhidos pelo jogador
  pokemonsEscolhidos.reserve(3); // Reserva espaço para 3 pokemons no vetor
  
  SDL_Color white = {255, 255, 255, 255}; // Cor branca para o texto 
  
  TTF_Font* font = TTF_OpenFont("font/PKMN_RBYGSC.ttf", 100); // Carrega a fonte que será utilizada para exibir o texto
  checkFont(font); // Verifica se a fonte foi carregada corretamente
  
  SDL_Window* window = SDL_CreateWindow( // Cria a janela que será exibida no monitor durante a execução do programa
    "Projeto Pokemon",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    window_width, window_height,
    SDL_WINDOW_SHOWN
  );
  checkWindow(window); // Verifica se a janela foi criada corretamente
  
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0); // Cria o renderizador que será responsável por desenhar na janela
  
  SDL_Texture* imgStartScreen = IMG_LoadTexture(renderer, "imgs/menu/start_screen.jpg"); // Carrega a imagem de fundo da tela inicial
  checkTexture(imgStartScreen);
  
  SDL_Texture* imgPokemonSelection = IMG_LoadTexture(renderer, "imgs/menu/pokemon_selection.png");
  checkTexture(imgPokemonSelection);
  
  SDL_Texture* imgBattleTextBox = IMG_LoadTexture(renderer, "imgs/battle/battle_text_box.png");
  checkTexture(imgBattleTextBox);
  
  SDL_Texture* imgHandCursor = IMG_LoadTexture(renderer, "imgs/menu/hand_cursor.png");
  checkTexture(imgHandCursor);
  
  SDL_Texture* img0_Mini = IMG_LoadTexture(renderer, "imgs/menu/0.png");
  checkTexture(img0_Mini);
  
  SDL_Texture* img1_Mini = IMG_LoadTexture(renderer, "imgs/menu/1.png");
  checkTexture(img1_Mini);
  
  SDL_Texture* img2_Mini = IMG_LoadTexture(renderer, "imgs/menu/2.png");
  checkTexture(img2_Mini);
  
  SDL_Texture* img3_Mini = IMG_LoadTexture(renderer, "imgs/menu/3.png");
  checkTexture(img3_Mini);
  
  SDL_Texture* img4_Mini = IMG_LoadTexture(renderer, "imgs/menu/4.png");
  checkTexture(img4_Mini);
  
  SDL_Texture* img3 = IMG_LoadTexture(renderer, "imgs/pokemon_front/4.png");
  checkTexture(img3);
  
  SDL_Texture* img4 = IMG_LoadTexture(renderer, "imgs/battle/choice_text_box.png");
  checkTexture(img4);
  
  SDL_Texture* img5 = IMG_LoadTexture(renderer, "imgs/pokemon_back/4.png");
  checkTexture(img5);
  
  SDL_Texture* img6 = IMG_LoadTexture(renderer, "imgs/battle/ally_hp_bar_white.png");
  checkTexture(img6);
  
  SDL_Texture* img7 = IMG_LoadTexture(renderer, "imgs/battle/enemy_hp_bar_white.png");
  checkTexture(img7);
  
  SDL_Texture* img8 = IMG_LoadTexture(renderer, "imgs/battle/selection_cursor.png");
  checkTexture(img8);
  
  SDL_Rect rectBackground, rect2, rect3, rect4, rect5, rect_text, rect_ally_hp, rect_enemy_hp, rect_battle_cursor,
  rect_ally_name, rect_enemy_name, rect_ally_hp_bar, rect_enemy_hp_bar, rect_ally_hp_bar_gray, rect_enemy_hp_bar_gray,
  rect_start_text, rect_hand_cursor, rect_0_mini, rect_1_mini, rect_2_mini, rect_3_mini, rect_4_mini;
  
  rectBackground.x = 0;
  rectBackground.y = 0;
  rectBackground.w = window_width;
  rectBackground.h = window_height;
  
  rect_0_mini.x = 80;
  rect_0_mini.y = 140;
  rect_0_mini.w = 60;
  rect_0_mini.h = 60;
  
  rect_1_mini.x = 180;
  rect_1_mini.y = 140;
  rect_1_mini.w = 60;
  rect_1_mini.h = 60;
  
  rect_2_mini.x = 280;
  rect_2_mini.y = 140;
  rect_2_mini.w = 60;
  rect_2_mini.h = 60;
  
  rect_3_mini.x = 380;
  rect_3_mini.y = 140;
  rect_3_mini.w = 60;
  rect_3_mini.h = 60;
  
  rect_4_mini.x = 480;
  rect_4_mini.y = 140;
  rect_4_mini.w = 60;
  rect_4_mini.h = 60;
  
  rect2.x = 0;
  rect2.y = 357;
  rect2.w = window_width;
  rect2.h = 123;
  
  rect3.x = 390;
  rect3.y = 110;
  rect3.w = 164;
  rect3.h = 164;
  
  rect4.x = 360 ;
  rect4.y = 360;
  rect4.w = window_width/2;
  rect4.h = 120;
  
  rect5.x = 100;
  rect5.y = 200;
  rect5.w = 240;
  rect5.h = 240;
  
  rect_text.x = 30;
  rect_text.y = 380;
  rect_text.w = 330;
  rect_text.h = 25;
  
  rect_ally_hp.x = 360;
  rect_ally_hp.y = 270;
  rect_ally_hp.w = 280;
  rect_ally_hp.h = 80;
  
  rect_enemy_hp.x = 80;
  rect_enemy_hp.y = 45;
  rect_enemy_hp.w = 240;
  rect_enemy_hp.h = 65;
  
  rect_battle_cursor.x = 510;
  rect_battle_cursor.y = 392;
  rect_battle_cursor.w = 20;
  rect_battle_cursor.h = 20;
  
  rect_hand_cursor.x = 100;
  rect_hand_cursor.y = 100;
  rect_hand_cursor.w = 40;
  rect_hand_cursor.h = 40;
  
  rect_ally_name.x = 385;
  rect_ally_name.y = 265;
  rect_ally_name.w = 140;
  rect_ally_name.h = 25;
  
  rect_enemy_name.x = 110;
  rect_enemy_name.y = 45;
  rect_enemy_name.w = 140;
  rect_enemy_name.h = 25;
  
  rect_start_text.x = window_width/2 - 70;
  rect_start_text.y = window_height/2 - 40;
  rect_start_text.w = 130;
  rect_start_text.h = 50;
  
  
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "Haroxus tomou 100 de dano", white);
  SDL_Surface* allyMessage = TTF_RenderText_Solid(font, "Haxorus", white);
  SDL_Surface* enemyMessage = TTF_RenderText_Solid(font, "Haxorus", white);
  SDL_Surface* startMessageTxt = TTF_RenderText_Solid(font, "Press Enter", white);
  
  SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 
  SDL_Texture* allyName = SDL_CreateTextureFromSurface(renderer, allyMessage); 
  SDL_Texture* enemyName = SDL_CreateTextureFromSurface(renderer, enemyMessage); 
  SDL_Texture* startMessage = SDL_CreateTextureFromSurface(renderer, startMessageTxt); 
  
  int up = 1; // Variável que controla o movimento do texto "Press Start" na tela inicial
  
  while(true){
    SDL_Event event0;
    while(SDL_PollEvent(&event0)){
      if( event0.type == SDL_QUIT ){ exit(0); }
      
      if (event0.type == SDL_KEYDOWN && event0.key.keysym.sym == SDLK_RETURN){
        bool estado1 = true;
        while(estado1){
          
          SDL_Event event1;
          while(SDL_PollEvent(&event1)){
            if( event1.type == SDL_QUIT ){ exit(0); } 
            else if(event1.type == SDL_KEYDOWN){
              if (event1.key.keysym.sym == SDLK_RIGHT && rect_hand_cursor.x < 480){
                rect_hand_cursor.x += 100;
              }
              else if (event1.key.keysym.sym == SDLK_LEFT && rect_hand_cursor.x > 100){
                rect_hand_cursor.x -= 100;
              }
              else if (event1.key.keysym.sym == SDLK_BACKSPACE){
                estado1 = false;
              }
              else if(event1.key.keysym.sym == SDLK_RETURN){
                if(pokemonsEscolhidos.size() == pokemonsEscolhidos.capacity()){ break; }
                switch (rect_hand_cursor.x){
                case 100:
                  if(pokemonsEscolhidos[0] == NULL){
                    pokemonsEscolhidos[0] = pokemons[0];
                    rect_0_mini.x = position_choosed_x1;
                    rect_0_mini.y = position_choosed_y;
                    break;
                  }
                  else if(pokemonsEscolhidos[1] == NULL && pokemonsEscolhidos[0] != NULL){
                    pokemonsEscolhidos[1] = pokemons[0];
                    rect_0_mini.x = position_choosed_x2;
                    rect_0_mini.y = position_choosed_y;
                    break;
                  }
                  else if(pokemonsEscolhidos[2] == NULL){
                    pokemonsEscolhidos[2] = pokemons[0];
                    rect_0_mini.x = position_choosed_x3;
                    rect_0_mini.y = position_choosed_y;
                    break;
                  }
                  if(rect_0_mini.x == position_choosed_x1){
                    rect_0_mini.x = 80;
                    rect_0_mini.y = 140;
                    break;
                  }
                  rect_0_mini.x = 100;
                  rect_0_mini.y = position_choosed_y;
                  break;
                case 200:
                  if(rect_1_mini.x == 200){
                    rect_1_mini.x = 180;
                    rect_1_mini.y = 140;
                    break;
                  }
                  rect_1_mini.x = 200;
                  rect_1_mini.y = position_choosed_y;
                  break;
                case 300:
                  if(rect_2_mini.x == 300){
                    rect_2_mini.x = 280;
                    rect_2_mini.y = 140;
                    break;
                  }
                  rect_2_mini.x = 300;
                  rect_2_mini.y = position_choosed_y;
                  break;
                case 400:
                  if(rect_3_mini.x == 400){
                    rect_3_mini.x = 380;
                    rect_3_mini.y = 140;
                    break;
                  }
                  rect_3_mini.x = 400;
                  rect_3_mini.y = position_choosed_y;
                  break;
                case 500:
                  if(rect_4_mini.x == 500){
                    rect_4_mini.x = 480;
                    rect_4_mini.y = 140;
                    break;
                  }
                  rect_4_mini.x = 500;
                  rect_4_mini.y = position_choosed_y;
                  break;
                default:
                  break;
                }
              }
            }
          }
          
          SDL_RenderClear(renderer);
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
          SDL_RenderCopy(renderer, imgPokemonSelection, NULL, &rectBackground);
          SDL_RenderCopy(renderer, img0_Mini, NULL, &rect_0_mini);
          SDL_RenderCopy(renderer, img1_Mini, NULL, &rect_1_mini);
          SDL_RenderCopy(renderer, img2_Mini, NULL, &rect_2_mini);
          SDL_RenderCopy(renderer, img3_Mini, NULL, &rect_3_mini);
          SDL_RenderCopy(renderer, img4_Mini, NULL, &rect_4_mini);
          SDL_RenderCopy(renderer, imgHandCursor, NULL, &rect_hand_cursor);
          SDL_RenderPresent(renderer);
        }
      }
      // else if(event0.type == SDL_KEYDOWN){
      //   switch(event0.key.keysym.sym){
      //     case SDLK_UP:
      //       rect_cursor.y = 392;
      //       break;
      //     case SDLK_DOWN:
      //       rect_cursor.y = 432;
      //       break;
      //   }
      // }
    }
    
    if (up == 1){
      rect_start_text.y++;
      if (rect_start_text.y > window_height/2 - 35){ up = 0; }
      usleep(90000); // sleep for 1 second
    }
    else if (up == 0){
      rect_start_text.y--;
      if (rect_start_text.y < window_height/2 - 40){ up = 1; }
      usleep(90000); // sleep for 1 second
    }
    
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 240, 250, 50, 255);
    SDL_SetRenderDrawColor(renderer, 9, 20, 33, 255);
    SDL_RenderCopy(renderer, imgStartScreen, NULL, &rectBackground);
    SDL_RenderCopy(renderer, startMessage, NULL, &rect_start_text);
    // SDL_RenderCopy(renderer, img5, NULL, &rect5);
    // SDL_RenderCopy(renderer, img2, NULL, &rect2);
    // SDL_RenderCopy(renderer, img3, NULL, &rect3);
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_RenderCopy(renderer, Message, NULL, &rect_text);
    // SDL_RenderCopy(renderer, img4, NULL, &rect4);
    // SDL_RenderCopy(renderer, img6, NULL, &rect_ally_hp);
    // SDL_RenderCopy(renderer, img7, NULL, &rect_enemy_hp);
    // SDL_RenderCopy(renderer, img8, NULL, &rect_cursor);
    // SDL_RenderCopy(renderer, allyName, NULL, &rect_ally_name);
    // SDL_RenderCopy(renderer, enemyName, NULL, &rect_enemy_name);
    SDL_RenderPresent(renderer);
  }
  
  SDL_DestroyTexture(imgStartScreen);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}