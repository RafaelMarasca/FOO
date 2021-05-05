/********************************************************************************************
 * @file Numeric.cpp
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 19 04 2021
 * @brief Declaração da classe Numeric.
 * 
 * Este arquivo contém as delcarações dos métodos e membros da classe Numeric.
 * 
 * A classe Numeric fornece as clsses e métodos para se criar e resolver sistemas de 
 * equações.
 *  
 ********************************************************************************************/

#include "Numeric.h"

#include <algorithm>
#include <cmath>
#include <string>

namespace NM{

	Matrix::Matrix(unsigned int r) {
		rowNumber = r;
		colNumber = 1;
		realMatrix = std::vector<std::vector<double>>(r, std::vector<double>(1, 0));
	}
	//  Constrói uma matriz de tamanho R e C e preenche com zeros.
	//TODO: fill?
	Matrix::Matrix(unsigned int r, unsigned int c) {
		std::vector<std::vector<double>> aux(r, std::vector<double>(c, 0));
		rowNumber = r;
		colNumber = c;
		realMatrix = aux;
	}
	//  Multiplica duas matrizes da forma naive
	Matrix Matrix::operator* (Matrix &m1) {
		if(this->getColNumber() != m1.getRowNumber())
			throw std::string("Matrizes incompativeis.");

		//  Helper pra não ESTRAGAR TUDO igual um IMBECIL
		Matrix helper = (*this);
		
		//  A matriz resultante tem o número de linhas da matriz do LHS
		//e o número de colunas da matriz do RHS.
		Matrix result(helper.getRowNumber(), m1.getColNumber());
		
		//  Dois laços pra pegar o R(i, j)
		for(unsigned int i = 0; i < result.getRowNumber(); i++) {
			for(unsigned int j = 0; j < result.getColNumber(); j++) {
				//  Laço pra somar as multiplicações de col x linha.
				for(unsigned int k = 0; k < helper.getColNumber(); k++) {
					result[i][j] += helper[i][k]*m1[k][j];
				}
			}
		}	
		return result;
	}
	//  Syntatic sugar.
	void Matrix::operator*= (Matrix &m1) {(*this) = (*this) * m1;}

	//  Soma os elementos de duas matrizes (M[i][j]+N[i][j] e retorna a matriz resultante.
	Matrix Matrix::operator+ (Matrix &m1) {
		if(this->getRowNumber() != m1.getRowNumber() or this->getColNumber() != m1.getColNumber())
			throw std::string("Matrizes incompativeis.");

		Matrix helper = (*this);

		for(unsigned int i = 0; i < helper.getRowNumber(); i++)
			for(unsigned int j = 0; j < helper.getColNumber(); j++)
				helper[i][j] += m1[i][j];

		return helper;
	}
	//  Syntatic sugar.
	void Matrix::operator+= (Matrix &m1) { (*this) = (*this) + m1; }

	//  Mesma coisa que a soma só que com subtração.
	Matrix Matrix::operator- (Matrix &m1) {
		if(this->getRowNumber() != m1.getRowNumber() or this->getColNumber() != m1.getColNumber())
			throw std::string("Matrizes incompativeis.");

		Matrix helper = (*this);

		for(unsigned int i = 0; i < helper.getRowNumber(); i++)
			for(unsigned int j = 0; j < helper.getColNumber(); j++)
				helper[i][j] -= m1[i][j];

		return helper;
	}
	//  Syntatic sugar.
	void Matrix::operator-= (Matrix &m1) { (*this) = (*this) - m1; }

	//  Copia os membros da matriz do RHS pra matriz do LHS.
	void Matrix::operator= (const Matrix &m1) { 
		this->realMatrix = m1.realMatrix; 
		this->rowNumber = m1.rowNumber;
		this->colNumber = m1.colNumber;
	}

	//  Retorna uma REFERÊNCIA ao vector<double> na posição [i], que pode ser
	//acessado novamente com um [] (simulando uma matriz) e pode ser modificado.
	std::vector<double> &Matrix::operator[] (unsigned int index) {
		if(index >= rowNumber)
			throw "Acesso invalido";

		return realMatrix[index]; 
	}

