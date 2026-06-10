#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdio>
#include "Memory.h"
#include "Instructions.h"
#include "Debugger.h"
#include "Registers.h"

using namespace std;

Debugger E;
Registers R;
Memory mem;

void Instructions::Dump()
{
   
    cout << '\n';
    cin.ignore();
    cout << "Enter the address or press Enter for the default memory pointer : ";
    if (cin.get() == '\n')
        address = mem.getMemoryPointer();
    else
        cin >> hex >> address;
    if (!(mem.isValidMemoryAddress(address)))
    {
        E.displayErrors();
        return;
    }
    mem.printMemory(address);
}

void Instructions::Enter()
{
    cout << '\n';
    cout << "Enter the address : ";
    cin >> hex >> address;
    if (!(mem.isValidMemoryAddress(address)))
    {
        E.displayErrors();
        return;
    }
    cout << "Enter the value (in hexadecimal) : ";
    cin >> hex >> value;

    // User jo bhi address enter kre ga us address pr us ki input value store ho jye gi;

    int row = address % 16;
    int column = address / 16;
    mem.memoryView[column][row] = value;
    mem.memoryRepresentation[column][row] = value;
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
    if (!(mem.isValidMemoryRange(startingAddress, endingAddress)))
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
            mem.memoryView[i][j] = value;
            mem.memoryRepresentation[i][j] = value;
        }
    }
}

void Instructions::Move()
{
    cout << "Enter the range of addresses [ starting address ] and [ ending address ] : ";
    cin >> hex >> startingAddress >> endingAddress;
    if (!(mem.isValidMemoryRange(startingAddress, endingAddress)))
    {
        E.displayErrors();
        return;
    }
    cout << "Enter the starting address where to move : ";
    cin >> hex >> address;
    if (!(mem.isValidMemoryAddress(address)))
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
            mem.memoryView[columnIdx][rowIdx] = mem.memoryView[i][j];
            mem.memoryRepresentation[columnIdx][rowIdx] = mem.memoryView[i][j];
            rowIdx += 1;
        }
        columnIdx += 1;
    }
}

