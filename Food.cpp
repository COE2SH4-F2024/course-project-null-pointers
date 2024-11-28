#include "Food.h"

Food::Food() 
{
    foodPos = objPos(); // Initialize food
}

Food::~Food() 
{
    // No dynamic memory to clean up
}

void Food::generateFood(const objPosArrayList *blockOff) 
{
    int randomX, randomY, i;
    bool validPosition = false;

    // Seed random with the current time
    srand(time(NULL));

    // Generate a valid position for the food
    while (validPosition == false) 
    {
        validPosition = true;

        // Generate random x, y coordinates
        randomX = (rand() % (BOARD_LENGTH - 2)) + 1;
        randomY = (rand() % (BOARD_HEIGHT - 2)) + 1;

        // Check if the position overlaps with the blocked positions
        for (i = 0; i < blockOff -> getSize(); i++) 
        {
            if (randomX == blockOff -> getElement(i).pos -> x && 
                randomY == blockOff -> getElement(i).pos -> y)
            {
                validPosition = false;
            }
        }
    }

    // Set the food position to these newly generated random coordinates
    foodPos.pos -> x = randomX;
    foodPos.pos -> y = randomY;
}

objPos Food::getFoodPos() const 
{
    return foodPos;
}