	Matrix Matrix::operator-() {
		Matrix temp(this->getRowNumber(), this->getColNumber());
		for(unsigned int i = 0; i < getRowNumber(); i++){
			for(unsigned int j = 0; j < getColNumber(); j++)
				temp[i][j]= - realMatrix[i][j];
		}
		return temp;
	}

	Matrix Matrix::transpose() {
		Matrix temp(this->colNumber, this->rowNumber);

		for(unsigned int i = 0; i < (this->rowNumber); i++){
			for(unsigned int j = 0; j < (this->colNumber); j++)
				temp[j][i] = this->realMatrix[i][j];
		}
		return temp;
	}

	Matrix Matrix::Abs(){
		Matrix temp(this->rowNumber, this->colNumber);

		for(unsigned int i = 0; i < getRowNumber(); i++){
			for(unsigned int j = 0; j < getColNumber(); j++)
				if(realMatrix[i][j] < 0)
                    temp[i][j] = -realMatrix[i][j];
		}
		return temp;
	}

	std::vector<double> Matrix::getCol(unsigned int col) {
		if(colNumber <= col)
			throw "Acesso invalido";

		std::vector<double> temp;

		for(unsigned int i = 0; i < getRowNumber(); i++)
			temp.push_back(realMatrix[i][col]);

		return temp;
	}
	//  Getters dos membros de linha e coluna.
	unsigned int Matrix::getColNumber() const { return colNumber; }
	unsigned int Matrix::getRowNumber() const { return rowNumber; }

	void Matrix::swapLines(double l1, double l2) {		
		if(this->getRowNumber() <= l1 or this->getRowNumber() <= l2)
			throw "Acesso invalido.";
		
		std::vector<double> aux = (*this)[l1];
		(*this)[l1] =  (*this)[l2];
		(*this)[l2] = aux;
	}

   
	//  Construtor inicializa A e B com a e b, respectivamente. Além de fazer o vetor x receber o vetor
	//nulo como chute inicial (acho que é uma escolha sensata).
	EquationSystem::EquationSystem(Matrix a, Matrix b) : A(a), B(b), x(Matrix(b.getRowNumber())){
		if(a.getRowNumber() != b.getRowNumber() or b.getColNumber() != 1)
			throw "Matrizes incompatíveis";
	}
	//  Escolhi fazer o x_kMaisUm ser o próprio vetor x da classe p/ evitar ficar retornando coisa 
	void EquationSystem::gaussSeidel(double tol, unsigned int maxIter) {
		//  Cria um vetor para representar o x_k
		Matrix x_k = x;	
		
		//  Laço que roda quantas vezes o usuário quer (não sei como calcular a tolerância)
		for(unsigned int k = 0; k < maxIter; k++) {
			for(unsigned int i = 0; i < x.getRowNumber(); i++) {	
				//  Variaveis para o somatorio.
				double s1 = 0, s2 = 0;
				//  Somatorio de a(i, j) * x_kMaisUm(j) de j=0 a i-1
				for(unsigned int j = 0; j < i; j++) {
					s1 += A[i][j] * x[j][0];
				}
				//  Somatório de a(i, j) * x_k(j) de j=i+1 a n-1
				for(unsigned int j = i+1; j < x.getRowNumber(); j++) {
					s2 += A[i][j] * x_k[j][0];
				}
				//  Atualiza o x_k+1 na posição i pela formula xi = 1/aii(bi-soma1-soma2)
				x[i][0] = (B[i][0] - s1 - s2) / A[i][i];
			}	
			//  Criterio de parada. Se o maior elemento do módulo das diferenças entre x_k e
			//x_k+1 for menor que a tolerância, o algoritmo para.
			Matrix tolAux = x_k - x;
			double biggest = fabs(tolAux[0][0]);
			for(unsigned int i = 0; i < tolAux.getRowNumber(); i++) 
				if(fabs(tolAux[i][0]) > biggest)
					biggest = fabs(tolAux[i][0]);
			if (biggest < tol)
				break;
			
			//  Atualiza o x_k pro antigo x_k+1
			x_k = x; 
		}
	}
	//  Critério de convergência para o método de Gauß-Seidel.
	bool EquationSystem::sassenfeldCriteria() {
		//  Primeiro, é criado um vetor de N casas.
		std::vector<double> beta_i(A.getRowNumber(), 0);
		
		//  A primeira casa é inicializada separadamente para garantir o funcionamento do laço.
		for(unsigned int j = 1; j < A.getColNumber(); j++)
			beta_i[0] += fabs(A[0][j]); 
		beta_i[0] /= fabs(A[0][0]);

		//  Só copiei a fórmula do livro.
		for(unsigned int i = 1; i < A.getRowNumber(); i++) {
			for(unsigned int j = 0; j < i - 1; j++)
				beta_i[i] += beta_i[j]*fabs(A[i][j]);
			for(unsigned int j = i + 1; j < A.getColNumber(); j++)
				beta_i[i] += fabs(A[i][j]);
			beta_i[i] /= A[i][i]; 
		}
		
		//  O critério de Sassenfeld diz que o sistema converge se o maior elemento do vetor 
		//beta for menor que 1. A função retorna se o critério é satisfeito.
		return ( *max_element(beta_i.begin(), beta_i.end()) < 1 )? 1 : 0;
	}
	//  Função para trocar de lugar uma linha tosca com uma linha que vai dar bom.
	void EquationSystem::findPivot (unsigned int startI) {	
		//  Começa pelo começo.
		unsigned int index = startI;	
		
		//  Busca linear p/ achar o maior elemento.
		double biggest = A[startI][startI];
		for(unsigned int i = startI; i < A.getRowNumber(); i++) {	
			if(fabs(A[i][startI]) > fabs(biggest)) {
				biggest = A[i][startI];
				index = i;
			}
		}
		//  Troca as linhas do maior elemento com o atual.
		A.swapLines(startI, index);	
		B.swapLines(startI, index);
	}

