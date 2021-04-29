#include "Circuit.h"
#include "Graph.h"
#include "Numeric.h"
#include <vector>
#include <string>
#include <stack>
#include <fstream>

namespace CCT{

/******************************* CIRCUIT ******************************/

	Circuit::Circuit(){ground = 0;}

	Circuit::~Circuit() {
		for(unsigned int i = 0; i<components.size();i++) {
			delete components[i];
		}
	}

    void Circuit::save(std::ofstream& output){
        std::pair<unsigned int,unsigned int> vtx;
        int32_t type;
        uint32_t size;
        uint32_t aux;
        double value;

        for(unsigned int i = 0; i < components.size(); i++){
            type = components[i]->getType();
            output.write(reinterpret_cast<char*>(&type), sizeof(CMP::type));

            size = components[i]->getLabel().size();
            output.write(reinterpret_cast<char*>(&size),sizeof(uint32_t));

            output.write((components[i]->getLabel()).c_str(),(components[i]->getLabel()).size());

            if(components[i]->getType() == CMP::RESISTOR){
                CMP::Resistor* R = dynamic_cast<CMP::Resistor*>(components[i]);

                if(R != nullptr){
                    value = R->getResistance();
                }else{
                    throw std::string("Falha");
                    return;
                }
            }else{
                value = components[i]->getVoltage();
            }

            output.write(reinterpret_cast<char*>(&value),sizeof(double));

            vtx = components[i]->getNodes();
            aux = vtx.first;
            output.write(reinterpret_cast<char*>(&aux),sizeof(uint32_t));
            aux = vtx.second;
            output.write(reinterpret_cast<char*>(&vtx.second),sizeof(uint32_t));
        }
    }

    void Circuit::load(std::ifstream &input){
        int32_t type;
        std::pair<uint32_t,uint32_t> vtx;
        uint32_t size;
        char byte;
        std::string label;
        double value;

        while(input.read(reinterpret_cast<char*>(&type),sizeof(int32_t))){
            input.read(reinterpret_cast<char*>(&size),sizeof(uint32_t));
            for(unsigned int j = 0; j < size; j++){
                input.read(&byte,sizeof(char));
                label.append(&byte,1);
            }

            input.read(reinterpret_cast<char*>(&value),sizeof(double));
            input.read(reinterpret_cast<char*>(&vtx.first),sizeof(uint32_t));
            input.read(reinterpret_cast<char*>(&vtx.second),sizeof(uint32_t));

            addComponent(CMP::type(type),label,value,vtx.first,vtx.second);
            label.clear();
           }
        }

    void Circuit::updateComponents(std::vector<double> currents, std::vector<double> pot) {
		std::pair<unsigned int, unsigned int> vtx;
		std::vector<unsigned int> aux;
		potential = pot;

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

    void Circuit::addComponent(CMP::type t,  std::string l,  double value,  unsigned int vtx1,  unsigned int vtx2) {
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
 
	void Circuit::setGround(unsigned int vtx) {
		if(vtx >= getVertexNumber())
			throw "Acesso Invalido";

		ground = vtx;
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

				if(not getConNum(aux.second))
					removeVertex(aux.second);

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
				Vin[i][0] = (components[i]->getVoltage());
            else if(components[i]->getType() == CMP::RESISTOR){
                CMP::Resistor *R = dynamic_cast<CMP::Resistor*> (components[i]);
		
			if(R != NULL)
				Z[i][i] = R->getResistance();
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

		NM::Matrix V = -(Z * I);
		NM::Matrix Mt = M.transpose();
		V += Vin;
		V = M * V;
		M = M * Mt;

		NM::EquationSystem PSys(M, V);
		NM::Matrix P = -PSys.getSolution(5e-8, 1000);

		double groundPotential = P[ground][0];

		for(unsigned int i = 0; i<P.getRowNumber();i++){
			P[i][0]-=groundPotential;
		}

        updateComponents(I.getCol(0),P.getCol(0));
	}

	double Circuit::getVoltage(unsigned int vtx1,  unsigned int vtx2) {
		if(vtx1 >= getVertexNumber() or vtx2 >= getVertexNumber())
			throw "Acesso invalido";

		return potential[vtx2] - potential[vtx1];
	}

	double Circuit::getVoltage(std::string l) {
		for(unsigned int i = 0; i < components.size(); i++) {
			if(components[i]->getLabel() == l)
				return components[i]->getVoltage();
			}
		throw "Componente nao encontrado";
	}

	double Circuit::getPotential(unsigned int vtx) {
		if(vtx >= getVertexNumber())
			throw "Acesso invalido";

		return potential[vtx];
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

	void Circuit::print() {
		for(unsigned int i = 0; i<getVertexNumber();i++){
			for(unsigned int k = 0; k<getEdgeNumber();k++){
				if(inMatrix[i][k]){
					std::cout<<components[i]->getLabel()<<"  ";
				}else{
					std::cout<<0<<"   ";
				}
			}			        
			std::cout<<std::endl;
		}
	}

	void Circuit::printCM() {
		for(unsigned int i = 0; i<circuitMatrix.size();i++){ 
			std::cout<<chords[i]<<": ";
			for(unsigned int k = 0; k<circuitMatrix[i].size();k++){
				if(circuitMatrix[i][k]){
					std::cout<<(components[k]->getLabel())<<"  ";
				}else{
					std::cout<<0<<"   ";
				}
			}
			std::cout<<std::endl;
		}
	}
}
