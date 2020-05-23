#include <iostream>
#include <vector>
#include <fstream>

#include <circuit/circuit.hpp>
#include <input/input.hpp>
#include <output/output.hpp>

using namespace std;

// for debugging only
void testCircuit1(stringstream& buffer){
    buffer << "ExampleCircuit1" << endl;
    buffer << "V1 1 0 SIN(0 1 10)" << endl;
    buffer << "V1 2 0 10" << endl;
    buffer << "Q1 2 1 3" << endl;
}
void testCircuit3(stringstream& buffer){
    buffer << "ExampleCircuit3" << endl;
    buffer << "V1 1 0 5" << endl;
    buffer << ".model D1N4148 D (IS=1n N=1.2)" <<endl;
    buffer << "R1 1 2 1k" << endl;
    buffer << "R2 1 0 500" << endl;
    buffer << "D1 2 0 D1N4148" <<endl;
}
void testCircuit4(stringstream& buffer){
    buffer << "ExampleCircuit4" << endl;
    buffer << "V1 1 0 Pwl(.1 10 .2 5 .3 2)" << endl;
    buffer << "R1 2 0 1k" << endl;
    buffer << "L1 1 2 .1" << endl;
}
void testCircuit5(stringstream& buffer){
    buffer << "ExampleCircuit5" << endl;
    buffer << "V1 1 0 20" << endl;
    buffer << "R1 2 0 1k" << endl;
    buffer << "R2 1 2 1k" <<endl;
    buffer << "C1 2 0 1u" << endl;
}
void testCircuit(stringstream& buffer){
    buffer << "ExampleCircuit6" << endl;
    buffer << "I1 1 0 PWL(0 10 .1 0)" <<endl;
    buffer << "R1 1 0 1" <<endl;
    buffer << "R2 1 2 1k" <<endl;
    buffer << "R3 2 0 100k" <<endl;
    buffer << "C1 2 0 0.00001" <<endl;
}

int main(int argc, char **argv){
    //get optional input arguments
    string outputFileName = "out.csv";
    float timeStep = 0.0005; //seconds
    float simulationTime = .2; //seconds
    if(argc > 1){
        outputFileName = argv[1];
    }
    if(argc > 2){
        timeStep = (float)atof(argv[2]);
    }
    if(argc > 3){
        simulationTime = (float)atof(argv[3]);
    }

    // setup circuit
    Circuit c{};
    setupBasic(c, timeStep);
    stringstream buffer;
    testCircuit(buffer);

    readSpice(c, buffer);
    // readSpice(c, cin); //use this if want to read from txt file

    // run simulation
    outputCSV(c, outputFileName, timeStep, simulationTime);
}