void Instructions::Search()
{
    cout << "Enter the range of addresses [ starting address ] and [ ending address ] : ";
    cin >> hex >> startingAddress >> endingAddress;
    if (!(mem.isValidMemoryRange(startingAddress, endingAddress)))
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
            if (mem.memoryView[i][j] == value)
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
    if (!(mem.isValidMemoryRange(startingAddress, endingAddress)))
    {
        E.displayErrors();
        return;
    }
    cout << "Enter the starting address from where to start compare : ";
    cin >> hex >> address;
    if (!(mem.isValidMemoryAddress(address)))
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
            if (mem.memoryView[i][j] != mem.memoryView[columnIdx][rowIdx])
            {
                cout << right << setfill('0') << "073F:" << setw(3) << i << j << "   " << setw(2) << mem.memoryView[i][j] << "   " << setw(2) << mem.memoryView[columnIdx][rowIdx] << "   " << setfill('0') << "073F:" << setw(3) << columnIdx << rowIdx << endl;
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


void Instructions::Assemble()
{
    cout << '\n';
    cout << "Enter the address : ";
    cin >> hex >> address;
    cin.ignore();
    if (!(mem.isValidMemoryAddress(address)))
    {
        E.displayErrors();
        return;
    }

    ofstream fout;
    fout.open("memory.txt");
    do
    {
        cout << "\n073F:" << right << setfill('0') << hex << setw(4) << address << " ";
        if (cin.get() == '\n')
            return;
        string opCode , operand , oper1 = "WE" , oper3 = "WE";
        int oper2 = 0;
        cin >> opCode >> operand;
        if (opCode == "add" || opCode == "sub")
            seperateOperandForAdd(operand, oper1, oper3);
        else
            seperateOperandForMovAndInc(operand, oper1, oper2);
        if (opCode == "add" || opCode == "dec" || opCode == "inc" || opCode == "sub" || opCode == "mov")
        {
            if (oper1 == "ax" || oper1 == "bx" || oper1 == "cx" || oper1 == "dx")
            {
                if ((opCode == "inc" || opCode == "dec") && operand[2] == '\n')
                        E.displayErrors();
                else
                {

                    // Save the Opcode , register and value in the memory.txt to restore them for later and user for actual operation of tracing and unassemlbe

                    if (opCode == "inc" || opCode == "dec")
                        fout << "073F:" << right << setfill('0') << hex << setw(4) << address << " " << opCode << " " << oper1 << '\n';
                    else if (opCode == "mov")
                        fout << "073F:" << right << setfill('0') << hex << setw(4) << address << " " << opCode << " " << oper1 << ' ' << oper2 << '\n';
                    else
                        fout << "073F:" << right << setfill('0') << hex << setw(4) << address << " " << opCode << " " << oper1 << ' ' << oper3 << '\n';

                    // Save the instructions in the memory;

                    int regAscii = R.getRegisterAscii(oper1);
                    if (opCode == "mov")
                    {
                        mem.saveMemoryInstruction(address, regAscii, oper2);
                        address += 3;
                    }
                    else if (opCode == "add" || opCode == "sub")
                        address += 2;
                    else
                        address++;
                }
            }
            else
                E.displayErrors();
        }
        else
            E.displayErrors();
    } while (cin.get() == '\n');
    fout.close();
}


void Instructions::seperateOperandForMovAndInc(string operand , string& regis, int& value)
{
    regis[0] = operand[0];
    regis[1] = operand[1];
    if(operand[2] == ',')
        value = ((operand[3] - 48) * 16) + (operand[4] - 48);
}

void Instructions::seperateOperandForAdd(string operand, string& regis, string& regis2)
{
    regis[0] = operand[0];
    regis[1] = operand[1];
    regis2[0] = operand[3];
    regis2[1] = operand[4];
}

void Instructions::Unassemble()
{
    ifstream fin;
    fin.open("memory.txt");
    string getContent;
    while (getline(fin, getContent))
    {
        cout << "\n" << getContent;
    } 
    fin.close();
}

void Instructions::Trace()
{
    ifstream fin;
    ofstream fout;
    fin.open("memory.txt");
    fout.open("temp_mem.txt");
    string addresses, opCode, regis, regis2;
    int value;
    fin >> addresses >> opCode >> regis;
    if (opCode == "mov")
        fin >> value;
    else if (opCode == "add" || opCode == "sub")
        fin >> regis2;

    R.displayRegiters();
    if (opCode == "inc" || opCode == "dec")
        cout << "\t\t\t" << opCode << "  " << regis;
    else if(opCode == "mov")
        cout << "\t\t\t" << opCode << "  " << regis << ' ' << value;
    else
        cout << "\t\t\t" << opCode << "  " << regis << ' ' << regis2;

    if (opCode == "mov")
    {
        if (regis == "ax")
            R.AX = value;
        else if(regis == "bx")
            R.BX = value;
        else if(regis == "cx")
            R.CX = value;
        else
            R.DX = value;
        R.checkForFlags();
        R.IP += 3;
    }
    else if (opCode == "inc")
    {
        if (R.AX == 0xffff || R.BX == 0xffff || R.CX == 0xFFFF || R.DX == 0xFFFF)
            R.carryFlag == true;
        if (regis == "ax")
            R.AX ++;
        else if (regis == "bx")
            R.BX ++;
        else if (regis == "cx")
            R.CX ++;
        else
            R.DX ++;
        R.checkForFlags();
        R.IP ++;
    }
    else if (opCode == "dec")
    {
        if (R.AX == 0 || R.BX == 0 || R.CX == 0 || R.DX == 0)
            R.carryFlag == true;
        if (regis == "ax")
            R.AX--;
        else if (regis == "bx")
            R.BX--;
        else if (regis == "cx")
            R.CX--;
        else
            R.DX--;

        R.checkForFlags();
        R.IP++;
    }
    else if (opCode == "add")
    {
        if (regis == "ax")
        {
            if (regis2 == "ax")
                R.AX += R.AX;
            else if (regis2 == "bx")
                R.AX += R.BX;
            else if (regis == "cx")
                R.AX += R.CX;
            else
                R.AX += R.DX;
        }
        else if (regis == "bx")
        {
            if (regis2 == "ax")
                R.BX += R.AX;
            else if (regis2 == "bx")
                R.BX += R.BX;
            else if (regis == "cx")
                R.BX += R.CX;
            else
                R.BX += R.DX;
        }
        else if(regis == "cx")
        {
            if (regis2 == "ax")
                R.CX += R.AX;
            else if (regis2 == "bx")
                R.CX += R.BX;
            else if (regis == "cx")
                R.CX += R.CX;
            else
                R.CX += R.DX;
        }
        else if (regis == "dx")
        {
            if (regis2 == "ax")
                R.DX += R.AX;
            else if (regis2 == "bx")
                R.DX += R.BX;
            else if (regis == "cx")
                R.DX += R.CX;
            else
                R.DX += R.DX;
        }
        R.checkForFlags();
        R.IP += 2;
    }
    else if (opCode == "sub")
    {
        if (regis == "ax")
        {
            if (regis2 == "ax")
                R.AX -= R.AX;
            else if (regis2 == "bx")
                R.AX -= R.BX;
            else if (regis == "cx")
                R.AX -= R.CX;
            else
                R.AX -= R.DX;
        }
        else if (regis == "bx")
        {
            if (regis2 == "ax")
                R.BX -= R.AX;
            else if (regis2 == "bx")
                R.BX -= R.BX;
            else if (regis == "cx")
                R.BX -= R.CX;
            else
                R.BX -= R.DX;
        }
        else if (regis == "cx")
        {
            if (regis2 == "ax")
                R.CX -= R.AX;
            else if (regis2 == "bx")
                R.CX -= R.BX;
            else if (regis == "cx")
                R.CX -= R.CX;
            else
                R.CX -= R.DX;
        }
        else if (regis == "dx")
        {
            if (regis2 == "ax")
                R.DX -= R.AX;
            else if (regis2 == "bx")
                R.DX -= R.BX;
            else if (regis == "cx")
                R.DX -= R.CX;
            else
                R.DX -= R.DX;
        }
        R.checkForFlags();
        R.IP += 2;
    }
    string line;
    while (getline(fin, line))
    {
        fout << line << endl;
    }
    fin.close();
    fout.close();
    remove("memory.txt");
    rename("temp_mem.txt", "memory.txt");
}

void Instructions::Help()
{
    ifstream fin;
    fin.open("helpMe.txt");
    string getContent;
    while (getline(fin, getContent))
    {
        cout << "\n" << getContent;
    }
    fin.close();
}