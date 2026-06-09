#include <iostream>
#include <iomanip>
#include "Memory.h"
#include "Instructions.h"
#include "Debugger.h"

using namespace std;

void Debugger::displayCommands()
{
    cout << left << '\n';
    cout << setw(16) << "1. dump" << "D  [range] \n";
    cout << setw(16) << "2. enter" << "E  address[list] \n";
    cout << setw(16) << "3. fill" << "F  range list \n";
    cout << setw(16) << "4. compare" << "C  range address \n";
    cout << setw(16) << "5. hex" << "H  value1 value2 \n";
    cout << setw(16) << "6. move" << "M  range address\n";
    cout << setw(16) << "7. register" << "R  [register]\n";
    cout << setw(16) << "8. search" << "S  range list\n";
    cout << setw(16) << "9. assemble" << "A  [address] \n";
    cout << setw(16) << "10.unassemble" << "U  [address] \n";
    cout << setw(16) << "11.trace" << "T  [=address] [value] \n";
    cout << setw(16) << "12.quit" << "Q\n";
}

void Debugger::displayErrors()
{
    cout << "\033[31m\n\t^  Error\n\033[0m";
    cin.ignore(100, '\n');
}

void Debugger::startDebugging()
{
    Instructions ins;
    char userInput;
    do
    {
        cout << "\n-";
        cin >> userInput;
        switch (userInput)
        {
            case 'd':
                ins.Dump();
                break;
            case 'e':
                ins.Enter();
                break;
            case 'h':
                ins.Hex();
                break;
            case 'f':
                ins.Fill();
                break;
            case 'm':
                ins.Move();
                break;
            case 's':
                ins.Search();
                break;
            case 'c':
                ins.Compare();
                break;
            case 'q':
                break;
            case 'r':
                ins.loadRegisters();
                break;
            case 'a':
                ins.Assemble();
                break;
            case 'u':
                ins.Unassemble();
                break;
            case 't':
                ins.Trace();
                break;
            default:
                displayErrors();          
        }
    } while (userInput != 'q');
}