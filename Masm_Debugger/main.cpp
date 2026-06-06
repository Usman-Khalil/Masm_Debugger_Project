#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void mainInputOutputHandling();
void displayListOfCommands();
void displayMemory(int[][16], char[][16], int);
void executionOfEnterCommand(int [][16], char[][16], int, int);
void executionOfHexCommand(int, int);

int main()
{
    mainInputOutputHandling();
    return 0;
}

void mainInputOutputHandling()
{
    int memoryView[16][16] = { 0 };
    char memoryRepresentation[16][16];
    int rowIdx, columnIdx;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j <= 16; j++)
        {
            memoryRepresentation[i][j] = '.';
        }
    }
    char userInput;
    do
    {
        cout << "-";
        cin >> userInput;
        if (userInput == '?')
            displayListOfCommands();
        else if (userInput == 'd')
        {
            cout << "\nPlease enter the Address or Press \'Enter\' for the default Address pointer : ";
            char temp;
            cin.ignore();
            cin.get(temp);
            if (temp == '\n')
            {
                cout << endl;
                displayMemory(memoryView, memoryRepresentation, 0x0);
            }
            else
            {
                int startingAddress;
                cin >> hex >> startingAddress;
                cout << endl ;
                displayMemory(memoryView, memoryRepresentation, startingAddress);
            }
        }
        else if (userInput == 'e')
        {
            cout << '\n';
            int address, value;
            cout << "Enter the address : ";
            cin >> hex >> address;
            cout << "Enter the value : ";
            cin >> hex >> value;
            executionOfEnterCommand(memoryView, memoryRepresentation, address, value);
        }
        else if (userInput == 'h')
        {
            int value1, value2;
            cin >> hex >> value1 >> value2;
            executionOfHexCommand(value1, value2);
        }
        
    } while (userInput != 'q');
}

void displayListOfCommands()
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

void displayMemory(int memoryView[][16], char memoryRepresentation[][16], int startingAddress = 0x0)
{
    cout << '\n';
    int rowIdx, columnIdx;
    columnIdx = startingAddress / 16;
    int endingOfColumn = (8 + startingAddress / 16);
    int endingOfRow = 16;
    for (int i = columnIdx; i <= endingOfColumn; i++)
    {
        rowIdx = 0;
        if (i == endingOfColumn)
        {
            endingOfRow = startingAddress % 16;
        }
        cout << hex << right;
        cout << setfill('0') << "073F:" << setw(3) << columnIdx << rowIdx << "  ";
        if (i == startingAddress / 16)
        {
            rowIdx = (startingAddress % 16);
            for (int j = 0; j < startingAddress % 16; j++)
            {
                cout << setw(3) << setfill(' ') << ' ';
            }
        }
        for (int j = rowIdx; j < endingOfRow; j++)
        {
            cout << setw(2) << setfill('0') << memoryView[i][j] << " ";
        }
        columnIdx++;
        if (i == endingOfColumn)
        {
            for (int j = 0; j <= 16 - endingOfRow; j++)
            {
                cout << setw(3) << setfill(' ') << ' ';
            }
        }
        cout << "\t\t\t";
        if (i == startingAddress / 16)
        {
            for (int j = 0; j < startingAddress % 16; j++)
            {
                cout << setw(2) << setfill(' ') << ' ';
            }
        }
        for (int j = rowIdx; j < endingOfRow; j++)
        {
            cout << memoryRepresentation[i][j] << " ";
            rowIdx++;
        }
        cout << '\n';
    }
    cout << '\n';
}

void executionOfEnterCommand(int memoryView[][16] , char memoryRepresentation[][16] , int address, int value)
{
    {
        int row = address % 16;
        int column = address / 16;
        memoryView[column][row] = value;
        memoryRepresentation[column][row] = value;
    }
}

void executionOfHexCommand(int value1, int value2)
{
    cout << setfill('0');
    cout << hex << setw(4) << (short int)(value1 + value2) << "   " << setw(4) << (short int)(value1 - value2) << endl;
}