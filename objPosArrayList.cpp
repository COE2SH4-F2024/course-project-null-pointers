#include "objPosArrayList.h"

objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[arrayCapacity];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
    aList = nullptr;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

objPosArrayList::objPosArrayList(objPosArrayList& copy)
{

    int i;

    // Allocate new memory for the array
    listSize = copy.listSize;

    arrayCapacity = copy.arrayCapacity;

    aList = new objPos[arrayCapacity];

    // Copy the elements from the other object
    for (i = 0; i < listSize; ++i) 
    {
        aList[i] = copy.aList[i];
    }
}

// Copy Assignment Operator
objPosArrayList& objPosArrayList::operator=(const objPosArrayList& copy)
{
    int i;

    // Self-assignment check
    if (this == &copy) 
    {
        return *this;
    }

    // Clean up any existing resources
    delete[] aList;

    // Allocate new memory for the array
    listSize = copy.listSize;

    arrayCapacity = copy.arrayCapacity;

    aList = new objPos[arrayCapacity];

    // Copy the elements from the other object
    for (i = 0; i < listSize; ++i) 
    {
        aList[i] = copy.aList[i];
    }

    return *this;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    int i;

    if (listSize < arrayCapacity)
    {
        listSize++;
        for (i = listSize - 1; i > 0; i--)
        {
            aList[i] = aList[i - 1];
        }
        
        aList[0] = thisPos;
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize < arrayCapacity)
    {
        aList[listSize] = thisPos;
        listSize++;
    }
}

void objPosArrayList::insertTails(int num) 
{
    if (listSize < arrayCapacity)
    {
        listSize = listSize + num;
    }
}

void objPosArrayList::removeHead()
{
    int i;

    if (listSize >= 1)
    {

        for (i = 0; i < listSize - 1; i++)
        {
            aList[i] = aList[i + 1];
        }

        listSize--;
    }
}

void objPosArrayList::removeTail()
{
    // Check this would not result in a negative list size
    if (listSize >= 1)
    {
        aList[listSize - 1] = objPos();
        listSize--;
    }
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{   
    return aList[index];
}

// Like removeHead but used if we need to specify an index
void objPosArrayList::removeElement(int index)
{
    int i;

    if (listSize >= 1 && index >= 0 && index < listSize)
    {
        for (i = index; i < listSize - 1; i++)
        {
            aList[i] = aList[i + 1];
        }
        listSize--;
    }
}
