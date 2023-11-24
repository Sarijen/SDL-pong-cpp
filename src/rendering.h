#ifndef RENDERING_H
#define RENDERING_H

#pragma once

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
using std::string;

class Render {
public:
    const int SCREEN_WIDTH = 1100;
    const int SCREEN_HEIGHT = 800;
    Render();
    ~Render();

    void Cleanup();
    void ClearScreen();
    void Present();
    void RenderRect(int x, int y, int width, int height, int red, int green, int blue);
    void RenderText(const string& text, int x, int y);

private:
    TTF_Font* font;
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif