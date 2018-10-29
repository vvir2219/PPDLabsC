#include <thread>

#include "Matrix.h"

#ifndef __RUNNER_INCLUDED__
#define __RUNNER_INCLUDED__

template <typename T>
class Runner{
	public:
	
	static void execFunc(T *v1, T *v2, T *rez, T (*func)(const T&, const T&), int start, int stop){
		for(; start < stop; ++start){
			rez[start] = func(v1[start], v2[start]);
		}
	}

	Matrix<T> * run(const Matrix<T>& m1, const Matrix<T>& m2, T (*func)(const T&, const T&), int noThreads){
		std::thread threads[noThreads];

		Matrix<T> *rez = new Matrix<T>(m1.lines, m2.columns);
		int n = m1.lines * m1.columns;
		int size = n / noThreads;
		int remainder = n % noThreads;
		int i, start = 0, stop = size;
		for(i = 0; i < noThreads; ++i){
			if (remainder > 0){
				stop++;
				remainder--;
			}
			threads[i] = std::thread(execFunc, m1.getElemens(), m2.getElemens(), rez->getElemens(), func, start, stop);
			start = stop;
			stop += size;
		}

		for(i = 0; i < noThreads; ++i)
			threads[i].join();

		return rez;
	}
};

#endif
