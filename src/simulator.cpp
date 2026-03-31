#include "../include/simulator.h"

using namespace std;

// ✅ Validate registers (UPDATED VERSION)
bool isValidRegister(string reg) {

    if(reg == "$zero") return true;

    if(reg.length() == 3 && reg[0] == '$') {
        char type = reg[1];
        char num = reg[2];

        // $t0-$t9
        if(type == 't' && num >= '0' && num <= '9') return true;

        // $s0-$s7
        if(type == 's' && num >= '0' && num <= '7') return true;

        // $a0-$a3
        if(type == 'a' && num >= '0' && num <= '3') return true;

        // $v0-$v1
        if(type == 'v' && num >= '0' && num <= '1') return true;
    }

    return false;
}

// ✅ Constructor
MIPSSimulator::MIPSSimulator() {

    instructionCount = 0;

    registers["$zero"] = 0;

    // $t0 - $t9
    for(int i = 0; i <= 9; i++)
        registers["$t" + to_string(i)] = 0;

    // $s0 - $s7
    for(int i = 0; i <= 7; i++)
        registers["$s" + to_string(i)] = 0;

    // $a0 - $a3
    for(int i = 0; i <= 3; i++)
        registers["$a" + to_string(i)] = 0;

    // $v0 - $v1
    for(int i = 0; i <= 1; i++)
        registers["$v" + to_string(i)] = 0;
}

// ✅ Load file and execute
void MIPSSimulator::loadFile(string filename) {

    ifstream file(filename);

    if(!file) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    string line;

    while(getline(file, line)) {

        // remove comments
        size_t comment = line.find('#');
        if(comment != string::npos)
            line = line.substr(0, comment);

        // skip empty lines
        if(line.find_first_not_of(" \t") == string::npos)
            continue;

        instructionCount++;

        executeInstruction(line);
    }

    file.close();
}

// ✅ Execute instructions
void MIPSSimulator::executeInstruction(string line) {

    // remove commas
    for(char &c : line)
        if(c == ',')
            c = ' ';

    stringstream ss(line);

    string instr, rd, rs, rt;
    int imm;

    ss >> instr;

    // 🔹 R-type instructions
    if(instr == "add" || instr == "sub" || instr == "mul" ||
       instr == "and" || instr == "or" || instr == "slt") {

        ss >> rd >> rs >> rt;

        if(!isValidRegister(rd) || !isValidRegister(rs) || !isValidRegister(rt)) {
            cout << "Error: Invalid register used\n";
            return;
        }

        if(instr == "add")
            registers[rd] = registers[rs] + registers[rt];

        else if(instr == "sub")
            registers[rd] = registers[rs] - registers[rt];

        else if(instr == "mul")
            registers[rd] = registers[rs] * registers[rt];

        else if(instr == "and")
            registers[rd] = registers[rs] & registers[rt];

        else if(instr == "or")
            registers[rd] = registers[rs] | registers[rt];

        else if(instr == "slt")
            registers[rd] = (registers[rs] < registers[rt]) ? 1 : 0;
    }

    // 🔹 ADDI instruction
    else if(instr == "addi") {

        ss >> rd >> rs >> imm;

        if(!isValidRegister(rd) || !isValidRegister(rs)) {
            cout << "Error: Invalid register used\n";
            return;
        }

        registers[rd] = registers[rs] + imm;
    }

    else {
        cout << "Error: Unknown instruction -> " << instr << endl;
    }
}

// ✅ Print final registers
void MIPSSimulator::printRegisters() {

    cout << "\nFinal Register State\n";
    cout << "-----------------------\n";

    cout << "Register\tValue\n";
    cout << "-----------------------\n";

    for(auto r : registers)
        cout << r.first << "\t\t" << r.second << endl;

    cout << "\nTotal Instructions Executed : " << instructionCount << endl;
}