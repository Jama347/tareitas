#include "hud.hpp"
#include <string>

void drawBar(SDL_Renderer* renderer, int x, int y, int w, int h, int percent, SDL_Color color) {
    SDL_Rect bg = { x, y, w, h };
    SDL_Rect fg = { x, y, w * percent / 100, h };
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &bg);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &fg);
}

void drawText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y) {
    SDL_Color white = {255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void drawHUD(SDL_Renderer* renderer, TTF_Font* font, int hp, int mana, int energy, int enemyHp) {
    drawText(renderer, font, "PLAYER", 50, 400);
    drawBar(renderer, 50, 430, 200, 20, hp, {255, 0, 0});
    drawText(renderer, font, "HP: " + std::to_string(hp), 260, 430);

    drawBar(renderer, 50, 460, 200, 20, energy, {255, 255, 0});
    drawText(renderer, font, "Energy: " + std::to_string(energy), 260, 460);

    drawBar(renderer, 50, 490, 200, 20, mana, {0, 0, 255});
    drawText(renderer, font, "Mana: " + std::to_string(mana), 260, 490);

    drawText(renderer, font, "ENEMY", 500, 100);
    drawBar(renderer, 500, 130, 200, 20, enemyHp, {255, 0, 0});
    drawText(renderer, font, "HP: " + std::to_string(enemyHp), 710, 130);
}