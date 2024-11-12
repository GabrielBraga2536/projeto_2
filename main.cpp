#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

#define window_width 720 
#define window_height 480

int main(int argc, char** argv){
  SDL_Init(SDL_INIT_EVERYTHING);
  
  SDL_Window* window = SDL_CreateWindow(
    "Projeto Monkepo",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    window_width, window_height,
    SDL_WINDOW_SHOWN
  );
  
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Texture* img = IMG_LoadTexture(renderer, "imgs/battle/battle_background.jpg");
  if( img == NULL ){
    cout << "Erro ao carregar imagem" << endl;
    return -1;
  }

  SDL_Texture* img2 = IMG_LoadTexture(renderer, "imgs/battle/battle_attack_box.png");
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

  SDL_Rect rect, rect2, rect3, rect4, rect5;
  rect.x = 0;
  rect.y = 0;
  rect.w = window_width;
  rect.h = window_height;
  
  rect2.x = 0;
  rect2.y = 357;
  rect2.w = window_width;
  rect2.h = 123;
  
  rect3.x = 390;
  rect3.y = 115;
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

  while(true){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if( event.type == SDL_QUIT ){
        exit(0);
      }
    }
    
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 240, 250, 50, 255);
    SDL_SetRenderDrawColor(renderer, 9, 20, 33, 255);
    SDL_RenderCopy(renderer, img, NULL, &rect);
    SDL_RenderCopy(renderer, img5, NULL, &rect5);
    SDL_RenderCopy(renderer, img2, NULL, &rect2);
    SDL_RenderCopy(renderer, img3, NULL, &rect3);
    //SDL_RenderCopy(renderer, img4, NULL, &rect4);
    SDL_RenderPresent(renderer);
  }
  
  SDL_DestroyTexture(img);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}