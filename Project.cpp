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

    mechanisms = new GameMechs(BOARD_LENGTH, BOARD_HEIGHT);
    food = new Food();
    snake = new Player(mechanisms, food);

    for(int i = 1; i <= 5; i++)
    {
        food -> generateFood(snake -> getPlayerPosList(), i); // I can really just call it with the argument 1 three times,
                                                              // but I think this is more clear as to whats going on
    }
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

    // Draw the board
    for (y = 0; y < BOARD_HEIGHT; y++)
    {
        for (x = 0; x < BOARD_LENGTH; x++)
        {
            // Draw borders
            if (x == 0 || x == (BOARD_LENGTH - 1) || y == 0 || y == (BOARD_HEIGHT - 1))
            {
                MacUILib_printf("#");
                continue; // Skip further checks for border cells
            }

            bool snakePresent = false;
            bool foodPresent = false;

            // Check if the snake is in this coordinate
            for (i = 0; i < snake -> getPlayerPosList() -> getSize(); i++)
            {
                objPos snakeTorso = snake -> getPlayerPosList() -> getElement(i); // Get each snake bodypart position

                if (snakeTorso.pos -> x == x && snakeTorso.pos -> y == y)
                {
                    MacUILib_printf("%c", snakeTorso.symbol);
                    snakePresent = true;
                    break;
                }
            }

            // If snake is not present, check if food is in this coordinate
            if (!snakePresent)
            {
                for (i = 0; i < food -> getFoodIndex() -> getSize(); i++)
                {
                    objPos currentFood = food -> getFoodIndex() -> getElement(i); // Get each food position

                    if (currentFood.pos -> x == x && currentFood.pos -> y == y)
                    {
                        MacUILib_printf("%c", currentFood.getSymbol()); 
                        foodPresent = true;
                        break; // No need to check further for food
                    }
                }
            }

            // If neither snake nor food is present, print empty space
            if (!snakePresent && !foodPresent)
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }

    // Display score and speed information
    MacUILib_printf("Score: %d\n", mechanisms -> getScore());
    MacUILib_printf("Current Speed Level: %d\n", mechanisms -> getSpeed());
    MacUILib_printf("Press '+' to increase speed, '-' to decrease speed.\n");
}

void LoopDelay(void)
{
    MacUILib_Delay(mechanisms -> getDelay()); // 0.1s delay by default
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
    else if (mechanisms -> getScore() >= 100) 
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
