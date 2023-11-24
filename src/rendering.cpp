#include "rendering.h"
#include <SDL.h>
#include <SDL_ttf.h>

using std::string;

Render::Render() : font(nullptr), window(nullptr), renderer(nullptr) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    font = TTF_OpenFont("fonts/retrofont.ttf", 64);
    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

Render::~Render() {
    Cleanup();
}

void Render::Present() {
    SDL_RenderPresent(renderer);
}

void Render::RenderRect(int x, int y, int width, int height, int red, int green, int blue) {
    SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
    SDL_Rect Rect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &Rect);
}

void Render::RenderText(const string& text, int x, int y) {
    SDL_Color textColor = { 255, 255, 255 };

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void Render::ClearScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Render::Cleanup() {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    TTF_CloseFont(font);
    font = nullptr;

    TTF_Quit();
    SDL_Quit();
}
