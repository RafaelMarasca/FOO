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

	Matrix::Matrix(unsigned int r, unsigned int c) {
		std::vector<std::vector<double>> aux(r, std::vector<double>(c, 0));
		rowNumber = r;
		colNumber = c;
		realMatrix = aux;
	}

	Matrix Matrix::operator* (Matrix &m1) {
		if(this->getColNumber() != m1.getRowNumber())
			throw std::string("Matrizes incompativeis.");

		Matrix helper = (*this);
		
        Matrix result(helper.getRowNumber(), m1.getColNumber());
		
		for(unsigned int i = 0; i < result.getRowNumber(); i++) {
			for(unsigned int j = 0; j < result.getColNumber(); j++) {
				for(unsigned int k = 0; k < helper.getColNumber(); k++) {
					result[i][j] += helper[i][k]*m1[k][j];
				}
			}
		}	
		return result;
	}

	void Matrix::operator*= (Matrix &m1) {(*this) = (*this) * m1;}

	Matrix Matrix::operator+ (Matrix &m1) {
		if(this->getRowNumber() != m1.getRowNumber() or this->getColNumber() != m1.getColNumber())
			throw std::string("Matrizes incompativeis.");

		Matrix helper = (*this);

		for(unsigned int i = 0; i < helper.getRowNumber(); i++)
			for(unsigned int j = 0; j < helper.getColNumber(); j++)
				helper[i][j] += m1[i][j];

		return helper;
    }

	void Matrix::operator+= (Matrix &m1) { (*this) = (*this) + m1; }

	Matrix Matrix::operator- (Matrix &m1) {
		if(this->getRowNumber() != m1.getRowNumber() or this->getColNumber() != m1.getColNumber())
			throw std::string("Matrizes incompativeis.");

		Matrix helper = (*this);

		for(unsigned int i = 0; i < helper.getRowNumber(); i++)
			for(unsigned int j = 0; j < helper.getColNumber(); j++)
				helper[i][j] -= m1[i][j];

		return helper;
	}

	void Matrix::operator-= (Matrix &m1) { (*this) = (*this) - m1; }


	void Matrix::operator= (const Matrix &m1) { 
		this->realMatrix = m1.realMatrix; 
		this->rowNumber = m1.rowNumber;
		this->colNumber = m1.colNumber;
    }

	std::vector<double> &Matrix::operator[] (unsigned int index) {
		if(index >= rowNumber)
            throw std::string("Acesso invalido");

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
            throw std::string("Acesso invalido");

		std::vector<double> temp;

		for(unsigned int i = 0; i < getRowNumber(); i++)
			temp.push_back(realMatrix[i][col]);

		return temp;
	}

	unsigned int Matrix::getColNumber() const { return colNumber; }
	unsigned int Matrix::getRowNumber() const { return rowNumber; }

	void Matrix::swapLines(double l1, double l2) {		
		if(this->getRowNumber() <= l1 or this->getRowNumber() <= l2)
            throw std::string("Acesso invalido.");
		
		std::vector<double> aux = (*this)[l1];
		(*this)[l1] =  (*this)[l2];
		(*this)[l2] = aux;
	}

	EquationSystem::EquationSystem(Matrix a, Matrix b) : A(a), B(b), x(Matrix(b.getRowNumber())){
		if(a.getRowNumber() != b.getRowNumber() or b.getColNumber() != 1)
            throw std::string("Matrizes incompatíveis");
	}

	void EquationSystem::gaussSeidel(double tol, unsigned int maxIter) {
		Matrix x_k = x;	
		
		for(unsigned int k = 0; k < maxIter; k++) {
			for(unsigned int i = 0; i < x.getRowNumber(); i++) {	
				double s1 = 0, s2 = 0;
				for(unsigned int j = 0; j < i; j++) {
					s1 += A[i][j] * x[j][0];
				}
				for(unsigned int j = i+1; j < x.getRowNumber(); j++) {
					s2 += A[i][j] * x_k[j][0];
				}
				x[i][0] = (B[i][0] - s1 - s2) / A[i][i];
			}	
			Matrix tolAux = x_k - x;
			double biggest = fabs(tolAux[0][0]);
			for(unsigned int i = 0; i < tolAux.getRowNumber(); i++) 
				if(fabs(tolAux[i][0]) > biggest)
					biggest = fabs(tolAux[i][0]);
			if (biggest < tol)
				break;
			x_k = x; 
		}
	}
	bool EquationSystem::sassenfeldCriteria() {
        std::vector<double> beta_i(A.getRowNumber(), 0);
		
		for(unsigned int j = 1; j < A.getColNumber(); j++)
			beta_i[0] += fabs(A[0][j]); 
		beta_i[0] /= fabs(A[0][0]);

		for(unsigned int i = 1; i < A.getRowNumber(); i++) {
			for(unsigned int j = 0; j < i - 1; j++)
				beta_i[i] += beta_i[j]*fabs(A[i][j]);
			for(unsigned int j = i + 1; j < A.getColNumber(); j++)
				beta_i[i] += fabs(A[i][j]);
			beta_i[i] /= A[i][i]; 
		}
		
		return ( *max_element(beta_i.begin(), beta_i.end()) < 1 )? 1 : 0;
    }

	void EquationSystem::findPivot (unsigned int startI) {	
		unsigned int index = startI;	
		
		double biggest = A[startI][startI];
		for(unsigned int i = startI; i < A.getRowNumber(); i++) {	
			if(fabs(A[i][startI]) > fabs(biggest)) {
				biggest = A[i][startI];
				index = i;
			}
        }
		A.swapLines(startI, index);	
		B.swapLines(startI, index);
	}

	void EquationSystem::gaussJordan() {
		Matrix a = A;
		Matrix b = B;
	
		for(unsigned int i = 0; i < a.getRowNumber() and i < a.getColNumber(); i++) {
			this->findPivot(i);
			
			double div = a[i][i];
			if(div == 0)
				continue;

			for(unsigned int j = i; j < a.getColNumber(); j++) { a[i][j] /= div; }

            b[i][0] /= div;
			
			for(unsigned int k = 0; k < a.getRowNumber(); k++) {
				if(i == k)
					continue;

				double mult = a[k][i];
				for(unsigned int l = i; l < a.getColNumber(); l++) {
					a[k][l] -= mult * a[i][l];
				}

				b[k][0] -= mult * b[i][0];  	
			}
		}
		x = b;
	}
	Matrix EquationSystem::getSolution( double tol,  unsigned int maxIter){
		if(sassenfeldCriteria() and A.getRowNumber() == A.getColNumber())
			gaussSeidel(tol, maxIter);
		else
			gaussJordan();
		
		return x;
	}
}

