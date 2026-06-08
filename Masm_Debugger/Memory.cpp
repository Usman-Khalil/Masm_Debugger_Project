#include <iostream>
#include "Memory.h"

using namespace std;

Memory::Memory()
{
    fillFakeMemory();
}

void Memory::fillFakeMemory()
{
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            memoryRepresentation[i][j] = '.';
        }
    }
}

Memory::~Memory()
{
    delete[]memoryView;
    delete[]memoryRepresentation;
}