#include <iostream>
#include "Memory.h"
#include <iomanip>
using namespace std;

void Memory::printMemory(short int address)
{
    cout << '\n';
    int rowIdx,
        columnIdx,
        endingOfColumn,
        endingOfRow;

    columnIdx = address / 16;
    endingOfColumn = (8 + address / 16);
    endingOfRow = 16;

    for (int i = columnIdx; i <= endingOfColumn; i++)
    {
        rowIdx = 0;

        if (i == endingOfColumn)
            endingOfRow = address % 16;

        cout << hex << right << setfill('0') << "073F:" << setw(3) << columnIdx << rowIdx << "  ";
        if (i == address / 16)
        {
            rowIdx = (address % 16);
            for (int j = 0; j < address % 16; j++)
            {
                cout << setw(3) << setfill(' ') << ' ';
            }
        }
        for (int j = rowIdx; j < endingOfRow; j++)
        {
            cout << setw(2) << setfill('0') << memoryView[i][j];
            if (j == 7)
                cout << '-';
            else
                cout << ' ';
        }
        columnIdx += 1;
        if (i == endingOfColumn)
        {
            for (int j = 0; j <= 16 - endingOfRow; j++)
            {
                cout << setw(3) << setfill(' ') << ' ';
            }
        }
        cout << "\t\t\t";
        if (i == address / 16)
        {
            for (int j = 0; j < address % 16; j++)
            {
                cout << setw(2) << setfill(' ') << ' ';
            }
        }
        for (int j = rowIdx; j < endingOfRow; j++)
        {
            if (memoryRepresentation[i][j] == 0)
                cout << '.' << " ";
            else
                cout << memoryRepresentation[i][j] << " ";
            rowIdx += 1;
        }
        cout << '\n';
    }
    cout << '\n';

}

short int Memory::getMemoryPointer()
{
    return memoryPointer;
}

bool Memory::isValidMemoryAddress(short int address)
{
    if (address <= 0 || address >= 0xf00)
        return false;
    else
        return true;
}

bool Memory::isValidMemoryRange(short int startingAddress, short int endingAddress)
{
    if ((startingAddress >= 0 && startingAddress < 0x0f00) && (endingAddress >= 0 && endingAddress < 0x0f00) && (startingAddress < endingAddress))
        return true;
    else
        return false;
}

void Memory::saveMemoryInstruction(int address , int opValue , int value)
{
    int row = address % 16;
    int column = address / 16;
    memoryView[column][row] = opValue;
    if(row < 15)
    {
        memoryView[column][row + 1] = value;
        memoryRepresentation[column][row + 1] = value;
    }
    else
    {
        memoryView[column + 1][0] = value;
        memoryRepresentation[column + 1][0] = value;
    }
}

Memory::~Memory()
{
    delete[]memoryView;
    delete[]memoryRepresentation;
}