	void EquationSystem::gaussJordan() {
		//  Matrizes auxiliares para não alterar as matrizes do sistema.
		Matrix a = A;
		Matrix b = B;
	
		for(unsigned int i = 0; i < a.getRowNumber() and i < a.getColNumber(); i++) {
			//  Coloca na diagonal principal o maior elemento da coluna.
			this->findPivot(i);
			
			//  Escolhe o elemento da diagonal principal como pivô.
			double div = a[i][i];
			//  TODO: tratar elemento da diagonal nulo. Pré-processamento?
			if(div == 0)
				continue;

			//  Pivoteia a linha do pivô (L_i <- 1/pivô * L_i).
			for(unsigned int j = i; j < a.getColNumber(); j++) { a[i][j] /= div; }
			//  Faz a mesma operação no vetor B, como na matriz expandida.
			b[i][0] /= div;		
			
			//  Zera os elementos acima e abaixo do pivô.
			for(unsigned int k = 0; k < a.getRowNumber(); k++) {
				if(i == k)
					continue;

				double mult = a[k][i];
				//  Realiza as operações na linha. L_k <- -mult*L_i.
				//Isso zera os elementos na coluna do pivô.
				for(unsigned int l = i; l < a.getColNumber(); l++) {
					a[k][l] -= mult * a[i][l];
				}
				//  Novamente, a operação é realizada no vetor B, como
				//na matriz expandida.
				b[k][0] -= mult * b[i][0];  	
			}
		}
		//  Passa o vetor b da matriz expandida (resultado) para o vetor x.
		x = b;
	}
	//  Função que resolve o sistema linear.
	Matrix EquationSystem::getSolution( double tol,  unsigned int maxIter){
		//  Se o método de Gauß-Seidel converge para o sistema, ele é chamado.
		if(sassenfeldCriteria() and A.getRowNumber() == A.getColNumber())
			gaussSeidel(tol, maxIter);
		//  Senão, é chamado um método direto.
		else
			gaussJordan();
		
		return x;
	}
}

