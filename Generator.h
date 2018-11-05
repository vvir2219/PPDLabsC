#include <random>

#include "Complex.h"

#ifndef GENERATOR_H_8SPAVDKT
#define GENERATOR_H_8SPAVDKT

Matrix<double> generateDoubleMatrix(int lines, int columns) {
	std::mt19937 mt_rand(time(0));

	Matrix<double> matrix(lines, columns);
	for (int i = 0; i < lines; ++i)
		for (int j = 0; j < columns; ++j)
			matrix.set(i, j, mt_rand());
	return matrix;
}

Matrix<Complex> generateComplexMatrix(int lines, int columns) {
	std::mt19937 mt_rand(time(0));

	Matrix<Complex> matrix(lines, columns);
	for (int i = 0; i < lines; ++i)
		for (int j = 0; j < columns; ++j)
			matrix.set(i, j, Complex(mt_rand(), mt_rand()));
	return matrix;
}

#endif /* end of include guard: GENERATOR_H_8SPAVDKT */
