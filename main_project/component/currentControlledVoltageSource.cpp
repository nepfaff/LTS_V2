#include <string>
#include <iostream>

#include "currentControlledVoltageSource.hpp"

CurrentControlledVoltageSource::CurrentControlledVoltageSource(string name, vector<string> args, vector<float> extraInfo)
    :CurrentControlledSource(name, args, extraInfo)
{
    types.push_back(componentType::voltageSource);
}

float CurrentControlledVoltageSource::ivAtNode(int n) const{
    cerr << "ivAtNode not implemented in dependent voltage source" <<endl;
    exit(1);
}
float CurrentControlledVoltageSource::divAtNode(int n, int dn) const{
    cerr << "divAtNode not implemented in dependent voltage source" <<endl;
    exit(1);
}