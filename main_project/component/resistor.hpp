#ifndef RESISTOR_HPP
#define RESISTOR_HPP

#include <vector>
#include <string>

#include "component.hpp"

class Resistor: public Component{
private:
    float conductance;
public:
    Resistor(string _name, vector<string> args, vector<float> extraInfo);
    Resistor(string _name, float r, int n1, int n2);
    ~Resistor() = default;

    float ivAtNode(int n1, int n2, int v) const override;
    float divAtNode(int n1, int n2, int dn, int v) const override;

    float getConductance() const override;
    vector<int> getNodes() const override;
};

#endif