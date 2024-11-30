#include "GameMechs.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    speed = 3;
    delay = 100000;
    score = 0;
    boardSizeX = 30;
    boardSizeY = 15;
    food = objPos(0, 0, '@');
    // food = new Food(); // Use dynamically allocated Food object
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    speed = 3;
    delay = 100000;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
    // food = new Food();
    food = objPos(0, 0, '@');
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    // Nothing on Heap
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getSpeed() const
{
    return speed;
}

int GameMechs::getDelay() const
{
    return delay;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::setSpeed(int newSpeed)
{
    speed = newSpeed;
}

void GameMechs::setDelay(int newDelay)
{
    delay = newDelay;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here