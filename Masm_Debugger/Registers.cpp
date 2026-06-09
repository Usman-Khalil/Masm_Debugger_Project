#include <iostream>
#include <iomanip>
#include "Registers.h"

using namespace std;

void Registers::displayRegiters()
{
	cout << endl << hex << setfill('0') << "AX=" << setw(4) << AX << "  "
		<< "BX=" << setw(4) << BX << "  "
		<< "CX=" << setw(4) << CX << "  "
		<< "DX=" << setw(4) << DX << "  "
		<< "SP=" << setw(4) << SP << "  "
		<< "BP=" << setw(4) << BP << "  "
		<< "SI=" << setw(4) << SI << "  "
		<< "DI=" << setw(4) << DI << "  \n"
		<< "DS=" << setw(4) << DS << "  "
		<< "ES=" << setw(4) << ES << "  "
		<< "SS=" << setw(4) << SS << "  "
		<< "CS=" << setw(4) << CS << "  "
		<< "IP=" << setw(4) << IP << "  ";
		        //<< overFlag << "  "
		        //<< zeroFlag << "  "
		        //<< carryFlag << endl;
}

short int Registers::getInsPointer()
{
	return IP;
}