#include "Component.h"
#include<string>
#include<iostream>

/****************************** COMPONENT ************************************/

namespace CMP{

    Component::Component(std::string l, unsigned int vtx1, unsigned int vtx2){
        label = l;
        vtxs.first = vtx1;
        vtxs.second = vtx2;
    }

    Component::~Component(){}

    void Component::setLabel(std::string newLabel){
        label = newLabel;
    }

    std::string Component:: getLabel() {
        return label;
    }

    double Component::getVoltage() {
        return voltage;
    }

    double Component::getCurrent() {
        return current;
    }

    std::pair<unsigned int, unsigned int> Component::getNodes() {
        return vtxs;
    }

    Resistor::Resistor(std::string l,  double res,  unsigned int vtx1,  unsigned int vtx2) : Component(l, vtx1, vtx2) {
        resistance = res;
        voltage = 0;
        current = 0;
    }

    Resistor::~Resistor() {}

    double Resistor::getResistance() {
        return resistance;
    }

    enum type Resistor::getType() {
        return RESISTOR;
    }

    void Resistor::setResistance(double res) {
        resistance = res;
    }


    void Resistor::setCurrent(double cur) {
        current = cur;
    }

    void Resistor::setVoltage(double cur) {
        voltage = cur*resistance;
    }

    Vcc::Vcc(std::string l,  double vol,  unsigned int negative,  unsigned int positive):Component(l,negative,positive){
        voltage = vol;
        current = 0;
    }

    Vcc::~Vcc(){}

    enum type Vcc::getType(){
        return VCC;
    }

    void Vcc::setCurrent(double cur){
        current  = cur;
    }

    void Vcc::setVoltage(double vol){
        voltage = vol;
    }
}
