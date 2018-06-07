#include "Mathobj.h"
#include <math.h>
using namespace math_obj;
long MathCaculator::frac(long x) {
	long res = 1;
	for (long i = 1; i < x + 1; i++)
		res *= i;
	return res;
}
void MathCaculator::setArthType(PHRASE phrase) {
	switch (phrase) {
	case Raito:
		this->arthType = 2.0*3.1415926;
		break;
	case degree:
		this->arthType = (1.0 / 180.0)*3.1415926;
		break;
	case PI:
		this->arthType = 1.0;
		break;
	default:
		Console::WriteLine("undefine arthemetic type");
		throw exception;
	}
}
double MathCaculator::exp(double x) {
	double res = 1.0;
	double xx = x;
	for (int i = 1; i < curracy; i++) {
		res += (xx / (double)frac(i));
		xx *= x;
	}
	return res;
}

double MathCaculator::ln(double x) {
	double a = x;
	for (int i = 0; i < 50; i++) {
		x = x - 1.0 + (a / exp(x));
	}
	return x;
}

double MathCaculator::pow(double b, double p) {
	return exp(p*ln(b));
}
double MathCaculator::sin(double arg) {


	double x = arg;
	x = normalize(x);
	Console::WriteLine(x);
	double res = x;
	double xx = x*x;
	x *= xx;
	for (int i = 1; i < curracy; i++) {
		if (i % 2) {
			res -= (x / ((double)frac( (i * 2) + 1)) );
		}
		else {
			res += (x / ((double)frac((i * 2) + 1))  );
		}
		x *= xx;
	}
	return res;
}

double MathCaculator::cos(double x) {
	x = normalize(x);
	double res = 0.0;
	for (int i = 0; i < curracy; i++) {
		res += intPow(x, 2 * i)*intPow(-1, 2 * i) / (double)frac(2*i);
	}
	return res;
}

double MathCaculator::normalize(double x) {
	Console::WriteLine("Type:" + arthType);
	return x *= arthType;
}
double MathCaculator::actan(double x) {

	x = normalize(x);
	double res = x;
	double xx = x*x;
	x *= xx;
	for (int i = 1; i < curracy; i++) {
		if (i % 2) {
			res -= (x / (double)((i * 2) + 1));
		}
		else
			res += (x / (double)((i * 2) + 1));
		x *= xx;
	}
	return res;
}

double MathCaculator::sinc(double x) {
	double sign;
	sign = x > 0.0 ? 1.0 : -1.0;
	x = normalize(x);
	if (x >= 3.1415926) {
		sign *= -1.0;
		x -= 3.1415926;
	}
	double res = 1.0;
	double xx = x*x;
	x = xx;
	for (int i = 1; i < curracy; i++) {
		if (i % 2) {
			res -= x / (double)frac((i * 2) + 1);
		}
		else
			res += x / (double)frac((i * 2) + 1);
		x *= xx;
	}
	return sign*res;
}

double MathCaculator::intPow(double x, int p) {
	double res = 1.0;
	if (p == 0)
		goto ans;
	for (int i = 0; i < p; i++) {
		res *= x;
	}
	
ans:
	return res;
}




MathFunction::MathFunction(Functional^ functional) {
	this->functional = functional;
	
}
double MathFunction::evaluate_composite_result(double x) {
	for each(Functional^ functional in FunctionalChain) {
		x = functional(x);
	}
	return x;
}
double MathFunction::evaluate(double x) {
	return this->functional(evaluate_composite_result(x));
}
MathFunction% MathFunction::operator<<(Functional^ math_function) {
	this->FunctionalChain.Add(math_function);
	return *this;
}
MathFunction% MathFunction::operator<<(MathFunction^ math_function) {
	this->FunctionalChain.Add(gcnew Functional(math_function, &MathFunction::evaluate));
	return *this;
}
PolynomialFunction::PolynomialFunction(Functional^ functional, array<double>^ coef) : 
	MathFunction(functional)
{
	this->coef = coef;
}

MathFunction^ PolynomialFunction::Linear(double a, double b) {
	PolynomialFunction^ p = gcnew PolynomialFunction(MathFunction::Identity, gcnew array<double>{a,b} );
	return (MathFunction^)p;
}


double PolynomialFunction::evaluate(double x){
	double c = evaluate_composite_result(x);
	int i = this->coef->Length - 1;
	double res = 0.0;
	while (i>0) {

		res += this->coef[i];
		res *= c;
		i--;
	}
	return (res + coef[0]);
}

double% PolynomialFunction::operator[](int i) {
	return this->coef[i];
}

PolynomialFunction::PolynomialFunction(const PolynomialFunction% p) : MathFunction(p.functional){
	//Console::WriteLine("copy constructor called");
	this->coef = gcnew array<double>(p.coef->Length);
	for (int i = 0; i < p.coef->Length; i++) {
		this->coef[i] = p.coef[i];
	}
}




