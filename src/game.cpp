#include <SDL.h>
#include <random>
#include <cmath>
#include <ctime>
#include "game.h"
#include "rendering.h"

Game::Game(Render& renderer) : renderer(renderer) {
    paddleHeight = 80;
    paddleWidth = 20;

    playerScore = 0;
    playerSpeed = 7;
    playerX = 30;
    playerY = renderer.SCREEN_HEIGHT / 2;

    computerScore = 0;
    computerSpeed = 7;
    computerX = renderer.SCREEN_WIDTH - 50;
    computerY = renderer.SCREEN_HEIGHT / 2;

    maxBallSpeed = 7;
    ballSize = 20;
    ballX = 500;
    ballY = 500;
    ballSpeedX = -3;
    ballSpeedY = 3;
}

void Game::HandleInput(SDL_Event& event) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_UP] && playerY-playerSpeed >= 0) {
        playerY -= playerSpeed;
    } else if (currentKeyStates[SDL_SCANCODE_DOWN] && playerY+paddleHeight < renderer.SCREEN_HEIGHT) {
        playerY += playerSpeed;
    }
}

void Game::Update() {

    ComputerMovement();

    // we check collision on every pixel otherwise the balls clips through objects
    for (int i = 0; i < maxBallSpeed; i++) {
        if (i <= std::abs(ballSpeedX)) {
            ballX += (ballSpeedX > 0) ? 1: -1;
        }
        if (i <= std::abs(ballSpeedY)) {
            ballY += (ballSpeedY > 0) ? 1: -1;
        }
        HandleCollision();
    }
}

void Game::HandleCollision() {
    std::uniform_int_distribution<int> distribution(1, 5);
    std::mt19937 rng(std::time(0));
    int probability = 1;
    int changeDirectionChance = distribution(rng);
    // there's a 20% chance for the ball to change direction when it hits the player/computer
    
    if (ballX < playerX+paddleWidth && ballY > playerY && ballY < playerY+paddleHeight) {
        BallHitsPlayer(probability, changeDirectionChance);
    } else if (ballX+ballSize == computerX && ballY+ballSize > computerY && ballY < computerY+paddleHeight) {
        BallHitsComputer(probability, changeDirectionChance);
    } else if (ballX+ballSize > renderer.SCREEN_WIDTH || ballX <= 0) {
        BallOutOfScreen();
    }  else if (ballY+20 > renderer.SCREEN_HEIGHT || ballY <= 0) {
        BallHitsWall();
    }
}

void Game::BallHitsComputer(int probability, int changeDirectionChance) {
        if (ballSpeedX < maxBallSpeed) {ballSpeedX += 1;}
        ballSpeedX = -ballSpeedX;
        if (changeDirectionChance == probability) {ballSpeedY = -ballSpeedY;}
}

void Game::BallHitsPlayer(int probability, int changeDirectionChance) {
        if (ballSpeedX > -maxBallSpeed) {ballSpeedX -= 1;}
        ballSpeedX = -ballSpeedX;
        if (changeDirectionChance == probability) {ballSpeedY = -ballSpeedY;}
}

void Game::BallOutOfScreen() {
    if (ballX + 20 > renderer.SCREEN_WIDTH) {
        // Reset the ball values when it hits the RIGHT side
        ballSpeedX = -2;
        ballSpeedY = -2;
        playerScore += 1;
    } else if (ballX <= 0) {
        // Reset the ball values when it hits on the LEFT side
        ballSpeedX = 2;
        ballSpeedY = 2;
        computerScore += 1;
    }
    ballX = 500;
    ballY = 500;
}

void Game::BallHitsWall() {
    ballSpeedY = - ballSpeedY;
    if (std::abs(ballSpeedY) < maxBallSpeed) {ballSpeedY += (ballSpeedY > 0) ? 1: -1;}
}

void Game::ComputerMovement() {
    // the computer moves different speeds based on where the ball is located and where it is going
    if (computerY < ballY && computerY+paddleHeight < renderer.SCREEN_HEIGHT && ballSpeedX < 0) {
        computerY += (computerSpeed - 4);
    } else if (computerY > ballY && computerY-computerSpeed >= 0  && ballSpeedX < 0) {
        computerY -= (computerSpeed - 4);
    } else if (computerY < ballY && computerY+paddleHeight < renderer.SCREEN_HEIGHT && ballX < renderer.SCREEN_WIDTH/2) {
        computerY += computerSpeed - 2;
    } else if (computerY > ballY && computerY+paddleHeight >= 0 && ballX < renderer.SCREEN_WIDTH/2) {
        computerY -= computerSpeed - 2;
    } else if (computerY < ballY && computerY+paddleHeight < renderer.SCREEN_HEIGHT) {
        computerY += computerSpeed;
    } else if (computerY > ballY && computerY-computerSpeed >= 0) {
        computerY -= computerSpeed;
    }
}

void Game::RenderGameObjects() {
    renderer.ClearScreen();

    // Draw squares in the middle of the screen
    for (int i = 0; i < 20; i++) {
        renderer.RenderRect((renderer.SCREEN_WIDTH/2)-10, i*40, 20, 20, 255, 255, 255);
    }

    // Score text
    renderer.RenderText(std::to_string(playerScore), 247, 70);
    renderer.RenderText(std::to_string(computerScore), 797, 70);

    renderer.RenderRect(ballX, ballY, ballSize, ballSize, 255, 255, 255);

    renderer.RenderRect(playerX, playerY, paddleWidth, paddleHeight, 255, 255, 255);
    renderer.RenderRect(computerX, computerY, paddleWidth, paddleHeight, 255, 255, 255);

    renderer.Present();
}