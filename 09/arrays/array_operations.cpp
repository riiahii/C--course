#include "array_operations.hh"

int greatest_v1(int *itemptr, int size)
{
    int greatest = *itemptr;
    int *startPosition = itemptr;

    while(itemptr < startPosition + size)
    {
        // unary toisin sanoen one-line if-else
        greatest = (*itemptr > greatest) ? *itemptr : greatest;

        //shift pointer
        itemptr++;
    }
    return greatest;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int greatest = *itemptr;
    while(itemptr < endptr)
    {
        greatest = (*itemptr > greatest) ? *itemptr : greatest;
        itemptr++;
    }
    return greatest;

}

void copy(int *itemptr, int *endptr, int *targetptr)
{

    while(itemptr < endptr)
    {
        *targetptr = *itemptr;
        itemptr++;
        targetptr++;
    }
}

void reverse(int *leftptr, int *rightptr)
{
    int temp;
    rightptr--;
    while(leftptr < rightptr)
    {
        // tallenna toinen
        temp = *leftptr;
        //vaihda arvot
        *leftptr = *rightptr;
        *rightptr = temp;

        //shift
        leftptr++;
        rightptr--;
    }
}
