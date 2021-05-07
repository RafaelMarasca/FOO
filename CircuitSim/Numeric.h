/********************************************************************************************
 * @file Numeric.h
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 19 04 2021
 * @brief IDeclaração das classe Matrix e EquationSystem..
 * 
 * Este arquivo contém a declarção dos métodos e membros da classe Numeric.
 * 
 * A classe Numeric fornece as clsses e métodos para se criar e resolver sistemas de 
 * equações.
 *  
 ********************************************************************************************/

#ifndef NUMERIC_H
#define NUMERIC_H

#include "Circuit.h"

#include <vector>
#include <iostream>

namespace NM {
   
   /*************************************************************************
    * Declaração da classe Matrix.
    *
    * Representa uma matriz matemática e implementa suas operações.
    ************************************************************************/
	class Matrix {
	private:
		std::vector<std::vector<double>> realMatrix; /**< Implementação concreta da matriz.*/
		unsigned int rowNumber; /**< Número de linhas da matriz.*/
		unsigned int colNumber; /**< Número de colunas da matriz.*/
	
	public:
	   /*********************************************************************************
    	* Construtor da classe Matrix.
    	*
        * Constrói uma matriz com um número escolhido linhas, preenchida com zeros.
    	* 
    	* @param r Número de linhas.
    	*********************************************************************************/
		Matrix(unsigned int r);
		

		/*************************************************************************
    	* Construtor da classe Matrix.
    	*
    	* Constrói uma matriz com um número escolhido de linhas e colunas, 
    	* preenchida com zeros.
    	*
    	* @param r Número de linhas.
    	* @param c Número de colunas.
		*
    	* @overload
    	*************************************************************************/
		Matrix(unsigned int r, unsigned int c);

		/*************************************************************************
    	* Sobrecarga do operador * da classe Matrix.
    	*
    	* Multiplica duas matrizes e retorna o resultado.
    	*
    	* @param &m1 referência à matriz que à direita.
    	*
		* @return Matriz à esquerda.
    	* @overload
    	*************************************************************************/
		Matrix operator* (Matrix &m1);
		
	  /*************************************************************************
    	* Sobrecarga do operador *= da classe Matrix.
    	*
    	* Multiplica duas matrizes e insere o resultado na matriz à esquerda.
    	*
    	* @param &m1 referência à matriz à direita.
		*
    	* @overload
    	*************************************************************************/
		void operator*= (Matrix &m1);	
		

		/*************************************************************************
    	* Sobrecarga do operador + da classe Matrix.
    	*
    	* Soma duas matrizes e retorna o resultado.
    	*
    	* @param &m1 referência à matriz à direita.
    	* @return Matriz à esquerda.
    	*
		* @overload
    	*************************************************************************/
		Matrix operator+ (Matrix &m1);
		
	   /*************************************************************************
    	* Sobrecarga do operador += da classe Matrix.
    	*
    	* Soma as entradas de duas matrizes e insere o resultado na primeira.
    	*
    	* @param &m1 referência à matriz que à direita.
    	* @overload
    	*************************************************************************/
		void operator+= (Matrix &m1);
		
		/*************************************************************************
    	* Sobrecarga do operador - da classe Matrix.
    	*
    	* Subtrai as entradas da matriz à direita da matriz à esquerda e retorna 
    	* o resultado.
    	* @param &m1 referência à matriz à direita.
    	*
		* @return Matriz à esquerda.
    	* @overload
    	*************************************************************************/
		Matrix operator- (Matrix &m1);
		
	   /*************************************************************************
    	* Sobrecarga do operador -= da classe Matrix.
    	*
    	* Subtrai as entradas matriz à direita da matriz à esquerda e insere o 
    	* resultado na matriz à esquerda.
    	*
    	* @param &m1 referência à matriz à direita.
    	* @overload
    	*************************************************************************/
		void operator-= (Matrix &m1);


	   /*************************************************************************
    	* Sobrecarga do operador = da classe Matrix.
    	*
    	* Substitui as entradas da matriz à esquerda pelas entradas da matriz à direita.
    	*
    	* @param &m1 referência à matriz que à direita.
    	* @overload
    	*************************************************************************/
		void operator= (const Matrix &m1);
		

	   /*************************************************************************
    	* Sobrecarga do operador [] da classe Matrix.
    	*
    	* Permite acesso direto aos valores presentes na matriz.
    	*
    	* @param index número da linha que será considerada.
		*
    	* @return Linha do índice index.
    	* @overload
    	*************************************************************************/
		std::vector<double> &operator[] (unsigned int index);
		

       /*************************************************************************
   		* Sobrecarga do operador - da classe Matrix.
   		*
   		* Multiplica todas as entradas da matriz à esquerda por -1 e retorna o 
   		* resultado.
   		*
   		* @return Matriz com sinais invertidos.
   		* @overload
   		*************************************************************************/
		Matrix operator-();


