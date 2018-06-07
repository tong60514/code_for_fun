#pragma once
#include "FormLayout.h"
#include "Shape.h"
#include  "MathObj.h"
#include "LabelTable.h"
#include <math.h>
using namespace System;
using namespace FormLayout;
using namespace System::Drawing::Drawing2D;


ref class PlotBoard : public Panel {
public:
	//delegate Shape^ GetShape();
	delegate double PlotFunction(double f);

private:
	System::Drawing::Graphics^ g;
	System::Windows::Forms::Timer^ timer;
	System::Drawing::Region^ clipRegion;

	float XRatio;
	float YRatio;
	float interval;
	float realCoodinate;

	System::Drawing::Font^ drawFont;
	System::Drawing::SolidBrush^ drawBrush;
	System::Drawing::Point Org;
	System::Drawing::Pen^ plotPen;
	System::Drawing::Rectangle reg;
	System::Drawing::Rectangle plotReg;
	
};


