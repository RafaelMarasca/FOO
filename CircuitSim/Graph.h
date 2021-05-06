/********************************************************************************************
 * @file Graph.h
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 19 04 2021
 * @brief Declaração das classes de grafo utilizadas no projeto.
 * 
 * Este arquivo contém as declarações dos métodos e membros utilizados por duas classes 
 * de grafo distintas. 
 * 
 * A classe incidenceMatrix implementa um grafo que utiliza matriz 
 * de incidência como estrutura base.
 * 
 * A classe adjacencyMatrix implemeta um grafo 
 * utilizando matriz de adjacência como estrutura base.
 *  
 ********************************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>

namespace GRF{

   /*************************************************************************
    * Declaração da classe incidenceMatrix.
    *
    * Representa um grafo direcionado através de uma matriz de incidência.
    * Cada vértice do grafo é representado por um número, conforme a ordem
    * de inserção, começando do 0.
    * Cada aresta do grafo é representada por um número, conforme a ordem
    * de inserção, começando do 0.
    *************************************************************************/
	class incidenceMatrix{

		private:
            unsigned int vertexNumber; /**< Armazena o número de vértices do grafo.*/
            unsigned int edgeNumber; /**< Armazena o número de arestas do grafo.*/

		protected:
            std::vector<std::vector<int>> inMatrix; /**< Vector bidimensional que armazena as conexões entre os vértices*/

		public:

           /*********************************************************************************************
            * Construtor para a classe incidenceMatrix.
            *
            * Constroi um objeto da classe incidenceMatrix cujo vetor de conexões está inicialmente
            * vazio.
            *********************************************************************************************/
			incidenceMatrix();

           /***********************************************************************************************
            * Construtor para a classe incidenceMatrix.
            *
            * Constroi um objeto da classe incidenceMatrix com número de vértices e arestas predefinido.
            *
            * @param v Número de vértices do grafo.
            * @param e Número de arestas do grafo.
            *
            * @overload
            ***********************************************************************************************/
			incidenceMatrix(unsigned int v,  unsigned int e);


           /***********************************************************************************************
            * Adiciona uma conexção entre dois vértices.
            *
            * Cria uma conexão entre dois vértices do grafo. A conexão é direcionada de vtx1 para vtx2.
            * Uma nova coluna é alocada dinâmicamente. Se ao menos um dos vértices não existe, estes são
            * criados até que a matriz tenha tamanho suficiente para armazená-lo.
            *
            * @param vtx1 Vértice de saída.
            * @param vtx2 Vértice de entrada.
            *
            * @return Void.
            ***********************************************************************************************/
			void addEdge(unsigned int vtx1,  unsigned int vtx2);


           /***********************************************************************************************
            * Cria uma conexão entre dois vértices em um objeto da classe incidenceMatrix.
            *
            * Cria uma conexão entre dois vértices do grafo, direcionado de vtx1 para vtx2, posicionando
            * estas conexões na aresta especificada, este método deve ser chamado apenas para arestas que
            * existam, mas que não possuam conexões.
            *
            * @param vtx1 Vértice de saída.
            * @param vtx2 Vértice de entrada.
            * @param edge Aresta que conecta ambos os vértices.
            *
            * @return Void.
            ***********************************************************************************************/
            void makeCon(unsigned int vtx1,  unsigned int vtx2,  unsigned int edge);


           /***********************************************************************************************
            * Remove uma conexão de um objeto da classe incidenceMatrix.
            *
            * Remove a aresta especificada existente entre dois vértices de um objeto, reduzindo o
            * tamanho da matriz através da remoção de uma coluna.
            *
            * @param edge Aresta a ser removida do grafo.
            *
            * @return Void.
            ***********************************************************************************************/
            void removeEdge(unsigned int edge);


           /***********************************************************************************************
            * Remove uma vértice de um objeto da classe incidenceMatrix.
            *
            * Remove o vértice especificado existente de um objeto, reduzindo o tamanho da matriz através
            * da remoção de uma linha. Todas as conexões entre este e outros vértices também é excluído.
            *
            * @param vtx Vértice a ser removido do grafo.
            *
            * @return Void.
            ***********************************************************************************************/
			void removeVertex(unsigned int vtx);


           /***********************************************************************************************
            * Getter para o número de vértices de um objeto da classe incidenceMatrix.
            *
            * Retorna o número de vértices do grafo.
            *
            * @return Número de vértices.
            ***********************************************************************************************/
			unsigned int getVertexNumber();


           /***********************************************************************************************
            * Getter para o número de arestas de um objeto da classe incidenceMatrix.
            *
            * Retorna o número de arestas do grafo.
            *
            * @return Número de arestas do grafo.
            ***********************************************************************************************/
			unsigned int getEdgeNumber();


           /*************************************************************************************************
            * Getter auxiliar prar obter um ciclo de um objeto da classe incidenceMatrix.
            *
            * Este método auxiliar foi desenvolvido para identificar o ciclo de um grafo que possui apenas
            * um loop.
            *
            * O vértice inicial deve fazer parte do ciclo.
            *
            * @param vtx Vértice de início da busca
            *
            * @return Vector de inteiros contendo as arestas do grafo. As arestas que fazem parte de um
            * ciclo dgrafo são marcadas com 1 se a aresta foi percorrida na direção atribuída ou -1 quando
            * esta foi percorrida na direção oposta da aresta. As arestas marcadas com 0 não fazem parte
            * do ciclo.
            *************************************************************************************************/
            std::vector<int> getLoop(unsigned int vtx);
			

           /***********************************************************************************************
            * Getter para a árvore geradora de um objeto da classe incidenceMatrix.
            *
            * Retorna a árvore geradora do grafo.
            *
            * @return Objeto da classe incidenceMatrix representando a árvore geradora do grafo.
            ***********************************************************************************************/
			incidenceMatrix getSpanningTree( unsigned int key);


           /***********************************************************************************************
            * Getter para um vértice de um objeto da classe incidenceMatrix.
            *
            * Retorna o vértice conectado a vtx pela aresta edge.
            *
            * @param vtx Vértice pertencente ao grafo.
            * @param edge Aresta pertencente ao grafo.
            *
            * @return Vértice conectado a vtx pela aresta edge.
            ***********************************************************************************************/
            unsigned int getVertexCon(unsigned int vtx,  unsigned int edge);


           /***********************************************************************************************
            * Getter para as arestas de um vértice de um objeto da classe incidenceMatrix.
            *
            * Retorna todas as arestas que conectam vtx a algum outro vértice.
            *
            * @param vtx Vértice pertencente ao grafo.
            *
            * @return std::vector contendo as arestas conectadas ao vértice vtx.
            ***********************************************************************************************/
			std::vector<unsigned int> getEdges(unsigned int vtx);
			

           /***********************************************************************************************
            * Getter para as arestas que conectam dois vértices de um objeto da classe incidenceMatrix.
            *
            * Retorna todas as arestas que conectam vtx1 e vtx2.
            *
            * @param vtx1 Vértice pertencente ao grafo.
            * @param vtx2 Vértice pertencente ao grafo.
            *
            * @return std::vector contendo as arestas que conectam ambos os vértices.
            *
            * @overload
            ***********************************************************************************************/
			std::vector<unsigned int> getEdges(unsigned int vtx1, unsigned int vtx2);


           /*****************************************************************************************************
            * Getter para os vértices que são conectados por uma aresta de um objeto da classe incidenceMatrix.
            *
            * std::pair contendo os 2 vértices que estão conectados por edge. O primeiro elemento do pair é o
            * vértice de saída enquanto que o segundo elemento do pair é o vértice de entrada da conexão.
            *
            * @param edge Aresta pertencente ao grafo.
            *
            * @return std::pair contendo os 2 vértices que estão conectados por edge.
            *****************************************************************************************************/
            std::pair<unsigned int,unsigned int> getVertex(unsigned int edge);


           /*****************************************************************************************************
            * Getter para o número de conexões de um vértice de um objeto da classe incidenceMatrix.
            *
            * Retorna o número de conexões que um vértice pertencente ao grafo possui.
            *
            * @param vtx Vértice pertencente ao grafo.
            *
            * @return Número de conexões de um vértice.
            *****************************************************************************************************/
			unsigned int getConNum(unsigned int vtx);	


           /**********************************************************************************************
            * Imprime um objeto da classe incidenceMatrix.
            *
            * Método para auxiliar no debug do código. Imprime a representação matricial da matriz de
            * incidência
            *
            * @return Void.
            **********************************************************************************************/
            void print();
	};


   /******************************************************************************
    * Declaração da classe adjacencyMatrix.
    *
    * Representa um grafo direcionado através de uma matriz de adjacências.
    ******************************************************************************/
    class adjacencyMatrix {

        private:
            unsigned int vertexNumber; /**< Armazena o número de vértices do grafo.*/
            std::vector<std::vector<int>> adjMatrix; /**< Vector bidimensional que armazena as conexões entre os vértices*/

        public:
           /*********************************************************************************************
            * Construtor para a classe adjacencyMatrix.
            *
            * Constroi um objeto da classe adjacencyMatrix cujo vetor de conexões está inicialmente
            * vazio.
            *********************************************************************************************/
            adjacencyMatrix();

           /***********************************************************************************************
            * Construtor para a classe adjacencyMatrix.
            *
            * Constroi um objeto da classe adjacencyMatrix com número de vértices predefinido.
            *
            * @param vertexNum Número de vértices do grafo.
            *
            * @overload
            ***********************************************************************************************/
            adjacencyMatrix(unsigned int vertexNum);


           /*******************************************************************************************************
            * Insere uma aresta entre dois vértices de um objeto da classe adjacencyMatrix.
            *
            * Insere dinâmicamente uma aresta entre dois vértices. Se ao menos um dos vértices não exise, são
            * criados novos vértices até que o grafo tenha o tamanho necessário para que se possa utilizar estes
            * vértices.
            *
            * @param vtx1 Vértice de saída.
            * @param vtx2 Vértice de entrada.
            *
            * @return Void.
            *******************************************************************************************************/
            void insertEdge(unsigned int vtx1, unsigned int vtx2);



            /*******************************************************************************************************
             * Insere um vértice em um objeto da classe adjacencyMatrix.
             *
             * Insere dinâmicamente um vértice no grafo. São criados novos vértices até que o grafo tenha o
             * tamanho necessário para que se possa utilizar o novo vértice. Caso o vértice já esteja no grafo,
             * não executa nada.
             *
             * @param vtx Vértice a ser inserido.
             *
             * @return Void.
             *******************************************************************************************************/
            void insertVertex(unsigned int vtx);



           /*********************************************************************************************************
            * Remove um vértice de um objeto da classe adjacencyMatrix.
            *
            * Remove um vértice do grafo. A linha e a coluna correspondentes ao vértice são removidas e o tamanho
            * do grafo é reduzido. Todos os vértices com com número maior são deslocados e têm seu número reduzido.
            *
            * @param vtx Vértice que se deseja remover.
            *
            * @return Void.
            *********************************************************************************************************/
            void removeVertex(unsigned int vtx);


           /*******************************************************************************************************
            * Verifica se há conexão entre 2 vértices de um objeto da classe adjacencyMatrix.
            *
            * Verifica se há uma conexão direcionada de vtxq para vtx2 no grafo.
            *
            * @param vtx1 Vértice de saída.
            * @param vtx2 Vértice de entrada
            *
            * @return 1 se há conexão e 0 se não há.
            *******************************************************************************************************/
            int query(unsigned int vtx1, unsigned int vtx2);


           /*******************************************************************************************************
            * Getter para o número de vértices de um objeto da classe adjacencyMatrix.
            *
            * Retorna o número de vértices presentes atualmente no grafo.
            *
            * @return Número de vértices do grafo.
            *******************************************************************************************************/
            unsigned int getVertexNumber();

    };


}
#endif
