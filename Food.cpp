#include "Food.h"

Food::Food() 
{
    foodStorage = new objPosArrayList();
}

Food::~Food() 
{
    // Need to delete foodStorage now
    delete foodStorage;
}

void Food::generateFood(const objPosArrayList *blockOff, int specialFood) 
{
    // Initialization
    int randomX, randomY, x, y;
    bool validPosition = false;
    char foodSymbol;
    bool occupied[BOARD_LENGTH][BOARD_HEIGHT];

    // Seed random with the current time
    srand(time(NULL));

    // Generate a valid position for the food
    while (!validPosition) 
    {
        validPosition = true; // Start by assuming the position is valid

        for (x = 0; x < BOARD_LENGTH; x++) 
        {
            for (y = 0; y < BOARD_HEIGHT; y++) 
            {
                occupied[x][y] = 0; // Set all positions to 0 initially (empty)
            }
        }

        // Check if player is occupying where food wants to be generated
        for (x = 0; x < blockOff -> getSize(); x++) 
        {
            objPos occupiedPlayerX = blockOff -> getElement(x);
            
            occupied[occupiedPlayerX.pos -> x][occupiedPlayerX.pos -> y] = 1;
        }

        // Check if food is already occupying where food wants to be generated
        for (x = 0; x < foodStorage -> getSize(); x++) 
        {
            objPos occupiedFoodX = foodStorage -> getElement(x);

            occupied[occupiedFoodX.pos -> x][occupiedFoodX.pos -> y] = 1;
        }

        // Generate random x, y coordinates for new food
        randomX = (rand() % (BOARD_LENGTH - 2)) + 1;
        randomY = (rand() % (BOARD_HEIGHT - 2)) + 1;

        // Check if the generated position is occupied (either by player or food)
        if (occupied[randomX][randomY] == 1) 
        {
            validPosition = false; // If occupied, set validPosition to false and try again
        }

        else 
        {
            // Switch food type depending on random value generated,
            // 3/5 of the time it is normal apple
            // 1/5 of the time it is special apple
            // 1/5 of the time it is golden apple 
            switch (specialFood)
            {
                case 1:
                case 2:
                case 3:
                    foodSymbol = 'A';
                    break;
                
                case 4:
                    foodSymbol = 'S';
                    break;

                case 5:
                    foodSymbol = 'G';
                    break;
            }

            // Create the food position object and insert it into the food storage
            objPos foodPos = objPos(randomX, randomY, foodSymbol);
            foodStorage -> insertHead(foodPos);
        }
    }
}

objPosArrayList* Food::getFoodIndex() const 
{
    return foodStorage;
}
