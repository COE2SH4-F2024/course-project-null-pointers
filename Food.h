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
    objPosArrayList *foodStorage;
    char foodSymbol;

public:
    Food(); // Constructor
    ~Food(); // Destructor (if needed)

    void generateFood(const objPosArrayList *blockOff, int specialFood);
    objPosArrayList* getFoodPos() const;
};

#endif