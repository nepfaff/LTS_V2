#include "circuit.hpp"
#include "capacitor.hpp"
#include "./CustomExceptionClasses/unsupportedIntegrationMethodOrderException.cpp"

Capacitor::Capacitor(string name, vector<string> args, vector<float> extraInfo)
    :Component{name}
{
    int n1 = stoi(args[0]);
    int n2 = stoi(args[1]);
    float val = getValue(args[2]);
	int order = 1;

	subComponents = 2;
	nodes.push_back(n1);
	nodes.push_back(n2);	
	comp_current = 0;
	
	if(order==1){ //Conductance of the capacitor will be the same as the companion model even at T=0 
		comp_conductance = (2.0*val)/extraInfo[0];
	}else{
		throw unsupportedIntegrationMethodOrderException();
	}

	types.push_back(0);
	types.push_back(2);
}

Capacitor::Capacitor(string _name,float c, int n1, int n2, float timeStep, int order)
	:Component{_name}, capacitance{c}{
	subComponents = 2;	
	nodes.push_back(n1);
	nodes.push_back(n2);	
	comp_current = 0;
	
	if(order==1){ //Conductance of the capacitor will be the same as the companion model even at T=0 
		comp_conductance = (2.0*c)/timeStep;
	}else{
		throw unsupportedIntegrationMethodOrderException();
	}

	types.push_back(0);
	types.push_back(2);
}

float Capacitor::getConductance() const{
	return comp_conductance;
}

float Capacitor::getCurrent() const{
	return comp_current;
}

void Capacitor::updateVals(float newVoltage, float newCurrent, int order){
	if(order==1){ //using companion model for the trapezoid integration method.
		newCurrent = (comp_conductance*newVoltage) - comp_current; //Current into capacitor = current through companion conductance - (as current source pointing towards + node) current source current.		
		comp_current = - newCurrent - (comp_conductance*newVoltage);
	}else{
		throw unsupportedIntegrationMethodOrderException();
	}
		
}
vector<int> Capacitor::getNodes() const{
    vector<int> res{};
    res.push_back(nodes.at(0));
    res.push_back(nodes.at(1));
    return res;
}
