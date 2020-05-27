#ifndef INDUCTOR_HPP
#define INDUCTOR_HPP

#include "component.hpp"

class Inductor: public Component{
private:
	float inductance;
	float compCurrent;//Value of the current source in the companion model
	float compVoltage; //value of the voltage across the inductor
	float compConductance;//Conductance of the resistor in the companion model
	float prevVoltage; //Voltage across the inductor in the previous iteration.
	float prevCurrent;
	float prevTotalCurrent;
	float timeStep; //used to update compConductance

public:
	Inductor(string name, vector<string> args, vector<float> extraInfo);
	~Inductor() = default;
	float getConductance() const override;
	vector<int> getNodes() const ;

	float ivAtNode(int n) const override;
    float divAtNode(int n, int dn) const override;

	float getCurrent() const override;
	float getTotalCurrent(const VectorXd &x, int highestNodeNumber, float voltage = 0, int order = 1)  override;
	void updateVals(float newVoltage, float newCurrent, int order) override; //Called at the end of every iteration, after calculating node voltages and component currents.
	void setTimeStep(float _timeStep) override;
};

#endif
