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
}

int objPosArrayList::getSize() const
{
    return listSize;
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

void objPosArrayList::removeHead()
{
    if (listSize >= 1)
    {

        int i;

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
    if (index >= 0 && index < listSize) {
        return aList[index];
    }
    return objPos();
}