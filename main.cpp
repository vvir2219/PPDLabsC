#include <iostream>
#include <sstream>
#include <chrono>
#include <functional>
#include <fstream>
#include <stdio.h>
#include <string>

#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "Runner.h"

#include "Generator.h"

#include "Complex.h"

//#define GENERATE_TESTS
#define DEBUG

void generateDoubleMatrices(const std::string& filename, int lines, int columns) {
	std::ofstream file(filename);
	if (file.is_open()) {
		file << generateDoubleMatrix(lines, columns) << generateDoubleMatrix(lines, columns);
	}
}

void generateComplexMatrices(const std::string& filename, int lines, int columns) {
	std::ofstream file(filename);
	if (file.is_open()) {
		file << generateComplexMatrix(lines, columns) << generateComplexMatrix(lines, columns);
	}
}

template <typename ValueType>
double testMapTest(const std::string filename, const std::function<ValueType(const ValueType&, const ValueType&)> func, int noThreads) {
	std::ifstream file(filename);
	if (file.is_open()) {
		Matrix<ValueType> m1, m2;
		Runner<ValueType> runner;

		file >> m1 >> m2;
		auto begin = std::chrono::steady_clock::now();
		runner.run(m1, m2, func, noThreads);
		auto end = std::chrono::steady_clock::now();
		return std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
	}
	return 0;
}

template <typename ValueType>
double runTest(const Matrix<ValueType>& m1, const Matrix<ValueType>& m2, const std::function<ValueType(const ValueType&, const ValueType&)> func, int noThreads) {
	auto begin = std::chrono::steady_clock::now();
	Runner<ValueType>::run(m1, m2, func, noThreads);
	auto end = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
}

template <typename ValueType>
double mediumTime(const Matrix<ValueType>& m1, const Matrix<ValueType>& m2, const std::function<ValueType(const ValueType&, const ValueType&)> func, int noThreads, int noRuns) {
	double time =0;
	for (int i = 0; i < noRuns; ++i)
		time += runTest(m1, m2, func, noThreads) / noRuns;
	return time;
}

int main() {
#ifndef DEBUG

#ifdef GENERATE_TESTS
	generateDoubleMatrices("double1000x1000", 1000, 1000);
	generateComplexMatrices("complex1000x1000", 1000, 1000);
#else
	Matrix<double> mdouble1, mdouble2;
	Matrix<Complex> mcomplex1, mcomplex2;

	{
		std::ifstream ifs("double1000x1000");
		if (!ifs.is_open())
			return -1;

		ifs >> mdouble1 >> mdouble2;
	}

	{
		std::ifstream ifs("complex1000x1000");
		if (!ifs.is_open())
			return -1;

		ifs >> mcomplex1 >> mcomplex2;
	}

	auto doubleProduct = [](double x, double y) {return x*y;};
	auto complexProduct = [](Complex x, Complex y) {return x*y; };
	auto doubleSomething = [](double x, double y) {return x*y/(x+y);};
	auto complexSomething = [](Complex x, Complex y) {return x*y*((x+y).inverse()); };
	int noThreads = 1, noRuns = 5;
	for (int i = 0; i < 4; ++i, noThreads <<= 1){
		std::cout << std::fixed;
		std::cout << mediumTime<double>(mdouble1, mdouble2, doubleProduct, noThreads, noRuns)
				  << " nanoseconds; operation [Double product]; noThreads [" << noThreads <<"]; noRuns ["<<noRuns<<"]\n";

		std::cout << mediumTime<Complex>(mcomplex1, mcomplex2, complexProduct, noThreads, noRuns)
				  << " nanoseconds; operation [Complex product]; noThreads [" << noThreads <<"]; noRuns ["<<noRuns<<"]\n";

		std::cout << mediumTime<double>(mdouble1, mdouble2, doubleSomething, noThreads, noRuns)
				  << " nanoseconds; operation [Double something]; noThreads [" << noThreads <<"]; noRuns ["<<noRuns<<"]\n";

		std::cout << mediumTime<Complex>(mcomplex1, mcomplex2, complexSomething, noThreads, noRuns)
				  << " nanoseconds; operation [Complex something]; noThreads [" << noThreads <<"]; noRuns ["<<noRuns<<"]\n";

		std::cout << "\n";
	}
	
#endif

#else
	auto m1 = generateDoubleMatrix(3, 3);
	auto m2 = generateDoubleMatrix(3, 3);
	Runner<double> runner;
	auto rez = runner.run(m1, m2, [](double a, double b) { return a+b; }, 2);

	std::cout << m1 << m2 << *rez;
#endif
	return 0;
}