	   /*************************************************************************
    	* Transpõe uma matriz.
    	*
    	* Encontra a matriz transposta e retorna o resultado.
    	*
    	* @return Matriz transposta.
    	* @overload
    	*************************************************************************/
		Matrix transpose();

	   /*************************************************************************
    	* Pega o "valor absoluto" de uma matriz.
    	*
    	* Faz com que todas as entradas da matriz se tornem positivas e retorna a
    	* matriz resultante.
    	*
    	* @return Matriz em termos absolutos.
    	* @overload
    	*************************************************************************/
		Matrix Abs();


	   /*************************************************************************
    	* Getter para uma coluna.
    	*
    	* Retorna um vector contendo as entradas de uma coluna da matriz.
    	*
    	* @param col índice da coluna.
    	* @return Vector representando a coluna.
    	* @overload
    	*************************************************************************/
		std::vector<double> getCol(unsigned int col);

	   /*************************************************************************
    	* Getter para a quantidade de colunas da matriz.
    	*
    	* Retorna a quantidade de colunas da matriz.
    	*
    	* @return Número de colunas.
    	* @overload
    	*************************************************************************/
		unsigned int getColNumber() const;
		

	   /*************************************************************************
    	* Getter para a quantidade de linhas da matriz.
    	*
    	* Retorna a quantidade de linhas da matriz.
    	*
    	* @return Número de cinhas.
    	* @overload
    	*************************************************************************/
		unsigned int getRowNumber() const;
		

		/*************************************************************************
    	* Troca duas linhas.
    	*
    	* Dados dois índices representando duas linhas, troca as entradas dessas
    	* duas linhas.
		*
    	* @param l1 linha 1.
    	* @param l2 linha 2.
		*
    	* @return Void.
    	* @overload
    	*************************************************************************/
		void swapLines(double l1,double l2);
	};	
	
   /*************************************************************************
    * Declaração da classe EquationSystem.
    *
    * Representa um sistema de equações e formas de solucioná-lo.
    *************************************************************************/
	class EquationSystem {
	private:

		Matrix A;/**< Matriz dos coeficientes do sistema.*/
		Matrix B;/**< Matriz (vetor) das constantes do sistema.*/
		Matrix x;/**< Matriz (vetor) solução do sistema.*/
		
	   /*************************************************************************
    	* Resolve o sistema pelo método de Gauss-Seidel.
    	*
    	* Encontra a solução aproximada iterativamente pelo método de Gauss-Seidel
    	* assumindo uma tolerância e um número máximo de iterações.
    	*
    	* @param tol Tolerância.
    	* @param maxIter Número máximo de iterações.
		*
    	* @return Void.
    	* @overload
    	*************************************************************************/
		void gaussSeidel(double tol, unsigned int maxIter);


	   /*******************************************************************************
    	* Checa se o sistema obedece ao critério de Sassenfeld.
    	*
    	* Aplica o critério de Sassenfeld ao sistema. Retorna verdadeiro se o
    	* método de Gauss-Seidel converge para uma solução e falso caso contrário.  
    	*
    	* @return Se o sistema satisfaz o crítério de Sassenfield retorna 1, caso
		* contrário, retorna 0.
    	*
		* @overload
    	******************************************************************************/
		bool sassenfeldCriteria();		
	

	   /*************************************************************************
    	* Realiza o pivoteamento parcial do sistema.
    	*
    	* Procura o maior dentre os elementos da coluna, começando por um índice
    	* inicial. Se existir, são trocadas as linhas do índice inicial e do 
    	* índice cujo elemento é o maior. 
    	*
    	* @param startI Índice inicial.
    	* 
		* @return Void.
    	* @overload
    	*************************************************************************/
		void findPivot(unsigned int startI);	
				

	   /******************************************************************************
    	* Resolve o sistema pelo método de Gauss-Jordan.
    	*
    	* Encontra a solução exata do sistema através do método de Gauss-Jordan.
    	*
    	* @return Void.
        *
    	* @overload
    	*******************************************************************************/
		void gaussJordan();

	public:

	   /***************************************************************************
        * Construtor da classe EquationSystem.
	    * 
        * Constrói um sistema de equações baseado numa matriz de coeficientes e 
        * outra de constantes.
    	* 
    	* @param a Matriz dos coeficientes.
    	* @param b Matriz das constantes.
    	***************************************************************************/
		EquationSystem(Matrix a, Matrix b);


		/*************************************************************************
        * Getter para a solução da classe EquationSystem.
	    * 
        * Resolve o sistema representado pela classe EquationSystem e retorna 
		* uma matriz contendo a solução.
    	* 
    	* @param tol Tolerância para o erro aproximado.
    	* @param maxIter Número máximo de iterações.
    	*************************************************************************/
		Matrix getSolution(double tol, unsigned int maxIter);
	};
}

#endif
