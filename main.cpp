#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

  SDL_Texture* img2 = IMG_LoadTexture(renderer, "imgs/battle/battle_text_box.png");
  if( img2 == NULL ){
    cout << "Erro ao carregar imagem" << endl;
    return -1;
  }
  
  SDL_Texture* img3 = IMG_LoadTexture(renderer, "imgs/pokemon_front/0.png");
  if( img3 == NULL ){
    cout << "Erro ao carregar imagem" << endl;
    return -1;
  }

  SDL_Rect rect, rect2, rect3;
  rect.x = 0;
  rect.y = 0;
  rect.w = window_width;
  rect.h = window_height;
  
  rect2.x = 0;
  rect2.y = 357;
  rect2.w = window_width;
  rect2.h = 123;
  
  rect3.x = 380;
  rect3.y = 115;
  rect3.w = 192;
  rect3.h = 192;

  while(true){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if( event.type == SDL_QUIT ){
        exit(0);
      }else if( event.type == SDL_MOUSEBUTTONDOWN ){
        rect2.x -= 20;
      }
    }
    
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 240, 250, 50, 255);
    SDL_SetRenderDrawColor(renderer, 9, 20, 33, 255);
    SDL_RenderCopy(renderer, img, NULL, &rect);
    SDL_RenderCopy(renderer, img2, NULL, &rect2);
    SDL_RenderCopy(renderer, img3, NULL, &rect3);
    SDL_RenderPresent(renderer);
  }
  
  SDL_DestroyTexture(img);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}