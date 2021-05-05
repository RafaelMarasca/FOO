/********************************************************************************************
 * @file Graph.cpp
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 19 04 2021
 * @brief Implementação das classes de grafo utilizadas no projeto.
 * 
 * Este arquivo contém as implementações dos métodos e membros utilizados por duas classes 
 * de grafo distintas. 
 * 
 * A classe incidenceMatrix implementa um grafo que utiliza matriz 
 * de incidência como estrutura base. 
 * 
 * A classe adjacencyMatrix implemeta um grafo 
 * utilizando matriz de adjacência como estrutura base.
 *  
 ********************************************************************************************/

#include "Graph.h"
#include <vector>
#include <stack>

namespace GRF{

	//Construtor da matriz se chamado sem parâmetro, cria a matriz apenas com um vértice
	incidenceMatrix::incidenceMatrix() {
		vertexNumber = 0;
		edgeNumber = 0;
	}
	//Construtor da matriz, cria a matriz com 'v' vertices e 'e' edges
	incidenceMatrix::incidenceMatrix(unsigned int v,  unsigned int e) {
		for(unsigned int i = 0; i < v; i++)
			inMatrix.push_back(std::vector<int>(e, 0));

		vertexNumber = v;
		edgeNumber = e;
	}
	
	//Cria uma conexao entre vertices em um grafo que ja possui tamanho definido
	void incidenceMatrix::makeCon(unsigned int vtx1,  unsigned int vtx2,  unsigned int edg) {
		if(vtx1 >= vertexNumber or vtx2 >= vertexNumber or edg >= edgeNumber)
			throw ("Acesso invalido");

		inMatrix[vtx1][edg] = 1;
		inMatrix[vtx2][edg] = -1;
	}
	//Adiciona uma nova aresta no grafo
	void incidenceMatrix::addEdge(unsigned int vtx1,  unsigned int vtx2) {
		while(vertexNumber <= vtx1 or vertexNumber <= vtx2) {
            inMatrix.push_back(std::vector<int>(edgeNumber, 0));
			vertexNumber++;
		}

		for(unsigned int k = 0; k < vertexNumber; k++)
			inMatrix[k].push_back(0);

		inMatrix[vtx1][edgeNumber] = 1;
		inMatrix[vtx2][edgeNumber] = -1;
		edgeNumber++;
	}

	void incidenceMatrix::removeEdge(unsigned int edg){
		if(edg >= getEdgeNumber())
			throw "Acesso invalido";

		for(unsigned int i = 0; i < getEdgeNumber();i++){
			if(i > edg){
				for(unsigned int j = 0; j < getVertexNumber(); j++){
					inMatrix[j][i-1] = inMatrix[j][i];
				}
			}
		}
		for(unsigned int i = 0; i < getVertexNumber(); i++){
			inMatrix[i].pop_back();
		}
		edgeNumber--;
	}

	void incidenceMatrix::removeVertex(unsigned int vtx){
		if(vtx >= getVertexNumber())
			throw "Acesso invalido";

		for(unsigned int i = 0; i < getVertexNumber(); i++){
			if(i>vtx){
				for(unsigned int j = 0; j < getEdgeNumber(); j++){
					inMatrix[i-1][j] = inMatrix[i][j];
				}
			}
		}
		inMatrix.pop_back();
		vertexNumber--;
	}

	unsigned int incidenceMatrix::getVertexNumber() {
		return this->vertexNumber;
	}

	unsigned int incidenceMatrix::getEdgeNumber() {
		return this->edgeNumber;
	}

	std::vector<int> incidenceMatrix::getLoop(unsigned int key){
		
		if(key>=vertexNumber)
			throw "Acesso invalido";

		std::vector<int> vEdg(edgeNumber,0);
		std::stack<unsigned int> aux;

		unsigned int vtx = 0;
		bool found = false;
		
		aux.push(key);

		while(not aux.empty() and not found){

			vtx= aux.top();
			
			for(unsigned int i= 0; i<getEdgeNumber(); i++){
				if(inMatrix[vtx][i] and not vEdg[i]){
					unsigned int j = getVertexCon(vtx,i);
					aux.push(j);
					vEdg[i]= inMatrix[vtx][i];
					if (j ==key)
						found = true;
					break;
				}
			}
				
			if(vtx==aux.top() and not found){
				std::vector<unsigned int>temp = getEdges(vtx);
				
				for(unsigned int i = 0; i<temp.size();i++)
					vEdg[temp[i]] = 2;

				aux.pop();
			}	
		}

		for(unsigned int i = 0; i< vEdg.size();i++){
			if(vEdg[i]==2)
				vEdg[i] =0;
		}

		return vEdg;;
	}
	//Retorna uma arvore geradora para o grafo
	incidenceMatrix incidenceMatrix::getSpanningTree(unsigned int key){
		
		if(key>=vertexNumber)
			throw "Acesso invalido";

		std::vector<bool> visited(vertexNumber,false);
		std::stack<unsigned int> aux;
		incidenceMatrix tree(vertexNumber,edgeNumber);
		unsigned int vtx = 0;
		
		aux.push(key);

		while(not aux.empty()){

			vtx= aux.top();
			visited[vtx]=true;

			for(unsigned int i= 0; i<edgeNumber; i++){

				unsigned int j = getVertexCon(vtx,i);

				if(inMatrix[vtx][i] and not visited[j]){
					aux.push(j);
					try{
						tree.makeCon(vtx,j,i);
					}catch( char* msg){
						std::cout<<msg;
					}
					break;
				}
			}
			if(vtx==aux.top())
				aux.pop();			
		}	
		return tree;
	}
	//Retorna o vertice que esta ligado a vtx pela aresta edg
	unsigned int incidenceMatrix::getVertexCon(unsigned int vtx,  unsigned int edg) {

		if(vtx>=vertexNumber or edg>=edgeNumber)
			throw("Acesso invalido");

		if(inMatrix[vtx][edg]){
			for(unsigned int i = 0;i<vertexNumber;i++){
				if(i!= vtx and inMatrix[i][edg])
					return i;
			}
		}
		return vtx; 
	}

