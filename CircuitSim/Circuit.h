#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "Graph.h"
#include "Component.h"
#include <vector>
#include <string>

namespace CCT{

/*********************** CIRCUIT *************************/

	class Circuit:public GRF::incidenceMatrix{

	private:
        std::vector<CMP::Component*> components;
		std::vector<std::vector<int>> circuitMatrix;
		std::vector<unsigned int> chords;
		std::vector<double> potential;
		unsigned int ground;

        void updateComponents(std:: vector<double> currents,std:: vector<double> potentials);

        public:
		Circuit();
        Circuit(std::vector<std::vector<int>> matrix, std::vector<CMP::Component*> comp);
		~Circuit();

        void load(std::fstream& input);
        void save(std::fstream& output);

		void initialize();
		void reset();
        void addComponent(CMP::type t,std::string l,double value, unsigned int vtx1, unsigned int vtx2);
		void setGround(unsigned int vtx);
        void editComponent(std::string label, double value);
        void editComponent(std::string label, std::string newLabel);
		void removeComponent(std::string l);

		void Solve();

		double getVoltage(unsigned int vtx1,unsigned int vtx2);
		double getVoltage(std::string l);
		double getPotential(unsigned int vtx);
		double getCurrent(std::string l);

		void printSol();
		void print();
		void printCM();
	};

}

#endif
