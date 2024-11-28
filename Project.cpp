#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Food.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define BOARD_LENGTH 30
#define BOARD_HEIGHT 15

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

Player *snake;
GameMechs *mechanisms;
Food *food;

int main(void)
{

    Initialize();

    while(!mechanisms -> getExitFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    mechanisms = new GameMechs(30, 15);
    food = new Food();
    snake = new Player(mechanisms, food);

    // Create first food item
    food -> generateFood(snake -> getPlayerPosList());
}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        mechanisms -> setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    snake -> updatePlayerDir();
    snake -> updatePlayerSpeed();
    snake -> updatePlayerDelay();
    snake -> movePlayer();
    mechanisms -> clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    int x;
    int y;
    int i;

    // draw the board
    for (y = 0; y < BOARD_HEIGHT; y++)
    {
        for (x = 0; x < BOARD_LENGTH; x++)
        {
            // Draw borders regardless
            if (x == 0 || x == (BOARD_LENGTH - 1) || y == 0 || y == (BOARD_HEIGHT - 1))
                {
                    MacUILib_printf("#");
                    continue;
                }
            
            bool snakePresent = false;

            // Check if the snake is in this coordinate
            for (i = 0; i < snake -> getPlayerPosList() -> getSize(); i++)
            {
                objPos snakeTorso = snake -> getPlayerPosList() -> getElement(i);
                if (snakeTorso.pos -> x == x && snakeTorso.pos -> y == y)
                {
                    MacUILib_printf("%c", snakeTorso.symbol);
                    snakePresent = true;
                    break;
                }
            }

            if (snakePresent)
            {
                continue; // Skip further checks for this cell
            }

            // If the snake isn't there, continue to draw the board
            if (!snakePresent)
            {
                // First, check if that position is filled with food
                if (x == food -> getFoodPos().pos -> x && y == food -> getFoodPos().pos -> y)
                {
                    MacUILib_printf("@");
                    continue;
                }

                // nothing otherwise
                else
                {
                    MacUILib_printf(" ");
                    continue;
                }
            }

        }
        MacUILib_printf("\n");
    }
    
    MacUILib_printf("Score: %d\n", mechanisms -> getScore());  

    MacUILib_printf("Current Speed Level: %d\n", mechanisms -> getSpeed());
    MacUILib_printf("Press '+' to increase speed, '-' to decrease speed.\n");

}

void LoopDelay(void)
{
    MacUILib_Delay(mechanisms -> getDelay()); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();

    // Check if the player lost
    if (mechanisms -> getLoseFlagStatus()) 
    {
        MacUILib_printf("You lost BUM!\nYou hit yourself bro you suck");
    }

    // Check if the player won based on the score
    else if (mechanisms -> getScore() >= 5) 
    {
        MacUILib_printf("Congratulations you win :|, you need a job man\nYour score this time was %d points\n", mechanisms -> getScore());
    }

    // Check if the game ended early without losing or winning
    else if (mechanisms -> getExitFlagStatus()) 
    {
        MacUILib_printf("Done already?\nYou scored %d points that run, you should have kept going.\n", mechanisms -> getScore());
    }

    delete snake;
    delete mechanisms;
    delete food;    

    MacUILib_uninit();
}
