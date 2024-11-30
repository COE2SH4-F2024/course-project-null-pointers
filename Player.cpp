#include "Player.h"
#include "objPosArrayList.h"

Player::Player(GameMechs* thisGMRef, Food *foodReference)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    food = foodReference;

    // more actions to be included
    playerPosList = new objPosArrayList();
    playerPosList -> insertHead(objPos(15, 7, '*'));
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
    int speed = mainGameMechsRef -> getSpeed(); 
    int delay = mainGameMechsRef -> getDelay();

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
    if (headNew.pos -> x == food -> getFoodPos().pos -> x && 
        headNew.pos -> y == food -> getFoodPos().pos -> y)
    {
        playerPosList -> insertHead(headNew);
        food -> generateFood(playerPosList);
        mainGameMechsRef -> incrementScore();
    }
}

// Check if the player collides with itself
void Player::selfCollisionCheck(const objPos &headNew) 
{
    for (int i = 1; i < playerPosList -> getSize(); i++) 
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
    if (headNew.pos -> x == food -> getFoodPos().pos -> x && 
        headNew.pos -> y == food -> getFoodPos().pos -> y) 
    {
        return; // Skip movement if a collision is detected
    }

    playerPosList -> insertHead(headNew);
    playerPosList -> removeTail();
}