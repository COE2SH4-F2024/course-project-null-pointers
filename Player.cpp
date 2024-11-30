#include "Player.h"
#include "objPosArrayList.h"

Player::Player(GameMechs* thisGMRef, Food *foodRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    food = foodRef;

    // more actions to be included

    int boardParametersX = mainGameMechsRef -> getBoardSizeX();
    int boardParametersY = mainGameMechsRef -> getBoardSizeY();

    playerPosList = new objPosArrayList();
    playerPosList -> insertHead(objPos(boardParametersX / 2, // Print snake in the middle of the board
                                       boardParametersY / 2, 
                                       '*'));
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList *Player::getPlayerPosList() const
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic

    char input = mainGameMechsRef -> getInput();
    if(input != 0)
    {   
        switch(input)
        {                      
            case 27: 
                mainGameMechsRef -> setExitTrue();
                break;

            case 'a':
            case 'A':
                if(myDir == UP || myDir == DOWN || myDir == STOP)
                {
                    myDir = LEFT;
                }
                break;

            case 'd':
            case 'D':
                if(myDir == UP || myDir == DOWN || myDir == STOP)
                {
                    myDir = RIGHT;
                }
                break;

            case 'w':
            case 'W':
                if(myDir == RIGHT || myDir == LEFT || myDir == STOP)
                {
                    myDir = UP;
                }
                break;
                
            case 's':
            case 'S':
                if(myDir == RIGHT || myDir == LEFT || myDir == STOP)
                {
                    myDir = DOWN;
                }
                break;

            default:
                break;
        }
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    objPos headNew = playerPosList -> getHeadElement();

    switch (myDir)
    {
        case STOP:
            return;

        case LEFT:
            headNew.pos -> x = headNew.pos -> x - 1;
            // Wrap right
            if (headNew.pos -> x == 0) 
            {
                headNew.pos -> x = mainGameMechsRef -> getBoardSizeX() - 2;
            }
            break;

        case RIGHT:
            headNew.pos -> x = headNew.pos -> x + 1;
            // Wrap  left
            if (headNew.pos -> x == mainGameMechsRef -> getBoardSizeX() - 1) 
            {
                headNew.pos -> x = 1;
            }
            break;
            
        case UP:
            headNew.pos -> y = headNew.pos -> y - 1;
            // Wrap bottom
            if (headNew.pos -> y == 0) 
            {
                headNew.pos -> y = mainGameMechsRef -> getBoardSizeY() - 2;
            }
            break;

        case DOWN:
            headNew.pos -> y = headNew.pos -> y + 1;
            // Wrap top
            if (headNew.pos -> y == mainGameMechsRef -> getBoardSizeY() - 1) 
            {
                headNew.pos -> y = 1;
            }
            break;

        default:
            // Handle unexpected direction states (if any)
            break;
    }

    // Handle collisions and movement
    foodConsumption(headNew);
    selfCollisionCheck(headNew);
    snakeMovement(headNew);

}

void Player::updatePlayerSpeed()
{
    // Need to get speed and input
    char input = mainGameMechsRef -> getInput();
    int speed = mainGameMechsRef -> getSpeed(); 

    // Adjust Speed
    if(input != 0)
    {   
        switch(input)
        {             
            case '+':
                if(speed < 5)
                {
                    speed++;
                }
                break;
            
            case '-':
                if(speed > 1)
                {
                    speed--;
                }
                break;

            default:
                break;
        }
    }

    mainGameMechsRef -> setSpeed(speed);
}

void Player::updatePlayerDelay()
{
    // Need to get speed and delay
    int speed = mainGameMechsRef -> getSpeed(); 
    int delay = mainGameMechsRef -> getDelay();

    // Change delay
    switch (speed)
    {
        case 1:
            delay = 400000;
            break;
        case 2:
            delay = 200000;
            break;
        case 3:
            delay = 100000;
            break;
        case 4:
            delay = 50000;
            break;
        case 5:
            delay = 10000;
            break;
        default:
            delay = 100000; 
            break;
    }

    mainGameMechsRef -> setDelay(delay);
}


// More methods to be added

void Player::foodConsumption(const objPos &headNew) 
{
    int i;
    int j;
    int k;

    for(i = 0; i < food -> getFoodPos() -> getSize(); i++)
    {
        if (headNew.pos -> x == food -> getFoodPos() -> getElement(i).pos -> x && 
            headNew.pos -> y == food -> getFoodPos() -> getElement(i).pos -> y)
        {
            // Start generation of new food
            int foodGenerator = rand() % (5) + 1;
            char specialFood = food -> getFoodPos() -> getElement(i).getSymbol();

            if(specialFood == 'G') // Golden Apple, increase score by 50, length by 10
            {
                mainGameMechsRef -> incrementScore(50);
                playerPosList -> insertTails(10);
                
            }

            else if(specialFood == 'S') // Special Apple, increase score by 10, and don't increase length
            {
                mainGameMechsRef -> incrementScore(10);
            }

            else  // normal food
            {
                mainGameMechsRef -> incrementScore(1);
                playerPosList -> insertTails(1);
            }

            food -> getFoodPos() -> removeElement(i);

            // Generate Special Apple
            if(foodGenerator == 4) 
            {
                food -> generateFood(playerPosList, 4);
            }

            // Generate Golden Apple
            else if (foodGenerator == 5) 
            {
                food -> generateFood(playerPosList, 5);
            }

            // Generate Normal Apple
            else
            {
                food -> generateFood(playerPosList, 1);   
            }
        }
    }
}

// Check if the player collides with itself
void Player::selfCollisionCheck(const objPos &headNew) 
{

    int i;

    for (i = 1; i < playerPosList -> getSize(); i++) 
    { // Skip the head at index 0

        objPos bodyPart = playerPosList -> getElement(i);

        if (headNew.pos -> x == bodyPart.pos -> x &&
            headNew.pos -> y == bodyPart.pos -> y) 
        {
            mainGameMechsRef -> setLoseFlag();
            mainGameMechsRef -> setExitTrue();
        }
    }
}

// Handle regular movement (if no collision occurs)
void Player::snakeMovement(const objPos &headNew) 
{

    int i;

    for(i = 0; i < food -> getFoodPos() -> getSize(); i++)
    {
        if (headNew.pos -> x == food -> getFoodPos() -> getElement(i).pos -> x && 
            headNew.pos -> y == food -> getFoodPos() -> getElement(i).pos -> y)
        {
            return;
        }
    }

    playerPosList -> insertHead(headNew);
    playerPosList -> removeTail();
}