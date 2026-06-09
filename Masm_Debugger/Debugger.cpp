#include <iostream>
#include <iomanip>
#include "Memory.h"
#include "Instructions.h"
#include "Debugger.h"

using namespace std;

void Debugger::displayCommands()
{
    cout << left;
    cout << setw(13) << "dump" << "D  [range] \n";
    cout << setw(13) << "enter" << "E  address[list] \n";
    cout << setw(13) << "fill" << "F  range list \n";
    cout << setw(13) << "compare" << "C  range address \n";
    cout << setw(13) << "hex" << "H  value1 value2 \n";
    cout << setw(13) << "move" << "M  range address\n";
    cout << setw(13) << "register" << "R  [register]\n";
    cout << setw(13) << "search" << "M  range list\n";
    cout << setw(13) << "quit" << "Q\n";
}

void Debugger::displayErrors()
{
    cout << "\033[31m\n\t^\n\t  Error\n\033[0m";
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
            default:
                displayErrors();          
        }
    } while (userInput != 'q');
}