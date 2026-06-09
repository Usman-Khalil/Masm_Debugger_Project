#ifndef MEMORY_H
#define MEMORY_H


// Parent Class :

class Memory
{

public:

    int (*memoryView)[16] = new int[256][16]();
    char (*memoryRepresentation)[16] = new char[256][16]();
    short int memoryPointer = 0x0100;

    // Functions

    short int getMemoryPointer();
    void printMemory(short int);
    bool isValidMemoryAddress(short int);
    bool isValidMemoryRange(short int , short int);
    void saveMemoryInstruction(int, int, int);
    ~Memory();
};

#endif
