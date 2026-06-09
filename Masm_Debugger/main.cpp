#include <iostream>
#include <iomanip>
#include "Memory.h"
#include "Instructions.h"
#include "Debugger.h"
#include <string>

using namespace std;

int main()
{
    Debugger d;

    d.displayCommands();
    d.startDebugging();

    return 0;
}