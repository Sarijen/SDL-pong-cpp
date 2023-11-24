#ifndef GAME_H
#define GAME_H

#pragma once

#include <SDL.h>
#include "rendering.h"

class Game {
public:
    Game(Render& renderer);
    void HandleInput(SDL_Event& event);
    void RenderGameObjects();
    void Update();
    Render& renderer;
private:
    void HandleCollision();
    void BallHitsComputer(int, int);
    void BallHitsPlayer(int, int);
    void BallHitsWall();
    void BallOutOfScreen();
    void ComputerMovement();
    int changeDirectionChance;
    int paddleHeight;
    int paddleWidth;

    int playerSpeed;
    int playerX;
    int playerY;
    int playerScore;

    int computerSpeed;
    int computerX;
    int computerY;
    int computerScore;

    int maxBallSpeed;
    int ballSpeedX;
    int ballSpeedY;
    int ballSize;
    int ballX;
    int ballY;
};

#endif