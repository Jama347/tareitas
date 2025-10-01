#ifndef HUD_HPP
#define HUD_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void drawHUD(SDL_Renderer* renderer, TTF_Font* font, int hp, int mana, int energy, int enemyHp);

#endif