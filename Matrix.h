#include <stdlib.h>
#include <string.h>

#ifndef __MATRIX_INCLUDED__
#define __MATRIX_INCLUDED__

template <typename T>
class Matrix{
	private:

	T *elements;

	public:

	int lines, columns;


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
		this->elements = (T*)malloc(this->lines*this->columns*sizeof(T));
		memcpy(this->elements, matrix.elements, this->lines*this->columns*sizeof(T));
	}

	T *getElemens() const { return elements;}

	T get(int line, int col){
		if (line < 0 || line >= lines)
			throw "Line is not within matrix bounds";
		if (col < 0 || col >= columns)
			throw "Column is not within matrix bounds";
		return elements[line*columns + col];
	}

	void set(int line, int col, T el){
		if (line < 0 || line >= lines)
			throw "Line is not within matrix bounds";
		if (col < 0 || col >= columns)
			throw "Column is not within matrix bounds";
		elements[line*columns + col] = el;
	}
};

#endif
