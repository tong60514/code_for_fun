#include "Mathobj.h"
math_obj::MyVector::MyVector(array<String^>^ arr, int start) {
	int state = symbol_check;
	int ptr = start;

	ArrayList^ arrlist;
	arrlist = gcnew ArrayList;
	try {

	transistion:
		switch (state) {
		case exception:
			throw gcnew FormatException;
		case r_arr:
			state = arr_val;
			goto transistion;
		case arr_val:
			goto read_arr_val;
		case symbol_check:
			goto array_symbol_check;
		case l_arr:
			//ptr = 0;
			goto vector_construct;
		}



	array_symbol_check:
		{
			if (arr[ptr]->Equals("["))
				state = r_arr;
			if (arr[ptr]->Equals("]"))
				state = l_arr;
			ptr++;
			goto transistion;
		}

	read_arr_val:
		{
			if (arr[ptr]->Equals("]")) {
				state = symbol_check;
			}
			else {
				try {
					arrlist->Add(Convert::ToDouble(arr[ptr]));
					ptr++;
				}
				catch (FormatException^ ex) {
					state = exception;
				}
			}
			goto transistion;
		}
	vector_construct:
		{
			list = gcnew array<double>(arrlist->Count);
			for (int i = 0; i < arrlist->Count; i++) {
				list[i] = ((double)arrlist[i]);
			}
		}
	}
	catch (FormatException^ ex) {
		throw;
	}


}



void math_obj::MyVector::add(MyVector^ vec) {
	for (int i = 0; i < this->list->GetLength(0); i++) {
		this->list[i] += (double)vec->list[i];
	}
}
void math_obj::MyVector::out() {
	Console::Write(" [ ");
	Console::Write(this->list[0]);
	for (int i = 1; i < this->list->GetLength(0); i++) {
		Console::Write(" , " + this->list[i]);
	}
	Console::WriteLine(" ] ");
}
int math_obj::MyVector::len() {
	return this->list->GetLength(0);
}

double math_obj::MyVector::dot(MyVector^ vec) {
	double res = 0.0;
	for (int i = 0; i < this->list->GetLength(0); i++) {
		res += this->list[i] * (double)vec->list[i];
	}
	return res;
}
math_obj::Caculator::Caculator(){
	this->data = 0;
	this->length = 0;
	
}
void  math_obj::Caculator::expand(math_obj::MathCaculator^ math_caculator,myMath^ func, int iter, double x) {
	if (this->length != -1) {
		delete[] data;
	}
	this->data = new double[iter];
	this->length = iter;
	for (int i = 0; i<iter; i++) {
		math_caculator->curracy = i + 1;
		this->data[i] = func(x);
		
	}
}

void  math_obj::Caculator::show() {
	if (this->length > 0) {
		for (int i = 0; i < this->length; i++) {
			Console::WriteLine(" " + i + " th iteration :" + this->data[i]);
		}
	}
	else return;
}
void  math_obj::Caculator::show(TextBox^ txtbx) {
	if (this->length > 0) {
		for (int i = 0; i < this->length; i++) {
			txtbx->AppendText(" " + i + " th iteration :" + this->data[i]);
		}
	}
	else return;
}

String^  math_obj::Caculator::getRes() {
	String^ res = gcnew String("");
	if (this->length > 0) {
		for (int i = 0; i < this->length; i++) {
			res += (" " + i + " th iteration :" + this->data[i] + "\r\n\r");
		}
	}
	return res;

}
math_obj::Caculator::~Caculator() {
	if (this->length > 0)
		delete[] this->data;
}