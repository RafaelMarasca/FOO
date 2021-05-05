/********************************************************************************************
 * @file Component.h
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 30 04 2021
 * @brief Declaração da classe Component.
 * 
 * Este arquivo contém as ideclarações dos métodos e membros da classe Component.
 * 
 * A classe Component fornece os métodos e definições para se criar e alterar objetos 
 * da classe Component. Estes objetos são necessários para se resolver o circuito.
 *  
 ********************************************************************************************/


#ifndef COMPONENT_H
#define COMPONENT_H

#include<string>
#include<iostream>

namespace CMP {

    /*************************************************************************
     * Fornece uma identificação para os tipos de componentes disponíveis
     * no programa.
     *
     * Estas identificações são utilizadas nos métodos da classe para se
     * tomar ações com base no tipo especificado.
     *************************************************************************/
    enum type {
        RESISTOR, /**< Componente do tipo Resistor.*/
        VCC /**< Fonte de Tensão de corrente contínua*/
    };

    /***************************************************************************
     * Declaração da classe abstrata Component.
     *
     * Representa um componente genérico, especificando os atributos em comum
     * de qualquer componente presente no circuito. Esta classe é desenvolvida
     * para a utilização conjunta com a classe Circuit.
     ***************************************************************************/
    class Component {

        protected:
            std::string label; /**< Armazena o nome de identificação do componente.*/
            std::pair<unsigned int, unsigned int> vtxs; /**< Armazena um par de inteiros utilizados para
                                                             identificar os veértices do componente.*/
            double voltage; /**< Armazena a tensão através dos terminais do componente.*/
            double current; /**< Armazena a corrente através dos terminais do componente.*/

        public:

           /******************************************************************************************
            * Construtor para a classe Component.
            *
            * Constroi um objeto da Classe Component com os parâmetros específicados.
            *
            * @param l Nome para a identificação do componente.
            * @param vtx1 Identificação do terminal 1 do componente.
            * @param vtx2 Identificação do terminal 2 do componente.
            ******************************************************************************************/
            Component(std::string l,  unsigned int vtx1,  unsigned int vtx2);

           /******************************************************************************************
            * Desconstrutor virtual da classe Component.
            *
            * Destrói um objeto da classe Component.
            ******************************************************************************************/
            virtual ~Component();

           /******************************************************************************************
            * Setter para o nome de identificação de um objeto da classe Component.
            *
            * Aletera o nome do objeto para newLabel.
            *
            * @param newLabel Novo nome de identificação do componente.
            *
            * return Void.
            ******************************************************************************************/
            void setLabel(std::string newLabel);

           /******************************************************************************************
            * Getter para o nome de identificação de um objeto da calsse Component.
            *
            * Retona o nome de identificação do objeto em formato no formato std::string.
            *
            * @return Nome de identificação do componente.
            ******************************************************************************************/
            std::string getLabel();

           /******************************************************************************************
            * Getter para a tensão de um objeto da classe Component.
            *
            * Retorna a tensão através dos terminais do componente representado pelo objeto.
            *
            * @return Tensão do componente.
            ******************************************************************************************/
            double getVoltage();

           /******************************************************************************************
            * Getter para a corrente de um objeto da classe Component.
            *
            * Retorna a corrente  através dos terminais do componente representado pelo objeto.
            *
            * @return Corrente do componente.
            ******************************************************************************************/
            double getCurrent();

           /******************************************************************************************
            * Getter para os vértices (terminais) de um objeto da classe Component.
            *
            * Retorna um std::pair constendo os vértices que representam os terminais do componente.
            * O primeiro elemento do pair representa o vértice 1 e o segundo elemento representa o
            * vértice 2.
            *
            * @return Vértices do componente.
            ******************************************************************************************/
            std::pair<unsigned int, unsigned int> getNodes();

           /******************************************************************************************
            * Getter para o tipo de um objeto da classe Component.
            *
            * Método virtual puro que retorna o tipo do objeto. Este método deve ser sobrescrito
            * pelas classes derivadas, pois cada componente tem seu tipo.
            *
            * @return Tipo do objeto.
            ******************************************************************************************/
            virtual enum type getType() = 0;

           /******************************************************************************************
            * Setter para a tensão de um objeto da classe Component.
            *
            * Método virtual puro que altera a tensão do componente.
            *
            * @param value Valor para o parâmetro utilizado para alterar a corrente de um objeto da
            * classe Component. Este método deve ser sobrescrito pelas classes derivadas, uma vez
            * que, cada componente possui uma forma específica de se atribuir a tensão.
            *
            * @return Void.
            ******************************************************************************************/
            virtual void setVoltage(double value) = 0;

