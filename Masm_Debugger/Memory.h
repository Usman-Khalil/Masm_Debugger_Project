#ifndef MEMORY_H
#define MEMORY_H


// Parent Class :

class Memory
{

public:

    int (*memoryView)[16] = new int[256][16]();
    char (*memoryRepresentation)[16] = new char[256][16]();
    int memoryPointer = 0x0100;

    // Functions

    void fillFakeMemory();
    Memory();
    ~Memory();
};

#endif
