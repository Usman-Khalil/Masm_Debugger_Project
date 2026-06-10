#include <iostream>
#include <iomanip>
#include "Registers.h"
#include <string>

using namespace std;

void Registers::displayRegiters()
{
	cout << right << endl << hex << setfill('0') << "AX=" << setw(4) << AX << "  "
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
	if (overFlow == true)
		cout << "OV  ";
	else
		cout << "NV  ";
	if (carryFlag == true)
		cout << "CF  ";
	else
		cout << "NC  ";
	if (zeroFlag == true)
		cout << "ZF  ";
	else
		cout << "NZ  \n";
}

short int Registers::getInsPointer()
{
	return IP;
}

int Registers::getRegisterAscii(string regis)
{
	if (regis == "ax")
		return 184;
	else if (regis == "bx")
		return 187;
	else if (regis == "cx")
		return 185;
	else
		return 186;
}

void Registers::checkForFlags()
{
	if (AX == 0 || BX == 0 || CX == 0 || DX == 0)
		zeroFlag = true;
	if (AX > 0xfff || BX > 0xfff || CX > 0xfff || DX > 0xfff)
		overFlow = true;
}