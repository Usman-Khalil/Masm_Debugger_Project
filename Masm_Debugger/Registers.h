#ifndef REGISTERS_H
#define REGISTERS_H
#include <string>
class Registers
{
public:
	unsigned short int AX = 0x0000,
		BX = 0x0000,
		CX = 0x0000,
		DX = 0x0000,
		SP = 0x0000,
		BP = 0x0000,
		DI = 0x0000,
		SI = 0x0000,
		DS = 0x0000,
		ES = 0x0000,
		SS = 0x0000,
		CS = 0x0000,
		IP = 0x0100;


	void displayRegiters();
	short int getInsPointer();

};


#endif