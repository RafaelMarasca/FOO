/********************************************************************************************
 * @file Numeric.h
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 19 04 2021
 * @brief Implementação da classe Numeric.
 * 
 * Este arquivo contém a implementação dos métodos e membros da classe Numeric.
 * 
 * A classe Numeric fornece as clsses e métodos para se criar e resolver sistemas de 
 * equações.
 *  
 ********************************************************************************************/

#ifndef	NUMERIC_H
#define NUMERIC_H

#include "Circuit.h"

#include <vector>
#include <iostream>

namespace NM {
	
	class Matrix {
	private:
		//  Vector que é syntatic-sugareado para o funcionamento da classe matrix.
		std::vector<std::vector<double>> realMatrix;
		//  Número de linhas.
		unsigned int rowNumber;
		//  Número de colunas.
		unsigned int colNumber;
	
	public:

		Matrix(unsigned int r);
	
		Matrix(unsigned int r, unsigned int c);

		//  Sobrecarga dos operadores para operações básicas & acesso "direto".
		Matrix operator* (Matrix &m1);
		void operator*= (Matrix &m1);	

		Matrix operator+ (Matrix &m1);
		void operator+= (Matrix &m1);

		Matrix operator- (Matrix &m1);
		void operator-= (Matrix &m1);

		void operator= (const Matrix &m1);
		std::vector<double> &operator[] (unsigned int index);
		
		Matrix operator-();

		Matrix transpose();

		Matrix Abs();

		std::vector<double> getCol(unsigned int col);

		//  Getters de linha/coluna.
		unsigned int getColNumber() const;
		unsigned int getRowNumber() const;

		void swapLines(double l1,double l2);
		
		//  TODO: apagar essa merda aqui.
		void print();

        void print(std::vector<CMP::Component*> C) ;
	};	

	class EquationSystem {
	private:
		//  Matriz dos coeficientes
		Matrix A;
		//  Vetor do igual(?)
		Matrix B;	
		//  Vetor solução
		Matrix x;
		//  Método que resolve o sistema utilizando o método de Gauß-Seidel.
		//TODO? implementar mais métodos?
		void gaussSeidel(double tol, unsigned int maxIter);

		//  Critério de Sassenfeld, que checa a convergência do método de Gauß-Seidel.
		bool sassenfeldCriteria();		
	
		//  Função que troca as linhas para garantir que o pivô seja o maior número e
		//que não haja divisão por zero.
		void findPivot(unsigned int startI);			
		//  Resolve o sistema por Gauß-Jordan.
		void gaussJordan();
	public:
		//  Constrói o sistema de equações lineares com base na matriz dos coef.
		//e no vetor do igual(?)
		EquationSystem(Matrix a, Matrix b);

		//  Resolve e retorna o sistema para o usuário.
		Matrix getSolution(double tol, unsigned int maxIter);

		//  Temp. Apagar após os testes.
		void printSolution();
		void print();
	};
}

#endif
