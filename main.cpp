#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

#define window_width 720 
#define window_height 480

int main(int argc, char** argv){
  SDL_Init(SDL_INIT_EVERYTHING); // Inicializa toda a SDL2
  TTF_Init(); // Inicializa a SDL2_ttf para carregar os arquivos de fonte
  
  
  SDL_Window* window = SDL_CreateWindow( // Cria a janela que será exibida no monitor durante a execução do programa
    "Projeto Monkepo",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    window_width, window_height,
    SDL_WINDOW_SHOWN
  );
  
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0); // Cria o renderizador que será responsável por desenhar na janela

  SDL_Texture* img = IMG_LoadTexture(renderer, "imgs/battle/battle_background.jpg"); // Carrega a imagem que será exibida na janela
  if( img == NULL ){
    cout << "Erro ao carregar imagem" << endl;
    return -1;
  }
  
  SDL_Texture* img2 = IMG_LoadTexture(renderer, "imgs/battle/battle_text_box.png");
  if( img2 == NULL ){
    cout << "Erro ao carregar imagem" << endl;
    return -1;
  }
  
  SDL_Texture* img3 = IMG_LoadTexture(renderer, "imgs/pokemon_front/4.png");
  if( img3 == NULL ){
    cout << "Erro ao carregar imagem" << endl;
    return -1;
  }
  
  SDL_Texture* img4 = IMG_LoadTexture(renderer, "imgs/battle/choice_text_box.png");
  if( img4 == NULL ){
    cout << "Erro ao carregar imagem" << endl;
    return -1;
  }
  
  SDL_Texture* img5 = IMG_LoadTexture(renderer, "imgs/pokemon_back/4.png");
  if( img5 == NULL ){
    cout << "Erro ao carregar imagem" << endl;
    return -1;
  }
  
  SDL_Texture* img6 = IMG_LoadTexture(renderer, "imgs/battle/ally_hp_bar_white.png");
  if( img6 == NULL ){
    cout << "Erro ao carregar imagem" << endl;
    return -1;
  }

  SDL_Texture* img7 = IMG_LoadTexture(renderer, "imgs/battle/enemy_hp_bar_white.png");
  if( img7 == NULL ){
    cout << "Erro ao carregar imagem" << endl;
    return -1;
  }

  SDL_Texture* img8 = IMG_LoadTexture(renderer, "imgs/battle/selection_cursor.png");
  if( img8 == NULL ){
    cout << "Erro ao carregar imagem" << endl;
    return -1;
  }
  
  SDL_Rect rect, rect2, rect3, rect4, rect5, rect_text, rect_ally_hp, rect_enemy_hp, rect_cursor,
  rect_ally_name, rect_enemy_name;
  rect.x = 0;
  rect.y = 0;
  rect.w = window_width;
  rect.h = window_height;
  
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
  
  rect_cursor.x = 510;
  rect_cursor.y = 392;
  rect_cursor.w = 20;
  rect_cursor.h = 20;
  
  rect_ally_name.x = 385;
  rect_ally_name.y = 265;
  rect_ally_name.w = 140;
  rect_ally_name.h = 25;
  
  rect_enemy_name.x = 110;
  rect_enemy_name.y = 45;
  rect_enemy_name.w = 140;
  rect_enemy_name.h = 25;
  
  TTF_Font* font = TTF_OpenFont("font/PKMN_RBYGSC.ttf", 100); // Carrega a fonte
  if( font == NULL ){
    cout << "Erro ao carregar a fonte" << endl;
    return -1;
  }
  
  SDL_Color white = {255, 255, 255, 255};
  
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "Haroxus tomou 100 de dano", white);
  SDL_Surface* allyMessage = TTF_RenderText_Solid(font, "Haxorus", white);
  SDL_Surface* enemyMessage = TTF_RenderText_Solid(font, "Haxorus", white);
  
  SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 
  SDL_Texture* allyName = SDL_CreateTextureFromSurface(renderer, allyMessage); 
  SDL_Texture* enemyName = SDL_CreateTextureFromSurface(renderer, enemyMessage); 
  
  while(true){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if( event.type == SDL_QUIT ){
        exit(0);
      }
      else if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){
          case SDLK_UP:
            rect_cursor.y = 392;
            break;
          case SDLK_DOWN:
            rect_cursor.y = 432;
            break;
        }
      }
      else if(event.type == SDL_KEYUP || rect_cursor.y == 392){
        switch(event.key.keysym.sym){
          case SDLK_RETURN:
            img2 = IMG_LoadTexture(renderer, "imgs/battle/battle_attack_box.png");
            img4 = IMG_LoadTexture(renderer, "");
            break;
        }
      }
    }
    
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 240, 250, 50, 255);
    SDL_SetRenderDrawColor(renderer, 9, 20, 33, 255);
    SDL_RenderCopy(renderer, img, NULL, &rect);
    SDL_RenderCopy(renderer, img5, NULL, &rect5);
    SDL_RenderCopy(renderer, img2, NULL, &rect2);
    SDL_RenderCopy(renderer, img3, NULL, &rect3);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderCopy(renderer, Message, NULL, &rect_text);
    SDL_RenderCopy(renderer, img4, NULL, &rect4);
    SDL_RenderCopy(renderer, img6, NULL, &rect_ally_hp);
    SDL_RenderCopy(renderer, img7, NULL, &rect_enemy_hp);
    SDL_RenderCopy(renderer, img8, NULL, &rect_cursor);
    SDL_RenderCopy(renderer, allyName, NULL, &rect_ally_name);
    SDL_RenderCopy(renderer, enemyName, NULL, &rect_enemy_name);
    SDL_RenderPresent(renderer);
  }
  
  SDL_DestroyTexture(img);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}