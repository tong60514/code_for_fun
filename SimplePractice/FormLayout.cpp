#include "FormLayout.h"
#include <math.h>
using namespace FormLayout;

GridLayout::GridLayout(Form^ form) {
	this->form = form;
	int count = form->Controls->Count;
	this->grid = gcnew List<LayoutUnit^>;
}

void GridLayout::addControl(Control^ ctrl) {
	this->form->Controls->Add(ctrl);
	//ctrl->AutoSize = false;
	this->grid->Add(gcnew LayoutUnit(ctrl));
}

void GridLayout::buildLayout() {

	int marginWidth = 40;
	int LayoutMarginW = form->Width - marginWidth*2;
	int LayoutMarginH = form->Height - marginWidth*2;

	float SizeRatio =  (float)(LayoutMarginW) / (float)(LayoutMarginH);

	int count = this->grid->Count;
	int control_per_row = (int)sqrt(count / SizeRatio);
	int control_per_column = (count / control_per_row)+1;

	int Width = (float)(LayoutMarginW)/ (float)(control_per_row+2);
	int Height = (float)(LayoutMarginH)/(float)(control_per_column+2);
	
	int gap_width = (Width / control_per_row);
	int gap_height = gap_width*SizeRatio ;

	
	
	System::Drawing::Size size = System::Drawing::Size(Width, Height/2);
	int i = 0;




	int prev_w =0, prev_h = 0;
	for each (LayoutUnit^ unit in this->grid) {
		System::Drawing::Point p = System::Drawing::Point(
			marginWidth +(i%control_per_row)*(Width + gap_width), marginWidth +((i / control_per_row)*(Height + gap_height))
		);
		Console::WriteLine(" x : " + p.X + " y :" + p.Y);
		unit->setLayoutLocation(p);
		unit->setLayoutSize(size);
		i++;
	}

	Console::WriteLine(
		" Width " + Width +
		"\n Height" + Height +
		"\n gap_width " + gap_width +
		"\n gap_height " + gap_height +
		"\n control_per_row " + control_per_row +
		"\n control_per_column " + control_per_column
	);
}



void GridLayout::excuteLayout() {
	for each (LayoutUnit^ unit in this->grid) {
		unit->setCurrentLocation();
		unit->setCurrentSize();
	}
}