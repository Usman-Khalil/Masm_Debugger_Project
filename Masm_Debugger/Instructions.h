#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include "Memory.h"
#include "Registers.h"
using namespace std;

// Child class which inherit the properties from the parent class "Memory" ;

class Instructions 
{
    int address,
        value,
        startingAddress,
        endingAddress;

public:

    // Display memory which either take the  address or use the default memory pointer;
    void Dump();
    // Function for the implementation of enter command;
    void Enter();
    // Function for the implementation of the hex command 
    void Hex();
    // Function that will fill the value input by the user in the range of addresses also input by the user;
    void Fill();
    // Function for the implementation of the move instruction that move the content of range of address to  another addres "It take the range and starting address where and content is  to be moved as a input from the user.";
    void Move();
    // Take the range of addresses and value input from the  user and print the addresses where the target value is found
    void Search();
    // Take the range and starting address input from the user and compare the content of addresses corresspondingly and display the address and there respective content where it is contradictory;
    void Compare();

    void loadRegisters();
    void Assemble();
    void Unassemble();
    void Trace();
    void Help();
    void seperateOperandForMovAndInc(string, string& , int&);
    void seperateOperandForAdd(string, string&, string&);
};


#endif
