/********************************************************************************************
 * @file Circuit.cpp
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 20 04 2021
 * @brief Implementação da classe Circuit.
 * 
 * Este arquivo contém as implementações dos métodos e membros da classe Circuit.
 * 
 * A classe Circuit fornece os métodos para se interligar objetos da classe Component e
 * obter os valores relacionados a cada um destes.
 *  
 ********************************************************************************************/

#include "Circuit.h"
#include "Graph.h"
#include "Numeric.h"

#include <vector>
#include <string>
#include <stack>
#include <fstream>

namespace CCT{
	/*************************************************************************
	 * Implementação dod métodos da classe Circuit.
	 * 
	 * Representa um circuito de componentes eletrônicos através de uma 
	 * matriz de incidência.
	 * 
	 *************************************************************************/


	
	Circuit::Circuit(){}

	Circuit::~Circuit() {
		for(unsigned int i = 0; i<components.size();i++) {
			delete components[i];
		}
	}

    void Circuit::updateComponents(std::vector<double> currents) {
		std::pair<unsigned int, unsigned int> vtx;
		std::vector<unsigned int> aux;

		for(unsigned int i = 0; i < components.size(); i++) {
			vtx = getVertex (i); 
			components[i]->setCurrent(currents[i]);

            if(components[i]->getType() == CMP::RESISTOR)
				components[i]->setVoltage(currents[i]);
		}
	}

	void Circuit::initialize() {
		incidenceMatrix temp,sTree = getSpanningTree(0);
		std::pair<unsigned int, unsigned int> edg;

		for(unsigned int i = 0; i<getEdgeNumber(); i++) {
			edg=sTree.getVertex(i);
			if(edg.first ==edg.second){
				chords.push_back(i);
				edg = getVertex(i);
				temp = sTree;
				temp.makeCon(edg.first,edg.second,i);
				circuitMatrix.push_back(temp.getLoop(edg.first));
			}
		}
		Solve();
	}

    void Circuit::reset() {
		while(chords.size())
			chords.pop_back();
		while(circuitMatrix.size())
			circuitMatrix.pop_back();
    }

    void Circuit::addComponent(CMP::type t,  std::string l,  double value,  unsigned int vtx1,  unsigned int vtx2){
        CMP::Component *C;

		for(unsigned int i = 0; i < components.size(); i++) {
			if(components[i]->getLabel() == l)
				throw " Nome invalido";
		}

		switch(t){
        case CMP::RESISTOR:
            C = new CMP::Resistor(l, value, vtx1, vtx2);
			break;

        case CMP::VCC:
            C = new CMP::Vcc(l, value, vtx1, vtx2);
			break;

		default:
			throw "Insercao invalida";
			break;
		}

		addEdge(vtx1, vtx2);
		components.push_back(C);
	}

	void Circuit::editComponent(std::string label, double value){

		for(unsigned int i = 0; i < components.size(); i++){
			if(label == components[i]->getLabel()){

				switch(components[i]->getType()){
                    case CMP::VCC:
						components[i]->setVoltage(value);
						return;
					break;

                    case CMP::RESISTOR:{
                        CMP::Resistor *R = dynamic_cast<CMP::Resistor*> (components[i]);
						
						if(R!=NULL)
							R->setResistance(value);
						else
							throw std::string("Erro ao atualizar componente.");
						return;
					}
					default:
						throw std::string("Componente invalido.");
					break;
				}
			}
		}
		throw std::string("Componente nao encontrado.");
	}

	void Circuit::editComponent(std::string label, std::string newLabel){

        CMP::Component* C = nullptr;

		if(newLabel == label)
			return;

		for(unsigned int i = 0; i < components.size(); i++){
			if(components[i]->getLabel() == newLabel)
				throw("label ja existente");

			if(components[i]->getLabel() == label )
				C = components[i];
		}

		if(C == nullptr)
			throw std::string("Componente nao encontrado.");

		C->setLabel(newLabel);
	}

	void Circuit::removeComponent(std::string l) {
		std::pair<unsigned int,unsigned int> aux;
		for(unsigned int i = 0; i < components.size(); i++){
			if(components[i]->getLabel() == l){
				aux = getVertex(i);
				removeEdge(i);

				if(not getConNum(aux.first))
					removeVertex(aux.first);

                if(not getConNum(aux.second)){
                    if(aux.second>aux.first)
                        removeVertex(aux.second-1);
                    else
                        removeVertex(aux.second);
                }

				unsigned int j = i+1;
                CMP::Component*C = components[i];
				while(j<components.size()){
					components[j-1]=components[j];
					j++;
				}
				delete C;
				components.pop_back();
				return;
			}
		}
		throw "Componente nao encontrado";
	}

	void Circuit::Solve() {
		NM::Matrix Z(getEdgeNumber(), getEdgeNumber());
		NM::Matrix Vin(getEdgeNumber());
		NM::Matrix I(getEdgeNumber());
		NM::Matrix M(getVertexNumber(),getEdgeNumber());

		for(unsigned int i = 0; i < getEdgeNumber(); i++) {
            if(components[i]->getType() == CMP::VCC)
                Vin[i][0] = -(components[i]->getVoltage());
            else if(components[i]->getType() == CMP::RESISTOR){
                CMP::Resistor *R = dynamic_cast<CMP::Resistor*> (components[i]);
		
			if(R != NULL)
                Z[i][i] = -R->getResistance();
			}

			for(unsigned int j = 0; j < getVertexNumber(); j++){
				M[j][i] = double(inMatrix[j][i]);
			}
		}

		if(chords.size() != 0){
			NM::Matrix B(chords.size(), getEdgeNumber());
			for(unsigned int i = 0; i < getEdgeNumber(); i++){
				for(unsigned int j = 0; j < chords.size(); j++){
					B[j][i] = double(circuitMatrix[j][i]);
				}
			}

			NM::Matrix Bt = B.transpose();
			NM::Matrix A = B * Z;
			A *= (Bt);
			B *= Vin;
			NM::EquationSystem curSys(A, B);
			I = curSys.getSolution(5e-8, 1000);
			I= Bt * I;
		}
        updateComponents(I.getCol(0));
	}

	double Circuit::getVoltage(std::string l) {
		for(unsigned int i = 0; i < components.size(); i++) {
			if(components[i]->getLabel() == l)
				return components[i]->getVoltage();
			}
		throw "Componente nao encontrado";
	}

	double Circuit::getCurrent(std::string l) {
		for(unsigned int i = 0; i<getEdgeNumber(); i++) {
			if(components[i]->getLabel()==l) {
				return components[i]->getCurrent();
			}
		}
		throw "Componente nao encontrado";
	}

    void Circuit::printSol() {
		for(unsigned int i = 0; i< components.size();i++){
			std::cout<<components[i]->getLabel()<<" V: "<<components[i]->getVoltage()<<" I: "<<components[i]->getCurrent()<<std::endl;
		}
	}

    /*void Circuit::print() {
		for(unsigned int i = 0; i<getVertexNumber();i++){
			for(unsigned int k = 0; k<getEdgeNumber();k++){
				if(inMatrix[i][k]){
                    std::cout<<components[k]->getLabel()<<"  ";
				}else{
					std::cout<<0<<"   ";
				}
			}			        
			std::cout<<std::endl;
		}
    }*/
}
