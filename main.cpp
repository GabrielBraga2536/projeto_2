#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <time.h>

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
  
  // Cria e abre um arquivo em modo de escrita
  ofstream logFile;
  logFile.open("files/logs.txt", ofstream::out | ofstream::trunc); // Abre o arquivo em modo de escrita e apaga o conteúdo anterior
  
  // Verifica se o arquivo foi aberto corretamente
  if (!logFile.is_open()) { cerr << "Erro ao abrir o arquivo!" << endl; return -1; }
  
  // Escreve no arquivo a data do dia em que o programa foi compilado
  logFile << "Logs para o dia: " << __DATE__ << endl;
  
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

  Itens pocaoDeCura(5);
  Itens pocaoDeCuraMax(2);
  Itens revive(5);
  Itens reviveMax(2);
  
  Treinador *treinador[2]; // Vetor que armazena os treinadores
  
  Pokemon* pokemonsAliados[5];
  pokemonsAliados[0] = new PokemonPlanta(0, "Serperior", 150, 150, 85, 85, 113, ataque1, ataque6, ataque3, ataque8, pularAtaque);
  pokemonsAliados[1] = new PokemonFogo(1, "Emboar", 220, 220, 93, 82, 65, ataque5, ataque6, ataque7, ataque4, pularAtaque);
  pokemonsAliados[2] = new PokemonAgua(2, "Samurott", 190, 190, 92, 89, 70, ataque5, ataque2, ataque7, ataque4, pularAtaque);
  pokemonsAliados[3] = new PokemonFantasma(3, "Cofagrigus", 116, 116, 97, 100, 30, ataque1, ataque6, ataque3, ataque8, pularAtaque);
  pokemonsAliados[4] = new PokemonDragao(4, "Haxorus", 184, 184, 97, 107, 98, ataque1, ataque2, ataque3, ataque8, pularAtaque);
  
  Pokemon* pokemonsInimigos[5];
  pokemonsInimigos[0] = new PokemonPlanta(0, "Serperior", 150, 150, 85, 85, 113, ataque1, ataque6, ataque3, ataque8, pularAtaque);
  pokemonsInimigos[1] = new PokemonFogo(1, "Emboar", 220, 220, 93, 82, 65, ataque5, ataque6, ataque7, ataque4, pularAtaque);
  pokemonsInimigos[2] = new PokemonAgua(2, "Samurott", 190, 190, 92, 89, 70, ataque5, ataque2, ataque7, ataque4, pularAtaque);
  pokemonsInimigos[3] = new PokemonFantasma(3, "Cofagrigus", 116, 116, 97, 100, 30, ataque1, ataque6, ataque3, ataque8, pularAtaque);
  pokemonsInimigos[4] = new PokemonDragao(4, "Haxorus", 184, 184, 97, 107, 98, ataque1, ataque2, ataque3, ataque8, pularAtaque);
  
  vector<Pokemon*> pokemonsEscolhidos; // Vetor que armazena os pokemons escolhidos pelo jogador
  pokemonsEscolhidos.reserve(3); // Reserva espaço para 3 pokemons no vetor
  pokemonsEscolhidos[0] = nullptr;
  pokemonsEscolhidos[1] = nullptr;
  pokemonsEscolhidos[2] = nullptr;
  
  
  Pokemon* equipeInimiga[3]; // Vetor que armazena os pokemons da equipe inimiga
  int random;
  // colocar seed para time(0)
  srand(time(0));
  for(int i = 0; i < 3; i++){
    do{
      random = rand() % 5;
    } while (equipeInimiga[i] == pokemonsInimigos[random]);
    equipeInimiga[i] = pokemonsInimigos[random]; // Adiciona os pokemons da equipe inimiga no vetor
  }
  
  treinador[1] = new Treinador(equipeInimiga[0], equipeInimiga[1], equipeInimiga[2], pocaoDeCura, pocaoDeCuraMax, revive, reviveMax); // Cria o treinador inimigo
  
  SDL_Color white = {255, 255, 255, 255}; // Cor branca para o texto 
  SDL_Color black = {0, 0, 0, 255}; // Cor preta para o texto
  
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

  SDL_Texture* imgBattleBackground = IMG_LoadTexture(renderer, "imgs/battle/battle_background.jpg");
  
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
  
  SDL_Texture* img0_Front = IMG_LoadTexture(renderer, "imgs/pokemon_front/0.png");
  checkTexture(img0_Front);
  
  SDL_Texture* img1_Front = IMG_LoadTexture(renderer, "imgs/pokemon_front/1.png");
  checkTexture(img1_Front);
  
  SDL_Texture* img2_Front = IMG_LoadTexture(renderer, "imgs/pokemon_front/2.png");
  checkTexture(img2_Front);
  
  SDL_Texture* img3_Front = IMG_LoadTexture(renderer, "imgs/pokemon_front/3.png");
  checkTexture(img3_Front);
  
  SDL_Texture* img4_Front = IMG_LoadTexture(renderer, "imgs/pokemon_front/4.png");
  checkTexture(img4_Front);
  
  SDL_Texture* img0_Back = IMG_LoadTexture(renderer, "imgs/pokemon_back/0.png");
  checkTexture(img0_Back);
  
  SDL_Texture* img1_Back = IMG_LoadTexture(renderer, "imgs/pokemon_back/1.png");
  checkTexture(img1_Back);
  
  SDL_Texture* img2_Back = IMG_LoadTexture(renderer, "imgs/pokemon_back/2.png");
  checkTexture(img2_Back);
  
  SDL_Texture* img3_Back = IMG_LoadTexture(renderer, "imgs/pokemon_back/3.png");
  checkTexture(img3_Back);
  
  SDL_Texture* img4_Back = IMG_LoadTexture(renderer, "imgs/pokemon_back/4.png");
  checkTexture(img4_Back);
  
  SDL_Texture* img_Choice_Box = IMG_LoadTexture(renderer, "imgs/battle/choice_text_box.png");
  checkTexture(img_Choice_Box);
  
  SDL_Texture* img_Ally_Hp = IMG_LoadTexture(renderer, "imgs/battle/ally_hp_bar_white.png");
  checkTexture(img_Ally_Hp);
  
  SDL_Texture* img_Enemy_Hp = IMG_LoadTexture(renderer, "imgs/battle/enemy_hp_bar_white.png");
  checkTexture(img_Enemy_Hp);
  
  SDL_Texture* img_Selection_Cursor = IMG_LoadTexture(renderer, "imgs/battle/selection_cursor.png");
  checkTexture(img_Selection_Cursor);
  
  SDL_Texture* img_Generic_Hp_Bar = IMG_LoadTexture(renderer, "imgs/battle/generic_hp_bar.png");
  checkTexture(img_Generic_Hp_Bar);
  
  SDL_Texture * img_Pokemon_Front, * img_Pokemon_Back; // Variáveis que armazenam as imagens dos pokemons que serão exibidos na tela
  
  SDL_Rect rectBackground, rect_Battle_Box, rect_pokemon_front, rect_Choice_Box, rect_pokemon_back, rect_text, rect_ally_hp, rect_enemy_hp, rect_battle_cursor,
  rect_ally_name, rect_enemy_name, rect_ally_hp_bar, rect_enemy_hp_bar, rect_ally_hp_green, rect_enemy_hp_green, rect_ataque_1, rect_ataque_2, rect_ataque_3, rect_ataque_4,
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
  
  rect_Battle_Box.x = 0;
  rect_Battle_Box.y = 357;
  rect_Battle_Box.w = window_width;
  rect_Battle_Box.h = 123;
  
  rect_pokemon_front.x = 390;
  rect_pokemon_front.y = 110;
  rect_pokemon_front.w = 164;
  rect_pokemon_front.h = 164;
  
  rect_Choice_Box.x = 360 ;
  rect_Choice_Box.y = 360;
  rect_Choice_Box.w = window_width/2;
  rect_Choice_Box.h = 120;
  
  rect_pokemon_back.x = 100;
  rect_pokemon_back.y = 200;
  rect_pokemon_back.w = 240;
  rect_pokemon_back.h = 240;
  
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
  
  rect_ally_hp_green.x = 484;
  rect_ally_hp_green.y = 298;
  rect_ally_hp_green.w = 119;
  rect_ally_hp_green.h = 10;
  
  rect_enemy_hp_green.x = 168;
  rect_enemy_hp_green.y = 76;
  rect_enemy_hp_green.w = 111;
  rect_enemy_hp_green.h = 10;
  
  rect_ataque_1.x = 85;
  rect_ataque_1.y = 388;
  rect_ataque_1.w = 100;
  rect_ataque_1.h = 25;
  
  rect_ataque_2.x = 285;
  rect_ataque_2.y = 388;
  rect_ataque_2.w = 100;
  rect_ataque_2.h = 25;
  
  rect_ataque_3.x = 85;
  rect_ataque_3.y = 428;
  rect_ataque_3.w = 100;
  rect_ataque_3.h = 25;
  
  rect_ataque_4.x = 285;
  rect_ataque_4.y = 428;
  rect_ataque_4.w = 100;
  rect_ataque_4.h = 25;
  
  SDL_Surface* surfaceMessageTop = TTF_RenderText_Solid(font, "", white);
  SDL_Surface* allyNameSurface;
  SDL_Surface* enemyNameSurface;
  SDL_Surface* startMessageTxt = TTF_RenderText_Solid(font, "Press Enter", white);
  SDL_Surface* ataque1Surface = TTF_RenderText_Solid(font, "Ataque 1", black);
  SDL_Surface* ataque2Surface = TTF_RenderText_Solid(font, "Ataque 2", black);
  SDL_Surface* ataque3Surface = TTF_RenderText_Solid(font, "Ataque 3", black);
  SDL_Surface* ataque4Surface = TTF_RenderText_Solid(font, "Ataque 4", black);
  SDL_Surface* surfaceMessageDano;
  
  SDL_Texture* MessageTop = SDL_CreateTextureFromSurface(renderer, surfaceMessageTop); 
  SDL_Texture* allyName;
  SDL_Texture* enemyName;
  SDL_Texture* startMessage = SDL_CreateTextureFromSurface(renderer, startMessageTxt); 
  SDL_Texture* ataque1Texture = SDL_CreateTextureFromSurface(renderer, ataque1Surface);
  SDL_Texture* ataque2Texture = SDL_CreateTextureFromSurface(renderer, ataque2Surface);
  SDL_Texture* ataque3Texture = SDL_CreateTextureFromSurface(renderer, ataque3Surface);
  SDL_Texture* ataque4Texture = SDL_CreateTextureFromSurface(renderer, ataque4Surface);
  
  int up = 1; // Variável que controla o movimento do texto "Press Start" na tela inicial
  int pokemonAliadoAtual = 0; // Variável que armazena o pokemon aliado atual na batalha, inicia com o primeiro pokemon do vetor
  int pokemonInimigoAtual = 0; // Variável que armazena o pokemon inimigo atual na batalha, inicia com o primeiro pokemon do vetor
  bool estado1 = false; // Variável que controla o estado da tela de seleção de pokemons
  bool estado2 = false; // Variável que controla o estado da tela de batalha
  bool estadoSelecionaAtaque = false; // Variável que controla o estado da tela de seleção de ataques
  bool turnoOponente = false; // Variável que controla o turno do oponente

  string mensagemDano; // Variável que armazena a mensagem de dano causado pelo ataque
  
  while(true){ // Loop principal do jogo
    
    SDL_Event event0; // Variável que armazena os eventos do teclado
    while(SDL_PollEvent(&event0)){
      if( event0.type == SDL_QUIT ){ exit(0); }
      
      if (event0.type == SDL_KEYDOWN && event0.key.keysym.sym == SDLK_RETURN){
        estado1 = true;
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
              else if(event1.key.keysym.sym == SDLK_RCTRL){
                estado1 = false;
                estado2 = true;
                treinador[0] == new Treinador(pokemonsEscolhidos[0], pokemonsEscolhidos[1], pokemonsEscolhidos[2], pocaoDeCura, pocaoDeCuraMax, revive, reviveMax);
              }
              else if(event1.key.keysym.sym == SDLK_RETURN){
                if(pokemonsEscolhidos.size() == pokemonsEscolhidos.capacity()){ break; }
                switch (rect_hand_cursor.x){
                case 100:
                  if(rect_0_mini.x == position_choosed_x1 || rect_0_mini.x == position_choosed_x2 || rect_0_mini.x == position_choosed_x3){
                    if(rect_0_mini.x == position_choosed_x1){pokemonsEscolhidos[0] = nullptr;}
                    else if(rect_0_mini.x == position_choosed_x2){pokemonsEscolhidos[1] = nullptr;}
                    else if(rect_0_mini.x == position_choosed_x3){pokemonsEscolhidos[2] = nullptr;}
                    rect_0_mini.x = 80;
                    rect_0_mini.y = 140;
                    break;
                  }
                  
                  if(pokemonsEscolhidos[0] == NULL){
                    pokemonsEscolhidos[0] = pokemonsAliados[0];
                    rect_0_mini.x = position_choosed_x1;
                    rect_0_mini.y = position_choosed_y;
                    break;
                  }
                  else if(pokemonsEscolhidos[1] == NULL && pokemonsEscolhidos[0] != 0){
                    pokemonsEscolhidos[1] = pokemonsAliados[0];
                    rect_0_mini.x = position_choosed_x2;
                    rect_0_mini.y = position_choosed_y;
                    break;
                  }
                  else if(pokemonsEscolhidos[2] == NULL && pokemonsEscolhidos[0] != 0 && pokemonsEscolhidos[1] != 0){
                    cout << pokemonsEscolhidos[1];
                    pokemonsEscolhidos[2] = pokemonsAliados[0];
                    rect_0_mini.x = position_choosed_x3;
                    rect_0_mini.y = position_choosed_y;
                    break;
                  }
                  break;
                case 200:
                  if(rect_1_mini.x == position_choosed_x1 || rect_1_mini.x == position_choosed_x2 || rect_1_mini.x == position_choosed_x3){
                    if(rect_1_mini.x == position_choosed_x1){pokemonsEscolhidos[0] = nullptr;}
                    else if(rect_1_mini.x == position_choosed_x2){pokemonsEscolhidos[1] = nullptr;}
                    else if(rect_1_mini.x == position_choosed_x3){pokemonsEscolhidos[2] = nullptr;}
                    rect_1_mini.x = 180;
                    rect_1_mini.y = 140;
                    break;
                  }
                  
                  if(pokemonsEscolhidos[0] == NULL){
                    pokemonsEscolhidos[0] = pokemonsAliados[1];
                    rect_1_mini.x = position_choosed_x1;
                    rect_1_mini.y = position_choosed_y;
                    break;
                  }
                  else if(pokemonsEscolhidos[1] == nullptr && pokemonsEscolhidos[0] != 0){
                    pokemonsEscolhidos[1] = pokemonsAliados[1];
                    rect_1_mini.x = position_choosed_x2;
                    rect_1_mini.y = position_choosed_y;
                    break;
                  }
                  else if(pokemonsEscolhidos[2] == NULL && pokemonsEscolhidos[0] != 0 && pokemonsEscolhidos[1] != 0){
                    pokemonsEscolhidos[2] = pokemonsAliados[1];
                    rect_1_mini.x = position_choosed_x3;
                    rect_1_mini.y = position_choosed_y;
                    break;
                  }
                  
                  break;
                case 300:
                  if(rect_2_mini.x == position_choosed_x1 || rect_2_mini.x == position_choosed_x2 || rect_2_mini.x == position_choosed_x3){
                    if(rect_2_mini.x == position_choosed_x1){pokemonsEscolhidos[0] = NULL;}
                    else if(rect_2_mini.x == position_choosed_x2){pokemonsEscolhidos[1] = NULL;}
                    else if(rect_2_mini.x == position_choosed_x3){pokemonsEscolhidos[2] = NULL;}
                    rect_2_mini.x = 280;
                    rect_2_mini.y = 140;
                    pokemonsEscolhidos.erase(pokemonsEscolhidos.begin());
                    break;
                  }
                  
                  if(pokemonsEscolhidos[0] == NULL){
                    pokemonsEscolhidos[0] = pokemonsAliados[2];
                    rect_2_mini.x = position_choosed_x1;
                    rect_2_mini.y = position_choosed_y;
                    break;
                  }
                  else if(pokemonsEscolhidos[1] == NULL && pokemonsEscolhidos[0] != 0){
                    pokemonsEscolhidos[1] = pokemonsAliados[2];
                    rect_2_mini.x = position_choosed_x2;
                    rect_2_mini.y = position_choosed_y;
                    break;
                  }
                  else if(pokemonsEscolhidos[2] == NULL && pokemonsEscolhidos[0] != 0 && pokemonsEscolhidos[1] != 0){
                    pokemonsEscolhidos[2] = pokemonsAliados[2];
                    rect_2_mini.x = position_choosed_x3;
                    rect_2_mini.y = position_choosed_y;
                    break;
                  }
                  
                  break;
                case 400:
                  if(rect_3_mini.x == position_choosed_x1 || rect_3_mini.x == position_choosed_x2 || rect_3_mini.x == position_choosed_x3){
                    if(rect_3_mini.x == position_choosed_x1){pokemonsEscolhidos[0] = NULL;}
                    else if(rect_3_mini.x == position_choosed_x2){pokemonsEscolhidos[1] = NULL;}
                    else if(rect_3_mini.x == position_choosed_x3){pokemonsEscolhidos[2] = NULL;}
                    rect_3_mini.x = 380;
                    rect_3_mini.y = 140;
                    break;
                  }
                  
                  if(pokemonsEscolhidos[0] == NULL){
                    pokemonsEscolhidos[0] = pokemonsAliados[3];
                    rect_3_mini.x = position_choosed_x1;
                    rect_3_mini.y = position_choosed_y;
                    break;
                  }
                  else if(pokemonsEscolhidos[1] == NULL && pokemonsEscolhidos[0] != 0){
                    pokemonsEscolhidos[1] = pokemonsAliados[3];
                    rect_3_mini.x = position_choosed_x2;
                    rect_3_mini.y = position_choosed_y;
                    break;
                  }
                  else if(pokemonsEscolhidos[2] == NULL && pokemonsEscolhidos[0] != 0 && pokemonsEscolhidos[1] != 0){
                    pokemonsEscolhidos[2] = pokemonsAliados[3];
                    rect_3_mini.x = position_choosed_x3;
                    rect_3_mini.y = position_choosed_y;
                    break;
                  }
                  
                  break;
                case 500:
                  if(rect_4_mini.x == position_choosed_x1 || rect_4_mini.x == position_choosed_x2 || rect_4_mini.x == position_choosed_x3){
                    if(rect_4_mini.x == position_choosed_x1){pokemonsEscolhidos[0] = NULL;}
                    else if(rect_4_mini.x == position_choosed_x2){pokemonsEscolhidos[1] = NULL;}
                    else if(rect_4_mini.x == position_choosed_x3){pokemonsEscolhidos[2] = NULL;}
                    rect_4_mini.x = 480;
                    rect_4_mini.y = 140;
                    break;
                  }
                  
                  if(pokemonsEscolhidos[0] == NULL){
                    pokemonsEscolhidos[0] = pokemonsAliados[4];
                    rect_4_mini.x = position_choosed_x1;
                    rect_4_mini.y = position_choosed_y;
                    break;
                  }
                  else if(pokemonsEscolhidos[1] == NULL && pokemonsEscolhidos[0] != 0){
                    pokemonsEscolhidos[1] = pokemonsAliados[4];
                    rect_4_mini.x = position_choosed_x2;
                    rect_4_mini.y = position_choosed_y;
                    break;
                  }
                  else if(pokemonsEscolhidos[2] == NULL && pokemonsEscolhidos[0] != 0 && pokemonsEscolhidos[1] != 0){
                    pokemonsEscolhidos[2] = pokemonsAliados[4];
                    rect_4_mini.x = position_choosed_x3;
                    rect_4_mini.y = position_choosed_y;
                    break;  
                  }
                  
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
        
        if(pokemonsEscolhidos[pokemonAliadoAtual]->getNome() == "Serperior"){ img_Pokemon_Back = IMG_LoadTexture(renderer, "imgs/pokemon_back/0.png"); checkTexture(img_Pokemon_Back);}
        else if(pokemonsEscolhidos[pokemonAliadoAtual]->getNome() == "Emboar"){ img_Pokemon_Back = IMG_LoadTexture(renderer, "imgs/pokemon_back/1.png"); checkTexture(img_Pokemon_Back);}
        else if(pokemonsEscolhidos[pokemonAliadoAtual]->getNome() == "Samurott"){ img_Pokemon_Back = IMG_LoadTexture(renderer, "imgs/pokemon_back/2.png"); checkTexture(img_Pokemon_Back);}
        else if(pokemonsEscolhidos[pokemonAliadoAtual]->getNome() == "Cofagrigus"){ img_Pokemon_Back = IMG_LoadTexture(renderer, "imgs/pokemon_back/3.png"); checkTexture(img_Pokemon_Back);}
        else if(pokemonsEscolhidos[pokemonAliadoAtual]->getNome() == "Haxorus"){ img_Pokemon_Back = IMG_LoadTexture(renderer, "imgs/pokemon_back/4.png"); checkTexture(img_Pokemon_Back);}
        
        if(equipeInimiga[pokemonInimigoAtual]->getNome() == "Serperior"){ img_Pokemon_Front = IMG_LoadTexture(renderer, "imgs/pokemon_front/0.png"); checkTexture(img_Pokemon_Front);}
        else if(equipeInimiga[pokemonInimigoAtual]->getNome() == "Emboar"){ img_Pokemon_Front = IMG_LoadTexture(renderer, "imgs/pokemon_front/1.png"); checkTexture(img_Pokemon_Front);}
        else if(equipeInimiga[pokemonInimigoAtual]->getNome() == "Samurott"){ img_Pokemon_Front = IMG_LoadTexture(renderer, "imgs/pokemon_front/2.png"); checkTexture(img_Pokemon_Front);}
        else if(equipeInimiga[pokemonInimigoAtual]->getNome() == "Cofagrigus"){ img_Pokemon_Front = IMG_LoadTexture(renderer, "imgs/pokemon_front/3.png"); checkTexture(img_Pokemon_Front);}
        else if(equipeInimiga[pokemonInimigoAtual]->getNome() == "Haxorus"){ img_Pokemon_Front = IMG_LoadTexture(renderer, "imgs/pokemon_front/4.png"); checkTexture(img_Pokemon_Front);}
        
        
        while(estado2){
          
          SDL_Event event2;
          while(SDL_PollEvent(&event2)){
            if(event2.type == SDL_QUIT){ exit(0); }
            else if(event2.type == SDL_KEYDOWN){
              switch(event2.key.keysym.sym){
                case SDLK_UP:
                  rect_battle_cursor.y = 392;
                  break;
                case SDLK_DOWN:
                  rect_battle_cursor.y = 432;
                  break;
                case SDLK_RETURN:
                  if(rect_battle_cursor.y == 392){
                    estadoSelecionaAtaque = true;
                    imgBattleTextBox = IMG_LoadTexture(renderer, "imgs/battle/battle_attack_box.png");
                    checkTexture(imgBattleTextBox);
                    rect_battle_cursor.x = 60;
                    rect_battle_cursor.y = 388;
                    
                    while(estadoSelecionaAtaque){
                      
                      SDL_Event event3;
                      while(SDL_PollEvent(&event3)){
                        if(event3.type == SDL_QUIT){ exit(0); }
                        else if(event3.type == SDL_KEYDOWN){
                          switch (event3.key.keysym.sym){
                          case SDLK_LEFT:
                            rect_battle_cursor.x = 60;
                            break;
                          case SDLK_RIGHT:
                            rect_battle_cursor.x = 265;
                            break;
                          case SDLK_UP:
                            rect_battle_cursor.y = 388;
                            break;
                          case SDLK_DOWN:
                            rect_battle_cursor.y = 428;
                            break;
                          case SDLK_BACKSPACE:
                            estadoSelecionaAtaque = false;
                            rect_battle_cursor.x = 510;
                            rect_battle_cursor.y = 392;
                            break;
                          case SDLK_RETURN:
                            switch(rect_battle_cursor.y){
                              case 388:
                                switch(rect_battle_cursor.x){
                                case 60:
                                  random = rand();
                                  equipeInimiga[pokemonInimigoAtual]->receberDano(
                                    ataque1.Dano(
                                      random, 
                                      pokemonsEscolhidos[pokemonAliadoAtual]->getAtributoEspecial(),
                                      equipeInimiga[pokemonInimigoAtual]->getAtributoEspecial()
                                    ) 
                                  );
                                  mensagemDano = pokemonsEscolhidos[pokemonAliadoAtual]->getNome() + " causou " + to_string(ataque1.Dano(random, pokemonsEscolhidos[pokemonAliadoAtual]->getAtributoEspecial(), equipeInimiga[pokemonInimigoAtual]->getAtributoEspecial())) + " de dano";
                                  surfaceMessageDano = TTF_RenderText_Solid(font, mensagemDano.c_str(), white);
                                  MessageTop = SDL_CreateTextureFromSurface(renderer, surfaceMessageDano);
                                  SDL_FreeSurface(surfaceMessageDano);
                                  break;
                                case 265:
                                random = rand();
                                  equipeInimiga[pokemonInimigoAtual]->receberDano(
                                    ataque2.Dano(
                                      random, 
                                      pokemonsEscolhidos[pokemonAliadoAtual]->getAtributoEspecial(),
                                      equipeInimiga[pokemonInimigoAtual]->getAtributoEspecial()
                                    ) 
                                  );
                                  mensagemDano = pokemonsEscolhidos[pokemonAliadoAtual]->getNome() + " causou " + to_string(ataque2.Dano(random, pokemonsEscolhidos[pokemonAliadoAtual]->getAtributoEspecial(), equipeInimiga[pokemonInimigoAtual]->getAtributoEspecial())) + " de dano";
                                  surfaceMessageDano = TTF_RenderText_Solid(font, mensagemDano.c_str(), white);
                                  MessageTop = SDL_CreateTextureFromSurface(renderer, surfaceMessageDano);
                                  SDL_FreeSurface(surfaceMessageDano);
                                  break;
                                }
                                break;
                              case 428:
                                switch(rect_battle_cursor.x){
                                case 60:
                                random = rand();
                                  equipeInimiga[pokemonInimigoAtual]->receberDano(
                                    ataque3.Dano(
                                      random, 
                                      pokemonsEscolhidos[pokemonAliadoAtual]->getAtributoFisico(),
                                      equipeInimiga[pokemonInimigoAtual]->getAtributoFisico()
                                    ) 
                                  );
                                  mensagemDano = pokemonsEscolhidos[pokemonAliadoAtual]->getNome() + " causou " + to_string(ataque3.Dano(random, pokemonsEscolhidos[pokemonAliadoAtual]->getAtributoEspecial(), equipeInimiga[pokemonInimigoAtual]->getAtributoEspecial())) + " de dano";
                                  surfaceMessageDano = TTF_RenderText_Solid(font, mensagemDano.c_str(), white);
                                  MessageTop = SDL_CreateTextureFromSurface(renderer, surfaceMessageDano);
                                  SDL_FreeSurface(surfaceMessageDano);
                                break;
                                case 265:
                                random = rand();
                                  equipeInimiga[pokemonInimigoAtual]->receberDano(
                                    ataque4.Dano(
                                      random, 
                                      pokemonsEscolhidos[pokemonAliadoAtual]->getAtributoFisico(),
                                      equipeInimiga[pokemonInimigoAtual]->getAtributoFisico()
                                    ) 
                                  );
                                  mensagemDano = pokemonsEscolhidos[pokemonAliadoAtual]->getNome() + " causou " + to_string(ataque4.Dano(random, pokemonsEscolhidos[pokemonAliadoAtual]->getAtributoEspecial(), equipeInimiga[pokemonInimigoAtual]->getAtributoEspecial())) + " de dano";
                                  surfaceMessageDano = TTF_RenderText_Solid(font, mensagemDano.c_str(), white);
                                  MessageTop = SDL_CreateTextureFromSurface(renderer, surfaceMessageDano);
                                  SDL_FreeSurface(surfaceMessageDano);
                                break;
                                }
                                break;
                              }
                          default:
                            if(equipeInimiga[pokemonInimigoAtual]->getCurrentHp() <= 0){
                              pokemonInimigoAtual++;
                              if(pokemonInimigoAtual == 3){
                                estado2 = false;
                                break;
                              }
                              if(equipeInimiga[pokemonInimigoAtual]->getNome() == "Serperior"){ img_Pokemon_Front = IMG_LoadTexture(renderer, "imgs/pokemon_front/0.png"); checkTexture(img_Pokemon_Front);}
                              else if(equipeInimiga[pokemonInimigoAtual]->getNome() == "Emboar"){ img_Pokemon_Front = IMG_LoadTexture(renderer, "imgs/pokemon_front/1.png"); checkTexture(img_Pokemon_Front);}
                              else if(equipeInimiga[pokemonInimigoAtual]->getNome() == "Samurott"){ img_Pokemon_Front = IMG_LoadTexture(renderer, "imgs/pokemon_front/2.png"); checkTexture(img_Pokemon_Front);}
                              else if(equipeInimiga[pokemonInimigoAtual]->getNome() == "Cofagrigus"){ img_Pokemon_Front = IMG_LoadTexture(renderer, "imgs/pokemon_front/3.png"); checkTexture(img_Pokemon_Front);}
                              else if(equipeInimiga[pokemonInimigoAtual]->getNome() == "Haxorus"){ img_Pokemon_Front = IMG_LoadTexture(renderer, "imgs/pokemon_front/4.png"); checkTexture(img_Pokemon_Front);}
                            }
                            imgBattleTextBox = IMG_LoadTexture(renderer, "imgs/battle/battle_text_box.png");
                            checkTexture(imgBattleTextBox);
                            
                            logFile << mensagemDano << endl;
                            logFile << "HP do " << equipeInimiga[pokemonInimigoAtual]->getNome() << ": " << equipeInimiga[pokemonInimigoAtual]->getCurrentHp() << endl;
                            rect_battle_cursor.x = 510;
                            rect_battle_cursor.y = 392;
                            estadoSelecionaAtaque = false;
                            turnoOponente = true;
                            break;
                          }
                        }
                      }
                      
                      SDL_RenderClear(renderer);
                      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                      SDL_RenderCopy(renderer, imgBattleBackground, NULL, &rectBackground);
                      SDL_RenderCopy(renderer, img_Pokemon_Front, NULL, &rect_pokemon_front);
                      SDL_RenderCopy(renderer, img_Pokemon_Back, NULL, &rect_pokemon_back);
                      SDL_RenderCopy(renderer, imgBattleTextBox, NULL, &rect_Battle_Box);
                      SDL_RenderCopy(renderer, ataque1Texture, NULL, &rect_ataque_1);
                      SDL_RenderCopy(renderer, ataque2Texture, NULL, &rect_ataque_2);
                      SDL_RenderCopy(renderer, ataque3Texture, NULL, &rect_ataque_3);
                      SDL_RenderCopy(renderer, ataque4Texture, NULL, &rect_ataque_4);
                      SDL_RenderCopy(renderer, img_Ally_Hp, NULL, &rect_ally_hp);
                      SDL_RenderCopy(renderer, img_Generic_Hp_Bar, NULL, &rect_ally_hp_green);
                      SDL_RenderCopy(renderer, img_Enemy_Hp, NULL, &rect_enemy_hp);
                      SDL_RenderCopy(renderer, img_Generic_Hp_Bar, NULL, & rect_enemy_hp_green);
                      SDL_RenderCopy(renderer, img_Selection_Cursor, NULL, &rect_battle_cursor);
                      SDL_RenderCopy(renderer, allyName, NULL, &rect_ally_name);
                      SDL_RenderCopy(renderer, enemyName, NULL, &rect_enemy_name);
                      SDL_RenderPresent(renderer); 
                      
                      SDL_RenderClear(renderer);
                    }  
                  }
                  break;
              }
            }
          }
          
          
          if(pokemonsEscolhidos[pokemonAliadoAtual]->getCurrentHp() <= 0){
            pokemonAliadoAtual++;
            if(pokemonAliadoAtual == 3){
              estado2 = false;
              break;
            }
            if(pokemonsEscolhidos[pokemonAliadoAtual]->getNome() == "Serperior"){ img_Pokemon_Back = IMG_LoadTexture(renderer, "imgs/pokemon_back/0.png"); checkTexture(img_Pokemon_Back);}
            else if(pokemonsEscolhidos[pokemonAliadoAtual]->getNome() == "Emboar"){ img_Pokemon_Back = IMG_LoadTexture(renderer, "imgs/pokemon_back/1.png"); checkTexture(img_Pokemon_Back);}
            else if(pokemonsEscolhidos[pokemonAliadoAtual]->getNome() == "Samurott"){ img_Pokemon_Back = IMG_LoadTexture(renderer, "imgs/pokemon_back/2.png"); checkTexture(img_Pokemon_Back);}
            else if(pokemonsEscolhidos[pokemonAliadoAtual]->getNome() == "Cofagrigus"){ img_Pokemon_Back = IMG_LoadTexture(renderer, "imgs/pokemon_back/3.png"); checkTexture(img_Pokemon_Back);}
            else if(pokemonsEscolhidos[pokemonAliadoAtual]->getNome() == "Haxorus"){ img_Pokemon_Back = IMG_LoadTexture(renderer, "imgs/pokemon_back/4.png"); checkTexture(img_Pokemon_Back);}
          }
          
          allyNameSurface = TTF_RenderText_Solid(font, pokemonsEscolhidos[pokemonAliadoAtual]->getNome().c_str(), white);
          allyName = SDL_CreateTextureFromSurface(renderer, allyNameSurface);
          SDL_FreeSurface(allyNameSurface);
          
          enemyNameSurface = TTF_RenderText_Solid(font, equipeInimiga[pokemonInimigoAtual]->getNome().c_str(), white);
          enemyName = SDL_CreateTextureFromSurface(renderer, enemyNameSurface);
          SDL_FreeSurface(enemyNameSurface);
          
          //Calcula a porcentagem de hp do pokemon aliado e inimigo para atualizar a barra de hp
          rect_ally_hp_green.w = (pokemonsEscolhidos[pokemonAliadoAtual]->getCurrentHp() * 119) / pokemonsEscolhidos[pokemonAliadoAtual]->getMaxHp();
          rect_enemy_hp_green.w = (equipeInimiga[pokemonInimigoAtual]->getCurrentHp() * 111) / equipeInimiga[pokemonInimigoAtual]->getMaxHp();
          
          // Batalha batalha(pokemonsEscolhidos, equipeInimiga);
          SDL_RenderClear(renderer);
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
          SDL_RenderCopy(renderer, imgBattleBackground, NULL, &rectBackground);
          SDL_RenderCopy(renderer, img_Pokemon_Front, NULL, &rect_pokemon_front);
          SDL_RenderCopy(renderer, img_Pokemon_Back, NULL, &rect_pokemon_back);
          SDL_RenderCopy(renderer, imgBattleTextBox, NULL, &rect_Battle_Box);
          SDL_RenderCopy(renderer, img_Choice_Box, NULL, &rect_Choice_Box);
          SDL_RenderCopy(renderer, img_Ally_Hp, NULL, &rect_ally_hp);
          SDL_RenderCopy(renderer, img_Generic_Hp_Bar, NULL, &rect_ally_hp_green);
          SDL_RenderCopy(renderer, img_Enemy_Hp, NULL, &rect_enemy_hp);
          SDL_RenderCopy(renderer, img_Generic_Hp_Bar, NULL, & rect_enemy_hp_green);
          SDL_RenderCopy(renderer, img_Selection_Cursor, NULL, &rect_battle_cursor);
          SDL_RenderCopy(renderer, allyName, NULL, &rect_ally_name);
          SDL_RenderCopy(renderer, enemyName, NULL, &rect_enemy_name);
          SDL_RenderCopy(renderer, MessageTop, NULL, &rect_text);
          SDL_RenderPresent(renderer); 
          
          // Verifica se o turno é do oponente e executa um ataque aleatório
          if(turnoOponente){
            //sleep(1);
            random = rand();
            
            if(random%100 < 25){
              pokemonsEscolhidos[pokemonAliadoAtual]->receberDano(
                ataque1.Dano(
                  random, 
                  equipeInimiga[pokemonInimigoAtual]->getAtributoEspecial(),
                  pokemonsEscolhidos[pokemonAliadoAtual]->getAtributoEspecial()
                ) 
              );
              mensagemDano = equipeInimiga[pokemonInimigoAtual]->getNome() + " causou " + to_string(ataque1.Dano(random, equipeInimiga[pokemonInimigoAtual]->getAtributoEspecial(), pokemonsEscolhidos[pokemonAliadoAtual]->getAtributoEspecial())) + " de dano";
            }
            else if(random%100 >=25 &&random%100 < 50){
              pokemonsEscolhidos[pokemonAliadoAtual]->receberDano(
                ataque2.Dano(
                  random, 
                  equipeInimiga[pokemonInimigoAtual]->getAtributoEspecial(),
                  pokemonsEscolhidos[pokemonAliadoAtual]->getAtributoEspecial()
                ) 
              );
              mensagemDano = equipeInimiga[pokemonInimigoAtual]->getNome() + " causou " + to_string(ataque2.Dano(random, equipeInimiga[pokemonInimigoAtual]->getAtributoEspecial(), pokemonsEscolhidos[pokemonAliadoAtual]->getAtributoEspecial())) + " de dano";
            }
            else if(random%100>=50 && random%100 < 75){
              pokemonsEscolhidos[pokemonAliadoAtual]->receberDano(
                ataque3.Dano(
                  random, 
                  equipeInimiga[pokemonInimigoAtual]->getAtributoFisico(),
                  pokemonsEscolhidos[pokemonAliadoAtual]->getAtributoFisico()
                ) 
              );
              mensagemDano = equipeInimiga[pokemonInimigoAtual]->getNome() + " causou " + to_string(ataque3.Dano(random, equipeInimiga[pokemonInimigoAtual]->getAtributoFisico(), pokemonsEscolhidos[pokemonAliadoAtual]->getAtributoFisico())) + " de dano";
            }
            else{
              pokemonsEscolhidos[pokemonAliadoAtual]->receberDano(
                ataque4.Dano(
                  random, 
                  equipeInimiga[pokemonInimigoAtual]->getAtributoFisico(),
                  pokemonsEscolhidos[pokemonAliadoAtual]->getAtributoFisico()
                ) 
              );
              mensagemDano = equipeInimiga[pokemonInimigoAtual]->getNome() + " causou " + to_string(ataque4.Dano(random, equipeInimiga[pokemonInimigoAtual]->getAtributoFisico(), pokemonsEscolhidos[pokemonAliadoAtual]->getAtributoFisico())) + " de dano";
            }
            
            surfaceMessageDano = TTF_RenderText_Solid(font, mensagemDano.c_str(), white);
            MessageTop = SDL_CreateTextureFromSurface(renderer, surfaceMessageDano);
            SDL_FreeSurface(surfaceMessageDano);
            
            logFile << mensagemDano << endl;
            logFile << "HP do " << pokemonsEscolhidos[pokemonAliadoAtual]->getNome() << ": " << pokemonsEscolhidos[pokemonAliadoAtual]->getCurrentHp() << endl;
            turnoOponente = false;
          }
        }
      }
      
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
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyTexture(imgStartScreen);
  SDL_DestroyTexture(imgPokemonSelection);
  SDL_DestroyTexture(imgBattleTextBox);
  SDL_DestroyTexture(imgHandCursor);
  SDL_DestroyTexture(imgBattleBackground);
  SDL_DestroyTexture(img0_Mini);
  SDL_DestroyTexture(img1_Mini);
  SDL_DestroyTexture(img2_Mini);
  SDL_DestroyTexture(img3_Mini);
  SDL_DestroyTexture(img4_Mini);
  SDL_DestroyTexture(img0_Front);
  SDL_DestroyTexture(img1_Front);
  SDL_DestroyTexture(img2_Front);
  SDL_DestroyTexture(img3_Front);
  SDL_DestroyTexture(img4_Front);
  SDL_DestroyTexture(img0_Back);
  SDL_DestroyTexture(img1_Back);
  SDL_DestroyTexture(img2_Back);
  SDL_DestroyTexture(img3_Back);
  SDL_DestroyTexture(img4_Back);
  SDL_DestroyTexture(img_Choice_Box);
  SDL_DestroyTexture(img_Ally_Hp);
  SDL_DestroyTexture(img_Enemy_Hp);
  SDL_DestroyTexture(img_Selection_Cursor);
  SDL_DestroyTexture(img_Generic_Hp_Bar);
  SDL_DestroyTexture(MessageTop);
  SDL_DestroyTexture(allyName);
  SDL_DestroyTexture(enemyName);
  SDL_DestroyTexture(startMessage);
  SDL_DestroyTexture(imgStartScreen);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(font);
  SDL_Quit();
  
  // Fecha o arquivo
  logFile.close();
  
  pokemonsEscolhidos.clear();
  
  for (int i = 0; i < 3; i++){
    delete equipeInimiga[i];
  }
  
  for(int j = 0; j < 5; j++){
    delete pokemonsAliados[j];
    delete pokemonsInimigos[j];
  }
  
  return 0;
}