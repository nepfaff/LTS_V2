#ifndef INDUCTOR_HPP
#define INDUCTOR_HPP

#include "component.hpp"

class Inductor: public Component{
private:
	double inductance;
	double compCurrent;//Value of the current source in the companion model
	double compVoltage; //value of the voltage across the inductor
	double compConductance;//Conductance of the resistor in the companion model
	double prevVoltage; //Voltage across the inductor in the previous iteration.
	double prevCurrent;
	double prevTotalCurrent;

public:
	Inductor(string name, vector<string> args, vector<double> extraInfo);
	Inductor(string _name, double l, int n1, int n2, double timeStep, int order);
	~Inductor() = default;
	double getConductance() const override;
	vector<int> getNodes() const ;
	double getCurrent() const override;
	double getTotalCurrent(double voltage, int order = 1) override;
	void updateVals(double newVoltage, double newCurrent, int order) override; //Called at the end of every iteration, after calculating node voltages and component currents.
};

#endif
