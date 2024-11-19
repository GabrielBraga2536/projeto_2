#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

int main(int argc, char** argv) {
  SDL_Init(SDL_INIT_EVERYTHING);
  
  TTF_Init();
  
  
  TTF_Font* font = TTF_OpenFont("font/PKMN_RBYGSC.ttf", 24);
  if( font == NULL ){
    std::cout << "Erro ao carregar a fonte" << std::endl;
    return -1;
  }
  
  SDL_Color White = {255, 255, 255};
  
  SDL_Window* window = SDL_CreateWindow(
    "Projeto Monkepo",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    720, 480,
    SDL_WINDOW_SHOWN
  );
  
  
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "Hello World", White);
  
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  
  SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
  
  SDL_Rect Message_rect; //create a rect
  Message_rect.x = 0;  //controls the rect's x coordinate 
  Message_rect.y = 0; // controls the rect's y coordinte
  Message_rect.w = 200; // controls the width of the rect
  Message_rect.h = 100; // controls the height of the rect
  
  while(true){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if( event.type == SDL_QUIT ){
        exit(0);
      }
    }
    
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_RenderPresent(renderer);
  }
  
  return 0;
}