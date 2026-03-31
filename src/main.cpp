#include "../include/simulator.h"

using namespace std;

int main(int argc, char* argv[]) {

    if(argc < 2) {
        cout << "Usage: ./simulator <asm_file>\n";
        return 1;
    }

    cout<<"=====================================\n";
    cout<<"        MIPS ASSEMBLY SIMULATOR\n";
    cout<<"=====================================\n";

    MIPSSimulator sim;

    sim.loadFile(argv[1]);

    sim.printRegisters();

    return 0;
}