#include "GuiForm.h"
void PhraseSelectForm::radioButtonRatio_CheckedChanged(Object^ snder, EventArgs^ arg) {
	Console::WriteLine("ratio");
	RadioButton^ sndr = (RadioButton^)snder;
	if (sndr->Checked) {
		label->Text = "ratio";
		phaseState = Raito;
	}
}
void PhraseSelectForm::radioButtonPi_CheckedChanged(Object^ snder, EventArgs^ arg) {
	Console::WriteLine("Pi");
	RadioButton^ sndr = (RadioButton^)snder;
	if (sndr->Checked) {
		label->Text = "Pi";
		phaseState = PI;
	}
}
void PhraseSelectForm::radioButtonDegree_CheckedChanged(Object^ snder, EventArgs^ arg) {
	Console::WriteLine("Degree");
	RadioButton^ sndr = (RadioButton^)snder;
	if (sndr->Checked) {
		label->Text = "Degree";
		phaseState = degree;
	}

}
void PhraseSelectForm::canel_evt(Object^ obj, EventArgs^ arg) {
	this->Close();
}

void PhraseSelectForm::InitializeComponent() {
	gpbox = gcnew GroupBox;
	button1 = gcnew Button;
	this->Controls->Add(button1);
	this->button1->Click += gcnew EventHandler(this, &PhraseSelectForm::canel_evt);
	this->button1->Text = "Ok";
	button2 = gcnew Button;
	label = gcnew Label;

	this->Text = "Format Select";

	this->Controls->Add(gpbox);
	gpbox->Text = "Phase";
	gpbox->Size = System::Drawing::Size(110, 110);
	gpbox->Location = System::Drawing::Point(10, 5);
	radioButtonRatio = gcnew RadioButton;
	radioButtonPi = gcnew RadioButton;
	radioButtonDegree = gcnew RadioButton;


	this->gpbox->Controls->Add(radioButtonRatio);
	this->gpbox->Controls->Add(radioButtonPi);
	this->gpbox->Controls->Add(radioButtonDegree);


	radioButtonRatio->Text = "Ratio (2PI)";
	radioButtonRatio->Size = System::Drawing::Size(95, 20);
	radioButtonRatio->Checked = false;
	radioButtonRatio->Location = System::Drawing::Point(10, 20);
	radioButtonRatio->CheckedChanged += gcnew  EventHandler(this,
		&PhraseSelectForm::radioButtonRatio_CheckedChanged);

	radioButtonPi->Text = "PI";
	radioButtonPi->Size = System::Drawing::Size(95, 20);
	radioButtonPi->Checked = false;
	radioButtonPi->Location = System::Drawing::Point(10, 40);
	radioButtonPi->CheckedChanged += gcnew  EventHandler(this,
		&PhraseSelectForm::radioButtonPi_CheckedChanged);

	radioButtonDegree->Text = "Degree";
	radioButtonDegree->Size = System::Drawing::Size(95, 20);
	radioButtonDegree->Checked = false;
	radioButtonDegree->Location = System::Drawing::Point(10, 60);
	radioButtonDegree->CheckedChanged += gcnew  EventHandler(this,
		&PhraseSelectForm::radioButtonDegree_CheckedChanged);
	label->Location = System::Drawing::Point(130, 20);
	this->Controls->Add(label);
}

PhraseSelectForm::PhraseSelectForm() {
	this->InitializeComponent();
}