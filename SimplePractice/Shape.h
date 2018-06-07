#pragma once
using namespace System;
#include <math.h>
typedef enum {
	REC, LINE, ELLIPSE, POINT
}ShapeMode;




/*ref class Shape {
private:
	Shape() {}
public:
	System::Drawing::Point point;
	Shape(System::Drawing::Point& point);
	virtual void draw(System::Drawing::Graphics^ g, System::Drawing::Pen^ pen) = 0;
};
delegate Shape^ DrawShape(Object^ arg);

ref class Rec : public Shape {
public :
	Rec(System::Drawing::Point& point,float Width,float Height);
	virtual void draw(System::Drawing::Graphics^ g, System::Drawing::Pen^ pen)override;
	virtual void trans(System::Drawing::Drawing2D::Matrix^ matrix) override;
private:
	System::Drawing::Rectangle^ rec;

};

ref class Ellipse :public Shape{
public:
	System::Drawing::Point& vector;
	Ellipse(System::Drawing::Point& point, System::Drawing::Point& vector);
	virtual void draw(System::Drawing::Graphics^ g, System::Drawing::Pen^ pen) override;
	virtual void trans(System::Drawing::Drawing2D::Matrix^ matrix)override;
};

ref class Line : public Shape {
public:
	System::Drawing::Point vector;
	Line(System::Drawing::Point& point, System::Drawing::Point& vector) ;
	virtual void draw(System::Drawing::Graphics^ g, System::Drawing::Pen^ pen) override;
	virtual void trans(System::Drawing::Drawing2D::Matrix^ matrix) override;
};

ref class BigDot : public Shape{
private:
	System::Drawing::Brush^ brush;
	
public :
	BigDot(System::Drawing::Point& point, System::Drawing::Brush^ brush);
	virtual void draw(System::Drawing::Graphics^ g, System::Drawing::Pen^ pen) override;
	virtual void trans(System::Drawing::Drawing2D::Matrix^ matrix) override;
}*/