/********************************************************************************************
 * @file Component.cpp
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 30 04 2021
 * @brief Implementação da classe Component.
 * 
 * Este arquivo contém as implementações dos métodos e membros da classe Component.
 * 
 * A classe Component fornece os métodos e definições para se criar e alterar objetos 
 * da classe Component. Estes objetos são necessários para se resolver o circuito.
 *  
 ********************************************************************************************/

#include "Component.h"

#include<string>
#include<iostream>

namespace CMP{

    //Inicializa o componente.
    Component::Component(std::string l, unsigned int vtx1, unsigned int vtx2){
        label = l;
        vtxs.first = vtx1;
        vtxs.second = vtx2;
    }

    Component::~Component(){}

    //Altera o nome de identificação do componente.
    void Component::setLabel(std::string newLabel){
        label = newLabel;
    }

    //Retorna o nome de identificação do componente.
    std::string Component:: getLabel() {
        return label;
    }

    //Retorna a tensão do componente.
    double Component::getVoltage() {
        return voltage;
    }

    //Retorna a corrente do componente.
    double Component::getCurrent() {
        return current;
    }

    //Retorna os vértices do componente.
    std::pair<unsigned int, unsigned int> Component::getNodes() {
        return vtxs;
    }

    //Inicializa o Resistor.
    Resistor::Resistor(std::string l,  double res,  unsigned int vtx1,  unsigned int vtx2) : Component(l, vtx1, vtx2) {
        resistance = res;
        voltage = 0;
        current = 0;
    }

    Resistor::~Resistor() {}

    //Retorna a resistência do resistor.
    double Resistor::getResistance() {
        return resistance;
    }

    //Retorna o tipo de componente (Resistor).
    enum type Resistor::getType() {
        return RESISTOR;
    }

    //Altera a resistência do resistor.
    void Resistor::setResistance(double res) {
        resistance = res;
    }

    //Altera a corrente do resistor.
    void Resistor::setCurrent(double cur) {
        current = cur;
    }

    //Altera a tensão do resistor.
    void Resistor::setVoltage(double cur) {
        voltage = cur*resistance;
    }

    //Inicializa a tensão da fonte.
    Vcc::Vcc(std::string l,  double vol,  unsigned int negative,  unsigned int positive):Component(l,negative,positive){
        voltage = vol;
        current = 0;
    }

    Vcc::~Vcc(){}

    //Retorna o tipo de componente (Vcc)
    enum type Vcc::getType(){
        return VCC;
    }

    //Altera a corrente da fonte.
    void Vcc::setCurrent(double cur){
        current  = cur;
    }

    //Altera a tensão da fonte.
    void Vcc::setVoltage(double vol){
        voltage = vol;
    }
}
