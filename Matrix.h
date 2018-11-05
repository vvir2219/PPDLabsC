#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#ifndef __MATRIX_INCLUDED__
#define __MATRIX_INCLUDED__

template <typename T>
class Matrix{
	private:

	T* elements;

	public:

	int lines, columns;

	Matrix() {}


	Matrix(int lines, int columns){
		this->lines = lines;
		this->columns = columns;
		this->elements = (T*)malloc(lines*columns*sizeof(T));
		memset(this->elements, 0, lines*columns*sizeof(T));
	}

	~Matrix(){
		free(elements);
	}

	Matrix(const Matrix& matrix){
		this->lines = matrix.lines;
		this->columns = matrix.columns;
		this->elements = matrix.elements;
	}

	T* getElemens() const { return elements; }

	T get(int line, int col){
		if (line < 0 || line >= lines)
			throw "Line is not within matrix bounds";
		if (col < 0 || col >= columns)
			throw "Column is not within matrix bounds";
		return elements[line*columns + col];
	}

	void set(int line, int col, const T& el) {
		if (line < 0 || line >= lines)
			throw "Line is not within matrix bounds";
		if (col < 0 || col >= columns)
			throw "Column is not within matrix bounds";
		elements[line*columns + col] = el;
	}

	void set(int pos, const T& el) {
		if (pos < 0 || pos >= lines*columns)
			throw "Position is not within matrix bounds";
		elements[pos] = el;
	}

	friend std::ostream& operator << (std::ostream& os, const Matrix<T>& mat) {
		os << mat.lines << " " << mat.columns << "\n";
		for(int i = 0; i < mat.lines*mat.columns; ++i) {
			os << mat.elements[i] << " ";
		}
		os << "\n";
		return os;
	}

	friend std::istream& operator >> (std::istream& is, Matrix<T>& mat) {
		is >> mat.lines >> mat.columns;
		mat.elements = (T*)malloc(mat.lines*mat.columns*sizeof(T));
		memset(mat.elements, 0, mat.lines*mat.columns*sizeof(T));
		for(int i = 0; i < (mat.lines*mat.columns); ++i){
			is >> mat.elements[i];
		}
		return is;
	}
};

#endif
