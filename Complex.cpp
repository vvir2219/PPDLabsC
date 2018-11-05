#include "Complex.h"


Complex::Complex (double a, double b) {
	this->a = a;
	this->b = b;
}

Complex Complex::inverse() {
	return Complex(a/(a*a + b*b), -b/(a*a+b*b));
}

Complex Complex::operator + (const Complex& ot) {
	return Complex(a + ot.a, b + ot.b);
}
Complex Complex::operator - (const Complex& ot) {
	return Complex(a - ot.a, b - ot.b);
}
Complex Complex::operator * (const Complex& ot) {
	return Complex(a*ot.a - b*ot.b, a*ot.b + b*ot.a);
}


