#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* foodReference);
        ~Player();
        
        objPosArrayList* getPlayerPosList() const;

        void updatePlayerDir();
        void updatePlayerSpeed();
        void updatePlayerDelay();
        void movePlayer();
        void foodConsumption(const objPos &headNew);
        void selfCollisionCheck(const objPos &headNew);
        void snakeMovement(const objPos &headNew);

        // More methods to be added here

    private:
        objPosArrayList* playerPosList;  // Upgraded       
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* food; 
};

#endif