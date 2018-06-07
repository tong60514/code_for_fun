#pragma once
#pragma once
using namespace System;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
enum PHRASE {
	Raito, PI, degree
};

#include <math.h>
namespace math_obj {
	delegate double Functional(double x);
	typedef double (*FuntionalPointer)(double x);
	typedef enum  {
		Lpar,Rpar,FUNC,VAR,EER
	}npdaState;
	typedef int npdaStackSymbol;

	ref class FunctionGenerator{
		wchar_t VarSymbol;
		String^ input_string;
		List<npdaStackSymbol> stack;
		FunctionGenerator(String^ input_string) {
			this->input_string = input_string;
		}

		
	};
	ref class MathFunction {
	protected:
		Functional^ functional;
		List<Functional^> FunctionalChain;
		double evaluate_composite_result(double x);
	public:
		MathFunction(Functional^ functional);
		double operator()(double x) {
			return this->evaluate(x);
		}
		virtual double evaluate(double x);
		MathFunction% operator<<(Functional^ functional);
		MathFunction% operator<<(MathFunction^ functional);
		static inline double ID(double x) {
			return x;
		}
		static Functional^ Identity = gcnew Functional(&ID);
		
	};

	ref class PolynomialFunction :public MathFunction {
	private:
		array<double>^ coef;
		List<PolynomialFunction^> operandlist;
	public:
		PolynomialFunction(Functional^ functional, array<double>^ coef);
		PolynomialFunction(const PolynomialFunction%);
		virtual double evaluate(double x)override;
		
		
		
		double% operator[](int x);
		static MathFunction^ Linear(double a, double b);
	};
	
	
	
	

	/*ref class PolynomialFunction : public MathFunction {
	private:
		array<double>^ coef;
	public:
		PolynomialFunction(array<double>^ coef);
		virtual double operator()(double x)override;
	};*/



	public delegate double myMath(double v);
	ref class MathCaculator {
	private:
		double arthType = 1.0;
	public:
		void setArthType(PHRASE phrase);
		long curracy = 5;
		long frac(long x);
		double exp(double x);
		double ln(double x);
		double pow(double b, double p);
		double sin(double x);
		double cos(double x);
		double normalize(double x);
		double actan(double x);
		double sinc(double x);
		double intPow(double x,int p);
	};
	typedef double(*math_func)(double x);
#define r_arr 0
#define exception -1
#define arr_val 1
#define symbol_check 2
#define l_arr 3

	ref class MyVector {
	private:
		array<double>^ list;
	public:
		MyVector(array<String^>^ arr, int start);
		void add(MyVector^ vec);
		void out();
		int len();
		double dot(MyVector^ vec);
	};




	class Caculator {
	private:
		double* data;
		int length;
	public:
		Caculator();
		void expand(math_obj::MathCaculator^ math_caculator, myMath^ func, int iter, double x);
		void show();
		void show(TextBox^ txtbx);
		String^ getRes();
		~Caculator();
	};
};
