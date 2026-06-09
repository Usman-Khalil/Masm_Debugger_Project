#include <iostream>
#include <iomanip>
#include "Memory.h"
#include "Instructions.h"
#include "Debugger.h"
#include "Registers.h"

using namespace std;

Debugger E;
Registers R;

void Instructions::Dump()
{
   
    cout << '\n';
    cin.ignore();
    cout << "Enter the address or press Enter for the default memory pointer : ";
    if (cin.get() == '\n')
        address = getMemoryPointer();
    else
        cin >> hex >> address;
    if (!(isValidMemoryAddress(address)))
    {
        E.displayErrors();
        return;
    }
    printMemory(address);
}

void Instructions::Enter()
{
    cout << '\n';
    cout << "Enter the address : ";
    cin >> hex >> address;
    if (!(isValidMemoryAddress(address)))
    {
        E.displayErrors();
        return;
    }
    cout << "Enter the value (in hexadecimal) : ";
    cin >> hex >> value;

    // User jo bhi address enter kre ga us address pr us ki input value store ho jye gi;

    int row = address % 16;
    int column = address / 16;
    memoryView[column][row] = value;
    memoryRepresentation[column][row] = value;
}

void Instructions::Hex()
{
    int value1, value2;
    cout << "Enter two values seperated by space in hexadeciaml : ";
    cin >> hex >> value1 >> value2;

    cout << setfill('0');
    cout << hex << setw(4) << (short int)(value1 + value2) << "   " << setw(4) << (short int)(value1 - value2) << endl;
}

void Instructions::Fill()
{
    cout << "Enter the range of addresses [ starting address ] and [ ending address ] : ";
    cin >> hex >> startingAddress >> endingAddress;
    if (!(isValidMemoryRange(startingAddress, endingAddress)))
    {
        E.displayErrors();
        return;
    }
    cout << "Enter the value to  be filled : ";
    cin >> hex >> value;

    unsigned short int startingColumnIdx,
        endingRowIdx,
        endingColumnIdx,
        startingRowIdx;

    startingColumnIdx = startingAddress / 16;
    endingRowIdx = 15;
    endingColumnIdx = endingAddress / 16;

    for (int i = startingColumnIdx; i <= endingColumnIdx; i++)
    {
        startingRowIdx = 0;
        if (i == startingAddress / 16)
            startingRowIdx = startingAddress % 16;
        if (i == endingColumnIdx)
            endingRowIdx = endingAddress % 16;
        for (int j = startingRowIdx; j <= endingRowIdx; j++)
        {
            memoryView[i][j] = value;
            memoryRepresentation[i][j] = value;
        }
    }
}

void Instructions::Move()
{
    cout << "Enter the range of addresses [ starting address ] and [ ending address ] : ";
    cin >> hex >> startingAddress >> endingAddress;
    if (!(isValidMemoryRange(startingAddress, endingAddress)))
    {
        E.displayErrors();
        return;
    }
    cout << "Enter the starting address where to move : ";
    cin >> hex >> address;
    if (!(isValidMemoryAddress(address)))
    {
        E.displayErrors();
        return;
    }
    int startingColumnIdx,
        endingRowIdx,
        endingColumnIdx,
        startingRowIdx,
        rowIdx,
        columnIdx;

    columnIdx = address / 16;
    startingColumnIdx = startingAddress / 16;
    endingRowIdx = 15;
    endingColumnIdx = endingAddress / 16;
    for (int i = startingColumnIdx; i <= endingColumnIdx; i++)
    {
        rowIdx = 0;
        startingRowIdx = 0;
        if (i == (startingAddress / 16))
        {
            rowIdx = (address % 16);
            startingRowIdx = (startingAddress % 16);
        }
        if (i == endingColumnIdx)
            endingRowIdx = (endingAddress % 16);
        for (int j = startingRowIdx; j <= endingRowIdx; j++)
        {
            memoryView[columnIdx][rowIdx] = memoryView[i][j];
            memoryRepresentation[columnIdx][rowIdx] = memoryView[i][j];
            rowIdx += 1;
        }
        columnIdx += 1;
    }
}

void Instructions::Search()
{
    cout << "Enter the range of addresses [ starting address ] and [ ending address ] : ";
    cin >> hex >> startingAddress >> endingAddress;
    if (!(isValidMemoryRange(startingAddress, endingAddress)))
    {
        E.displayErrors();
        return;
    }
    cout << "Enter the value to  be searched : ";
    cin >> hex >> value;

    int startingColumnIdx,
        endingRowIdx,
        endingColumnIdx,
        startingRowIdx;

    startingColumnIdx = startingAddress / 16;
    endingRowIdx = 15;
    endingColumnIdx = endingAddress / 16;

    for (int i = startingColumnIdx; i <= endingColumnIdx; i++)
    {
        startingRowIdx = 0;
        if (i == startingAddress / 16)
            startingRowIdx = startingAddress % 16;
        if (i == endingColumnIdx)
            endingRowIdx = endingAddress % 16;
        for (int j = startingRowIdx; j <= endingRowIdx; j++)
        {
            if (memoryView[i][j] == value)
            {
                cout << right << setfill('0') << "073F:" << setw(3) << i << j << endl;
            }
        }
    }
}

void Instructions::Compare()
{
    cout << "Enter the range of addresses [ starting address ] and [ ending address ] : ";
    cin >> hex >> startingAddress >> endingAddress;
    if (!(isValidMemoryRange(startingAddress, endingAddress)))
    {
        E.displayErrors();
        return;
    }
    cout << "Enter the starting address from where to start compare : ";
    cin >> hex >> address;
    if (!(isValidMemoryAddress(address)))
    {
        E.displayErrors();
        return;
    }
    int startingColumnIdx,
        endingRowIdx,
        endingColumnIdx,
        startingRowIdx,
        rowIdx,
        columnIdx;

    columnIdx = address / 16;
    startingColumnIdx = startingAddress / 16;
    endingRowIdx = 15;
    endingColumnIdx = endingAddress / 16;
    for (int i = startingColumnIdx; i <= endingColumnIdx; i++)
    {
        rowIdx = 0;
        startingRowIdx = 0;
        if (i == (startingAddress / 16))
        {
            rowIdx = (address % 16);
            startingRowIdx = (startingAddress % 16);
        }
        if (i == endingColumnIdx)
            endingRowIdx = (endingAddress % 16);
        for (int j = startingRowIdx; j <= endingRowIdx; j++)
        {
            if (memoryView[i][j] != memoryView[columnIdx][rowIdx])
            {
                cout << right << setfill('0') << "073F:" << setw(3) << i << j << "   " << setw(2) << memoryView[i][j] << "   " << setw(2) << memoryView[columnIdx][rowIdx] << "   " << setfill('0') << "073F:" << setw(3) << columnIdx << rowIdx << endl;
            }
            rowIdx += 1;
        }
        columnIdx += 1;
    }
}

void Instructions::loadRegisters()
{
    R.displayRegiters();
}