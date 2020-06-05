#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <circuit/circuit.hpp>
#include <component/component.hpp>
#include <component/resistor.hpp>
#include <component/capacitor.hpp>
#include <component/inductor.hpp>
#include <component/voltageControlledVoltageSource.hpp>
#include <component/currentControlledVoltageSource.hpp>
#include <component/voltageControlledCurrentSource.hpp>
#include <component/currentControlledCurrentSource.hpp>
#include <component/opamp.hpp>

#include "linearAnalysis.hpp"
#include "nonLinearAnalysis.hpp"

#include "output.hpp"

void outputCSV(Circuit& c, string outputFileName){
    //get references to the components stored inside the circuit
    vector<Component*> components = c.getComponentsRef();
    vector<Component*> voltageSources = c.getVoltageSourcesRef();
    vector<Component*> currentSources = c.getCurrentSourcesRef();
    vector<Component*> conductanceSources = c.getConductanceSourcesRef();

    //get simulation parameters from circuit
    float timeStep = c.getTimeStep(); //Change once we have implemented a dynamic timestep (Currently we are using the printing step tStep as the static timestep)
    float simulationTime = c.getSimulationTime();
    // float tStep = c.getTStep(); //printing increment for csv file
    // float maxTimeStep = c.getMaxTimeStep(); //used for dynamic timestep

    //setup csv file
    ofstream outputFile;
    outputFile.open(outputFileName);

    //add headers to csv file
    //display time, node voltages, current through components
    outputFile << "time";
    int highestNodeNumber = c.getHighestNodeNumber();
    for(int i{1}; i<=highestNodeNumber; i++){
        outputFile << ",v_" + to_string(i);
    }
    for(const auto &comp : components){
        outputFile << ",i_" + comp->getName();
    }
    outputFile << "\n";
    
    runAnalysis(c, outputFile, timeStep, simulationTime);
    
    outputFile.close();
}

void runAnalysis(Circuit& c, ofstream& outputFile, float timeStep, float simulationTime){
    // c.setHasNonLinearComponents(true); //TESTING ONLY
    
    string outLine{};
    if(false && !c.hasNonLinearComponents()){
        //DC operating point analysis. Results are not written to CSV file.
        linearDCSetup(c);
        runLinearTransience(c, -1);
	//c.setupXMeaning();	
	//cerr << c.getX() << endl;
        // linearDCSetup(c);
        // runLinearTransience(c, -1);
        // cout << c.getB() <<endl<<endl; //testing only
        // cout << c.getA() <<endl;
        // c.setupXMeaning();
        // for(auto & el : c.getXMeaning()){
        //     cout << el <<endl;
        // }
	

        linearSetup(c);
        for(float t = 0; t<=simulationTime; t += timeStep){
            outLine = runLinearTransience(c, t); 
            // cout << c.getB() <<endl<<endl; //testing only
            // cout << c.getA() <<endl;
            // break;
            outputFile << outLine << endl;
        }
    }else{
        nonLinearSetup(c);
       // for(float t = 0; t<=simulationTime; t += c.getTimeStep()){// could replace with a while loop if we ever do dynamic time steps
while(c.getCurrentTime() < simulationTime){
            outLine = runNonLinearTransience(c, c.getCurrentTime());
	    c.setCurrentTime(c.getCurrentTime() + c.getTimeStep());
            outputFile << outLine << endl;
	    cerr << "Output Cycle" << endl;
	    //cerr << "Time: " << c.getCurrentTime() << endl;//+c.getTimeStep() << "Simulation Time: " << simulationTime << endl;	    
		if(c.getCurrentTime() > simulationTime){
			c.setCurrentTime(simulationTime);
			cerr << "Time: " << simulationTime << endl;
			c.setTimeStep(simulationTime - c.getPrevTime());			
			outLine = runNonLinearTransience(c,simulationTime);
			c.setCurrentTime(c.getCurrentTime() + c.getTimeStep());
			outputFile << outLine << endl;
			//return;
	    }
        }
    }
}
