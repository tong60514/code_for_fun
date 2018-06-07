

#include "GuiForm.h"
#include "FormLayout.h"
using namespace FormLayout;
void myForm::InitializeComponent() {
	GridLayout^ grid = gcnew GridLayout(this);
	
	parser = gcnew CommandParser(this->caculator,10, op_str);
	CmdInit(parser, parser->getMathCaculator());
	select = gcnew PhraseSelectForm;
	textBox1 = gcnew TextBox;
	this->Width = 800; this->Height = 600;
	//this->Controls->Add(textBox1);

	grid->addControl(textBox1);
	textBox1->Location = System::Drawing::Point(200, 100);
	textBox1->Width = 102; textBox1->Height = 30;

	textBox2 = gcnew TextBox;
	//this->Controls->Add(textBox2);
	grid->addControl(textBox2);
	textBox2->Location = System::Drawing::Point(500, 200);
	textBox2->Multiline = true;
	textBox2->Width = 300; textBox2->Height = 400;

	label = gcnew Label;
	//this->Controls->Add(label);
	grid->addControl(label);
	label->Location = System::Drawing::Point(textBox1->Location.X+160, textBox1->Location.Y);
	label->Width = 130; label->Height = 30;
	label->Text = "(pow 0.13 2)";
	button1 = gcnew Button;
	button2 = gcnew Button;
	button3 = gcnew Button;
	//this->Controls->Add(button1);
	//this->Controls->Add(button2);
	//this->Controls->Add(button3);
	grid->addControl(button1);
	grid->addControl(button2);
	grid->addControl(button3);
	button1->Location = System::Drawing::Point(700, 51);
	button2->Location = System::Drawing::Point(700, 82);
	button3->Location = System::Drawing::Point(700, 113);
	button1->Text = "Cmd";
	button2->Text = "Enter";
	button3->Text = "Clear";

	this->button1->Click += gcnew EventHandler(this, &myForm::b1_evt_handler);
	this->button2->Click += gcnew EventHandler(this, &myForm::b2_evt_handler);
	this->button3->Click += gcnew EventHandler(this, &myForm::b3_evt_handler);

	this->menustrip = gcnew MenuStrip;
	this->Controls->Add(menustrip);

	
	this->mathItem = gcnew ToolStripMenuItem;
	this->timeItem = gcnew ToolStripMenuItem;
	this->fileItem = gcnew ToolStripMenuItem;

	this->menustrip->Items->AddRange(gcnew array<ToolStripItem^>(3){mathItem, timeItem, fileItem});

	this->mathItem->Text = L"math";
	this->mathItem->Click += gcnew EventHandler(this,&myForm::mathItem_Click);

	this->timeItem->Text = L"time";
	this->timeItem->Click += gcnew EventHandler(this, &myForm::timeItem_Click);

	this->fileItem->Text = L"file";
	this->fileItem->Click += gcnew EventHandler(this, &myForm::fileItem_Click);
	this->timers = gcnew array<TimerPanel^>(20);
	this->Tcount = 0;
	this->timerCreator = gcnew TimerCreateForm(this);
	//this->Controls->Add(timerCreator);

	grid->buildLayout();
	grid->excuteLayout();
}

void myForm::b1_evt_handler(Object^ snder, EventArgs^ arg) {
	this->select->ShowDialog();
	this->phrase = this->select->getPhrase();
}
void myForm::b2_evt_handler(Object^ snder, EventArgs^ arg) {
	array<String^>^ arr = { ","," " };
	try {

		String^ std_cmd = this->parser->normalize(this->textBox1->Text);
		array<String^>^ spilt_str = std_cmd->Split(arr, StringSplitOptions::RemoveEmptyEntries);
		int err;
		try {
			this->caculator->setArthType(this->phrase);
			err = parser->match(spilt_str);
			this->textBox2->Text = CommandParser::globalstr;
			Console::WriteLine(this->textBox2->Text);
		}
		catch (FormatException^ ex) {
			Console::WriteLine("format error . 'help'  for format detail");
			MessageBox::Show("format error . 'help'  for format detail");
			
		}
		if (err == -1) {
			Console::WriteLine(" command error.'help' for command ");
			MessageBox::Show(" command error.'help' for command ");
		}
		return;
	}
	catch (Exception^ ex) {
		Console::WriteLine(" error . 'help'  for  detail");
	}

	this->textBox1->Text = "";
}
void myForm::b3_evt_handler(Object^ snder, EventArgs^ arg) {
	this->textBox1->Text = "";
	this->textBox2->Text = "";
}

myForm::myForm() {
	caculator = gcnew math_obj::MathCaculator;
	InitializeComponent();
}
myForm::TimerCreateForm::TimerCreateForm(myForm^ parentForm) {
	this->parentForm = parentForm;

	this->Closed += gcnew EventHandler(this, &TimerCreateForm::close_event_handler);
	init_label = gcnew  TextBox;
	bound_label = gcnew TextBox;
	interval_label = gcnew TextBox;
	button = gcnew Button;

	this->Controls->Add(init_label);
	this->Controls->Add(bound_label);
	this->Controls->Add(interval_label);
	this->Controls->Add(button);

	init_label->Location = System::Drawing::Point(50, 50);
	init_label->Width = 130;
	init_label->Width = 30;
	init_label->AutoSize = false;

	GenNext(init_label, bound_label);
	GenNext(bound_label, interval_label);
	GenNext(interval_label, button);

	button->Click += gcnew EventHandler(this, &TimerCreateForm::creatTimer_click);

}