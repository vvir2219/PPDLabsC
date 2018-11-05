#include <iostream>

#ifndef COMPLEX_H_P69S0SNW
#define COMPLEX_H_P69S0SNW

class Complex
{
public:
	Complex() { }
	Complex (double a, double b);
	~Complex () {}

	inline double real() { return a; }
	inline double imag() { return b; }

	Complex inverse();
	Complex operator + (const Complex& ot);
	Complex operator - (const Complex& ot);
	Complex operator * (const Complex& ot);

	friend std::ostream& operator << (std::ostream& os, const Complex& c) {
		os << c.a << " " << c.b;
		return os;
	}

	friend std::istream& operator >> (std::istream& is, Complex& c) {
		is >> c.a >> c.b;
		return is;
	}
private:
	double a, b;
};

#endif /* end of include guard: COMPLEX_H_P69S0SNW */
