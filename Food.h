#ifndef FOOD_H
#define FOOD_H

#include "objPosArrayList.h"
#include "stdlib.h"
#include "time.h"

#define BOARD_HEIGHT 15
#define BOARD_LENGTH 30

class Food 
{
private:
    objPos foodPos; // Tracks the position of the food

public:
    Food(); // Constructor
    ~Food(); // Destructor (if needed)

    void generateFood(const objPosArrayList *blockOff);
    objPos getFoodPos() const;
};

#endif