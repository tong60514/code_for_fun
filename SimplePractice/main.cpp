#include <iostream>

#include "GuiForm.h"
#include "FormLayout.h"
#include "plot.h"
#include "LabelTable.h"
#include "FunctionForm.h"
using namespace System;
using namespace FormLayout;
#include "math.h"







ref class TestForm: public LayoutForm {
public:
	TestForm():LayoutForm(1920,1080) {
		InitComponent();
	}
private:
	
	ToolStripMenuItem^ fileToolStripMenuItem1; 
	ToolStripMenuItem^ mathToolStripMenuItem1; 
	ToolStripMenuItem^ graphToolStripMenuItem1;
	ToolStripMenuItem^ helpToolStripMenuItem1; 
	ToolStripMenuItem^ textToolStripMenuItem1;
	ToolStripMenuItem^ ellipseToolStripMenuItem1; 
	ToolStripMenuItem^ clearToolStripMenuItem1;
	ScrollBar^ scroll_X;
	ScrollBar^ scroll_Y;

	GroupBox^ group_box;

	RadioButton^ line;
	RadioButton^ ellipse;
	RadioButton^ rectangle;
	RadioButton^ dot;
	

	

	void InitComponent() {

		


		this->Text = "Gui Course Program";
		group_box = gcnew GroupBox;
		group_box->Location= System::Drawing::Point(800,500);
		group_box->AutoSize = false;
		group_box->Text = "mode";
		group_box->Size = System::Drawing::Size(200, 130);

		
		

		
		group_box->Controls->Add(line);
		group_box->Controls->Add(ellipse);
		group_box->Controls->Add(rectangle);
		group_box->Controls->Add(dot);
		this->Controls->Add(group_box);
		group_box->Visible = false;
		

		
		
		
		//this->Controls->Add(config);
		//fileToolStripMenuItem1 = gcnew ToolStripMenuItem;
		//pmathToolStripMenuItem1 = gcnew ToolStripMenuItem;
		graphToolStripMenuItem1 = gcnew ToolStripMenuItem;

		textToolStripMenuItem1 = gcnew ToolStripMenuItem;
		

		ellipseToolStripMenuItem1 = gcnew ToolStripMenuItem;
		clearToolStripMenuItem1 = gcnew ToolStripMenuItem;
		
		textToolStripMenuItem1->Text = "text";
		ellipseToolStripMenuItem1->Text = "open";
		ellipseToolStripMenuItem1->Click += gcnew EventHandler(this,&TestForm::eclipse_item_click_handler);
		clearToolStripMenuItem1->Text = "clear";
		clearToolStripMenuItem1->Click += gcnew EventHandler(this, &TestForm::clear_item_click_handler);
		graphToolStripMenuItem1->DropDownItems->AddRange(gcnew array<ToolStripMenuItem^>{
			textToolStripMenuItem1, ellipseToolStripMenuItem1, clearToolStripMenuItem1
		});

		//helpToolStripMenuItem1 = gcnew ToolStripMenuItem;
		
		addMenuItem("plot function",gcnew EventHandler(this,&TestForm::file_item_click_handler));
		addMenuItem("math", gcnew EventHandler(this, &TestForm::math_item_click_handler));
		addMenuItem("graph",graphToolStripMenuItem1);
		addMenuItem("help", gcnew EventHandler(this, &TestForm::file_item_click_handler));
		
	}
	
	void file_item_click_handler(Object^ obj,EventArgs^ evt) {
		
		
	}
	static float linear(float x) {
		return 2.0*x;
	}
	array<double>^ createXs(double interval) {
		int I = int((double)140/ interval);
		array<double>^ a = gcnew array<double>(I);
		for (int i = 0; i < I; i++) {
			a[i] = -70+i*interval;
		}
		return a;
	}
	void math_item_click_handler(Object^ obj, EventArgs^ evt) {
		(gcnew myForm)->ShowDialog();
	}
	void graph_item_click_handler(Object^ obj, EventArgs^ evt) {
		
	}
	void line_item_click_handler(Object^ obj, EventArgs^ evt) {
		
	}
	void help_item_click_handler(Object^ obj, EventArgs^ evt) {
		
	}
	void eclipse_item_click_handler(Object^ obj, EventArgs^ evt) {
		
	}
	void clear_item_click_handler(Object^ obj, EventArgs^ evt) {
		
	}
	
	
	
};
static double Id(double x) {
	return x;
}

static double tj(double x) {
	return 8 * x + 9;
}
int main() {
	Functional^ f = gcnew Functional(&Id);
	
	//Functional^ tt = gcnew Functional(f, &PolynomialFunction::evaluate);
	MathFunction^ math = gcnew MathFunction(gcnew Functional(&Id));
	math << PolynomialFunction::Linear(8.0, 9.6);
	PolynomialFunction^ p = gcnew PolynomialFunction(f, gcnew array<double>{
		2.0,3.6,52.0,50
	});
	PolynomialFunction^ p2 = gcnew PolynomialFunction(f, gcnew array<double>{
		2.0, 3.6, 52.0, 50
	});
	PolynomialFunction q = *p;
	p << math<<math;
	Console::WriteLine(math(1));
	p[0] = 8.5;
	Console::WriteLine(q(1));
	Application::Run(gcnew SimplePractice::FunctionForm);
	return 0;
}