           /******************************************************************************************
            * Setter para a corrente de um objeto da classe Component.
            *
            * Método virtual puro que altera a corrente do componente.
            *
            * @param value Valor para o parâmetro utilizado para alterar a corrente de um objeto da
            * classe Component. Este método deve ser sobrescrito pelas classes derivadas, uma vez
            * que, cada componente possui uma forma específica de se atribuir a corrente. Apesar de
            * neste projeto ambos os componentes possuírem a mesma forma de se atribuir a corrente,
            * o método é virtual puro pois, em futuras atualizações, outros tipos de componentes
            * podem ser adicionados.
            *
            * @return Void.
            ******************************************************************************************/
            virtual void setCurrent(double value) = 0;
    };


   /******************************************************************************
    * Declaração da classe Resitor.
    *
    * Classe derivada de Component. Esta classe fornece os métodos necessários
    * para a manipulação de um objeto que representa um resistor.
    ******************************************************************************/
    class Resistor : public Component {

        private:
            double resistance; /**< Armazena a resistência do resistor.*/

        public:

           /******************************************************************************************
            * Construtor para a classe Resistor.
            *
            * Constroi um objeto da Classe Resistor com os parâmetros específicados.
            *
            * @param l Nome para a identificação do resistor.
            * @param res Valor da resistência do resistor.
            * @param vtx1 Identificação do terminal 1 do resistor.
            * @param vtx2 Identificação do terminal 2 do resistor.
            ******************************************************************************************/
            Resistor(std::string l,  double res,  unsigned int vtx1,  unsigned int vtx2);

           /******************************************************************************************
            * Desconstrutor para a classe Resistor.
            *
            * Destrói um objeto da classe Resistor.
            ******************************************************************************************/
            ~Resistor();

           /******************************************************************************************
            * Getter para a resistência de um objeto da classe Resistor.
            *
            * Retorna o valor da resistência do objeto.
            *
            * @return Resistência do Resistor.
            ******************************************************************************************/
            double getResistance() ;

           /******************************************************************************************
            * Setter para a resistência de um objeto da classe Resistor.
            *
            * Altera o valor da resistência do objeto.
            *
            * @return Void.
            ******************************************************************************************/
            void setResistance(double res);

           /******************************************************************************************
            * Getter para o tipo do componente da classe Resistor.
            *
            * Retorna enum type RESISTOR.
            *
            * @return RESISTOR.
            ******************************************************************************************/
            enum type getType() ;

           /******************************************************************************************
            * Setter para a corrente do resistor.
            *
            * Altera a corrente do resistor com base no parâmetro passado.
            *
            * @param value Valor da corrente através do resistor.
            *
            * @return Void.
            ******************************************************************************************/
            void setCurrent(double value);

           /******************************************************************************************
            * Setter para a tensão do resistor.
            *
            * Altera a tensão do resistor com base no parâmetro passado.
            *
            * @param value Valor da corrente através do resistor.
            *
            * @return Void.
            ******************************************************************************************/
            void setVoltage(double value);
    };


   /****************************************************************************
    * Declaração da classe Vcc.
    *
    * Classe derivada de Component. Esta classe fornece os métodos para a
    * manipulação de um objeto que representa uma fonte de tensão de corrente
    * contínua.
    ****************************************************************************/
    class Vcc : public Component{

        public:

        /******************************************************************************************
         * Construtor para a classe Vcc.
         *
         * Constroi um objeto da Classe Vcc com os parâmetros específicados.
         *
         * @param l Nome para a identificação da fonte.
         * @param vol valor da tensão da fonte.
         * @param vtx1 Identificação do terminal negativo da fonte.
         * @param vtx2 Identificação do terminal positivo da fonte.
         ******************************************************************************************/
            Vcc(std::string l,  double vol,  unsigned int negative,  unsigned int positive);

           /******************************************************************************************
            * Desconstrutor para a classe Vcc.
            *
            * Destrói um objeto da classe Vcc.
            ******************************************************************************************/
            ~Vcc();

           /******************************************************************************************
            * Getter para o tipo do componente da classe Vcc.
            *
            * Retorna enum type VCC.
            *
            * @return VCC.
            ******************************************************************************************/
            enum type getType();

           /******************************************************************************************
            * Setter para a corrente da fonte.
            *
            * Altera a corrente da fonte com base no parâmetro passado.
            *
            * @param value Valor da corrente através da fonte.
            *
            * @return Void.
            ******************************************************************************************/
            void setCurrent(double cur);

           /******************************************************************************************
            * Setter para a tensão do fonte
            *
            * Altera a tensão da fonte com base no parâmetro passado.
            *
            * @param value Valor da tensão da fonte.
            *
            * @return Void.
            ******************************************************************************************/
            void setVoltage(double vol);
    };
}
#endif // COMPONENT_H