	std::vector<unsigned int> incidenceMatrix::getEdges(unsigned int vtx){
		if (vtx>=getVertexNumber()){
			throw "Acesso invalido";
		}
		
		std::vector<unsigned int>temp;
		
		for(unsigned int i = 0; i<getEdgeNumber();i++){
			if(inMatrix[vtx][i])
				temp.push_back(i); 
		}
		return temp;
	}

	std::vector<unsigned int> incidenceMatrix::getEdges(unsigned int vtx1,  unsigned int vtx2){
		
		if(vtx1>=getVertexNumber() or vtx2>=getVertexNumber())
			throw "Acesso invalido";

		std::vector<unsigned int> temp;
		
		for(unsigned int i = 0; i<edgeNumber;i++){
			if(inMatrix[vtx1][i] and inMatrix[vtx2][i])
				temp.push_back(i);
		}
		return temp;
	}

	std::pair<unsigned int,unsigned int> incidenceMatrix::getVertex(unsigned int edg){
		
		if(edg>=edgeNumber)
			throw "Acesso invalido";
		
		std::pair<unsigned int,unsigned int> vtx(0,0);

		for(unsigned int i= 0; i<vertexNumber; i++){
			if(inMatrix[i][edg]){
				if(inMatrix[i][edg]==1)
					vtx.first=i;
				else
					vtx.second=i;
			}
		}
		return vtx;
	}

	unsigned int incidenceMatrix::getConNum(unsigned int vtx){
		if(vtx>=getVertexNumber())
            return 0;//throw "Acesso invalido";
		unsigned int num = 0;

		for(unsigned int i = 0; i<getEdgeNumber();i++){
			if(inMatrix[vtx][i])
				num++;
		}
		return num;
	}
	//Printa o grafo na representacao de matriz de incidencia
	void incidenceMatrix::print(){
		
		for(unsigned int i = 0; i<vertexNumber;i++){
			for(unsigned int k = 0; k<edgeNumber;k++)
				std::cout<<inMatrix[i][k]<<" ";
			std::cout<<std::endl;
		}
	}

    adjacencyMatrix::adjacencyMatrix() {
            vertexNumber = 0;
            //  Inicializa o número de vértices como V, aloca um vector de vectos preenchido com null
            //e passa esse vector de vectors para a matriz de adjacência.
        }
    adjacencyMatrix::adjacencyMatrix(unsigned int vertexNum) {
            vertexNumber = vertexNum;
            adjMatrix = std::vector<std::vector<int>>(vertexNum,std::vector<int>(vertexNum,0));
            //  Inicializa o número de vértices como V, aloca um vector de vectos preenchido com null
            //e passa esse vector de vectors para a matriz de adjacência.
        }

        //Insere um dado ponteiro para T na posição (i,j) da matriz
        void adjacencyMatrix::insertEdge(unsigned int i, unsigned int j){

            while(i >= vertexNumber || j >= vertexNumber){

                adjMatrix.push_back(std::vector<int>(vertexNumber,0));
                vertexNumber++;
            }

            for(unsigned int i = 0; i< vertexNumber; i++)
            {
                while(adjMatrix[i].size()<vertexNumber){
                    adjMatrix[i].push_back(0);
                }
            }

            adjMatrix[i][j] = 1;
        }

        //Deleta o ponteiro em (i,j) e faz (i,j) apontar para null (redundante?)

        void adjacencyMatrix::removeVertex(unsigned int vertex) {

            if(vertex >= vertexNumber)
                throw std::string("Acesson Invalido");

            for(unsigned int i = 0; i < vertexNumber; i++){
                if(i>vertex)
                    std::swap(adjMatrix[i-1],adjMatrix[i]);
            }

            for(unsigned int i = 0; i < vertexNumber;i++){
                if(i > vertex){
                    for(unsigned int j = 0; j < vertexNumber; j++){
                        adjMatrix[j][i-1] = adjMatrix[j][i];
                    }
                }
            }
            for(unsigned int i = 0; i < vertexNumber-1; i++){
                adjMatrix[i].pop_back();
            }

            adjMatrix.pop_back();
            vertexNumber--;
        }

    //Getter da posição (i,j)
    int adjacencyMatrix::query(unsigned int i, unsigned int j) {

        if(i>=vertexNumber||j>=vertexNumber)
            return 0;

        return adjMatrix[i][j];
    }

    unsigned int adjacencyMatrix::getVertexNumber(){return vertexNumber;}

}
