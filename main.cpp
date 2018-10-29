#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "Runner.h"

int add(const int& a, const int& b){
	return a + b;
}

int main() {
	Runner<int> runner = Runner<int>();
	Matrix<int> m1 = Matrix<int>(3, 3);
	Matrix<int> m2 = Matrix<int>(3, 3);

	m1.set(0, 0, 1);
	m1.set(0, 2, 1);
	m1.set(1, 1, 1);
	m1.set(2, 0, 1);
	m1.set(2, 2, 1);

	m2.set(0, 1, 1);
	m2.set(1, 0, 1);
	m2.set(1, 2, 1);
	m2.set(2, 1, 1);

	Matrix<int> *rez = runner.run(m1, m2, add, 2);
	for(int i = 0; i < rez->lines; ++i){
		for(int j = 0; j < rez->columns; ++j)
			printf("%d ", rez->get(i, j));
		printf("\n");
	}

	return 0;
}
