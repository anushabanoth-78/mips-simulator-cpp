#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

class MIPSSimulator {
private:
    std::map<std::string, int> registers;
    int instructionCount;

public:
    MIPSSimulator();
    void loadFile(std::string filename);
    void executeInstruction(std::string line);
    void printRegisters();
};

bool isValidRegister(std::string reg);

#endif