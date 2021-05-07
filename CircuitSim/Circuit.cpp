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
	
	Circuit::Circuit(){}

	Circuit::~Circuit() {
        //Libera a memória utilizada pelos componentes armazenados no circuito.
		for(unsigned int i = 0; i<components.size();i++) {
			delete components[i];
		}
	}

    void Circuit::updateComponents(std::vector<double> currents) {
		std::pair<unsigned int, unsigned int> vtx;
		std::vector<unsigned int> aux;

        //Percorre o vector de componentes e atualiza o falor da corrente.
		for(unsigned int i = 0; i < components.size(); i++) {
			vtx = getVertex (i); 
			components[i]->setCurrent(currents[i]);

            //Se for um resitor, atualiza a tensão através dos terminais.
            if(components[i]->getType() == CMP::RESISTOR)
				components[i]->setVoltage(currents[i]);
		}
	}

	void Circuit::initialize() {

        //Não inicializa o circuito se este estiver vazio
        if(getVertexNumber() == 0)
            return;

		incidenceMatrix temp,sTree = getSpanningTree(0);
		std::pair<unsigned int, unsigned int> edg;

        //Percorre o grafo original, verifica se o vértice está presente na árvore geradora
        //Para cada aresta não presente, adiciona esta à árvore geradora e encontra o único
        //ciclo existente e remove a aresta previamente adicionada.
		for(unsigned int i = 0; i<getEdgeNumber(); i++) {

            //Verifica se a aresta existe na árvore
            edg = sTree.getVertex(i);

            if(edg.first == edg.second){
				chords.push_back(i);
				edg = getVertex(i);
				temp = sTree;
				temp.makeCon(edg.first,edg.second,i);
                //Assimila o ciclo fundamental.
				circuitMatrix.push_back(temp.getLoop(edg.first));
			}
		}
        //Resolve o circuito.
		Solve();
	}

    //Reseta as matrizes de circuito e acorde, para que o circuito possa ser resolvido
    //após a edição sem que ocorram erros.
    void Circuit::reset() {
		while(chords.size())
			chords.pop_back();
		while(circuitMatrix.size())
			circuitMatrix.pop_back();
    }

    void Circuit::addComponent(CMP::type t,  std::string l,  double value,  unsigned int vtx1,  unsigned int vtx2){
        CMP::Component *C;

        //Verifica se um componente com mesmo nome de identificação já existe no circuito.
		for(unsigned int i = 0; i < components.size(); i++) {
			if(components[i]->getLabel() == l)
                throw std::string("Nome invalido");
		}
        //Verifica o tipo de componente que deve ser inserido.
		switch(t){
            case CMP::RESISTOR:
                C = new CMP::Resistor(l, value, vtx1, vtx2);
			break;

            case CMP::VCC:
                C = new CMP::Vcc(l, value, vtx1, vtx2);
			break;

            default:
                throw std::string("Insercao invalida");
			break;
		}

        //Adiciona a aresta ao grafo.
		addEdge(vtx1, vtx2);

        //Adiciona o componente inserido no vector de componentes do circuito.
		components.push_back(C);
	}

	void Circuit::editComponent(std::string label, double value){

        //Verifica se um componente com mesmo nome de identificação está presente no circuito
		for(unsigned int i = 0; i < components.size(); i++){
			if(label == components[i]->getLabel()){

				switch(components[i]->getType()){
                    //Caso o componente seja um fonte, altera a tensão.
                    case CMP::VCC:
						components[i]->setVoltage(value);
						return;
					break;

                    //Caso o componente seja o resistor, altera a resistência.
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

    //Altera o nome de identificação do componente.
	void Circuit::editComponent(std::string label, std::string newLabel){

        CMP::Component* C = nullptr;

		if(newLabel == label)
			return;

        //Verifica se o nome informado já existe no circuito.
		for(unsigned int i = 0; i < components.size(); i++){
			if(components[i]->getLabel() == newLabel)
                throw std::string("label ja existente");

			if(components[i]->getLabel() == label )
				C = components[i];
		}

		if(C == nullptr)
			throw std::string("Componente nao encontrado.");

        //Caso exista, altera o nome.
		C->setLabel(newLabel);
	}

	void Circuit::removeComponent(std::string l) {
		std::pair<unsigned int,unsigned int> aux;

        //Procura o componente
        for(unsigned int i = 0; i < components.size(); i++){

            //Se encontrou o componente remove os vértices da matriz de incidência
            //e do vector de componentes.
            if(components[i]->getLabel() == l){
				aux = getVertex(i);
				removeEdge(i);
                bool removedFirst = false;

				if(not getConNum(aux.first))
                {
                    removeVertex(aux.first);
                    removedFirst = true;
                }

                if(not getConNum(aux.second)){
                    if(aux.second>aux.first and removedFirst)
                        removeVertex(aux.second-1);
                    else
                        removeVertex(aux.second);
                }

				unsigned int j = i+1;
                CMP::Component*C = components[i];
                //Remove o componente do vector de componentes.
                while(j<components.size()){
					components[j-1]=components[j];
					j++;
				}

                delete C;
				components.pop_back();
				return;
			}
		}

        //Caso não encontre o componente.
        throw std::string("Componente nao encontrado");
	}


    std::string Circuit::getComponentLabel(unsigned int edge){

        //Verifica se a aresta existe no grafo.
        if(edge >= getEdgeNumber())
            throw std::string("Componente não existente");

        return components[edge]->getLabel();
    }


	void Circuit::Solve() {

        //Matriz de impedância (resistência) do circuito.
		NM::Matrix Z(getEdgeNumber(), getEdgeNumber());

        //Matriz das fontes de tensão do circuito.
		NM::Matrix Vin(getEdgeNumber());

        //Matriz das correntes do circuito.
		NM::Matrix I(getEdgeNumber());

        //Matriz das conexões do circuito.
		NM::Matrix M(getVertexNumber(),getEdgeNumber());

        //Adiciona as resistências dos componentes à matriz de impedância.
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

        //Resolve o circuito caso o circuito seja fechado.
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
        //Atualiza os componentes
        updateComponents(I.getCol(0));
	}

	double Circuit::getVoltage(std::string l) {
        //Procura pelo componente e retorna a tensão caso este exista.
        for(unsigned int i = 0; i < components.size(); i++){
			if(components[i]->getLabel() == l)
				return components[i]->getVoltage();
			}
        //caso o componente não tenha sido encontrado.
        throw std::string("Componente nao encontrado");
	}

	double Circuit::getCurrent(std::string l) {
        //Procura pelo componente e retorna a corrente caso este exista.
		for(unsigned int i = 0; i<getEdgeNumber(); i++) {
			if(components[i]->getLabel()==l) {
				return components[i]->getCurrent();
			}
		}

        //Caso o componente não exista.
        throw std::string("Componente nao encontrado");
	}
}
