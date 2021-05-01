#ifndef COMPONENT_H
#define COMPONENT_H

#include<string>
#include<iostream>

namespace CMP {

    enum type {RESISTOR,VCC,WIRE,GROUND};

    class Component {

        protected:
            std::string label;
            std::pair<unsigned int, unsigned int> vtxs;
            double voltage;
            double current;

        public:
            Component( std::string l,  unsigned int vtx1,  unsigned int vtx2);
            virtual ~Component();

            void setLabel(std::string newLabel);
            std::string getLabel();
            double getVoltage();
            double getCurrent();
            std::pair<unsigned int, unsigned int> getNodes();

            virtual enum type getType() = 0;

            virtual void setCurrent(double cur) = 0;
            virtual void setVoltage(double vol) = 0;

    };

    class Resistor : public Component {

        private:
            double resistance;

        public:
            Resistor(std::string l,  double res,  unsigned int vtx1,  unsigned int vtx2);
            ~Resistor();

            double getResistance() ;
            void setResistance(double res);

            enum type getType() ;

            void setCurrent(double cur);
            void setVoltage(double cur);
    };

    class Vcc : public Component{

        private:

        public:
            Vcc(std::string l,  double vol,  unsigned int negative,  unsigned int positive);
            ~Vcc();

            enum type getType();
            void setCurrent(double cur);
            void setVoltage(double vol);
    };
}
#endif // COMPONENT_H
