#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

// Função para verificar se a textura foi carregada corretamente
int checkTexture(SDL_Texture* texture) { return texture ? 0 : (cout << "Error: " << SDL_GetError() << endl, -1); }

// Função para verificar se a fonte foi carregada corretamente
int checkFont(TTF_Font* font) { return font ? 0 : (cout << "Error: " << TTF_GetError() << endl, -1); }

// Função para verificar se a superfície foi carregada corretamente
int checkSurface(SDL_Surface* surface) { return surface ? 0 : (cout << "Error: " << SDL_GetError() << endl, -1); }

int checkWindow(SDL_Window* window) { return window ? 0 : (cout << "Error: " << SDL_GetError() << endl, -1); }