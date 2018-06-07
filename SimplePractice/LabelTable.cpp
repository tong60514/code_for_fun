#include "LabelTable.h"

LabelTable::LabelTable(array<String^>^ headers,int label_width, int label_height) {
	
	this->column = headers->Length ;
	this->Width = label_width*(column+1);
	this->Height = label_height;
	this->label_size.Width = label_width;
	this->label_size.Height = label_height;
	this->bottom_height = 0;

	array_label_list = gcnew List<array<Label^>^>;
	this->button_list = gcnew List<DeleteButton^>;
	setHeader(headers);
}
static array<String^>^ LabelsToStringArray(array<Label^>^ label_array) {
	array<String^>^ string_array = gcnew array<String^>(label_array->Length);

	for (int i = 0; i < label_array->Length; i++) {
		string_array[i] = label_array[i]->Text;
	}
	return string_array;
}
LabelTable^ LabelTable::LablelMap(array<Label^>^ label_array,System::Drawing::Size& labelSize) {
	array<String^>^ string_array = LabelsToStringArray(label_array);
	LabelTable^ table = gcnew LabelTable(
		string_array, labelSize.Width, labelSize.Height
	);

	return table;


}
void LabelTable::update() {
	int count = 0;
	System::Drawing::Point p;
	p.Y = this->label_size.Height;
	p.X = 0;
	for each (array<Label^>^ label_row in this->array_label_list) {
		for (int i = 0; i < column; i++) {
			label_row[i]->Location = p;
			p.X += label_size.Width;
			Console::WriteLine(label_row[i]->Text);
		}
		p.Y += label_size.Height;
		p.X = 0;
		label_row[0]->Text = Convert::ToString(count);
		count++;
	}

	p.Y = this->label_size.Height;
	p.X = column*label_size.Width;
	for each (DeleteButton^ button in this->button_list) {
		button->Location = p;
		p.Y+= label_size.Height;
	}
	this->Height = label_size.Height*(1+PointCount());
	Refresh();

}
void LabelTable::setHeader(array<String^>^ string_array) {
	array<Label^>^ label_array = gcnew array<Label^>(this->column);
	for (int i = 0; i < this->column; i++) {
		label_array[i] = gcnew Label;
		label_array[i]->Text = string_array[i];
		
		label_array[i]->Size = label_size;
		label_array[i]->Location = 
			System::Drawing::Point(i*label_size.Width,bottom_height);
		this->Controls->Add(label_array[i]);
	}

	bottom_height = this->label_size.Height;
}
void LabelTable::remove_DeleteButton_handler(Object^ obj){
	array<Label^>^ labelArray = (array<Label^>^)obj;
	this->array_label_list->Remove(labelArray);
	for (int i = 0; i < column; i++) {
		this->Controls->Remove(labelArray[i]);
	}
}
void LabelTable::addRow(array<Label^>^ label_array) {

	DeleteButton^ button = gcnew DeleteButton(label_array,
		gcnew DeleteButton::Remove_Control_handler(this,&LabelTable::remove_DeleteButton_handler));
	button->Size = this->label_size;
	button->Click += gcnew EventHandler(this,&LabelTable::delete_button_click_handler);
	this->array_label_list->Add(label_array);
	this->button_list->Add(button);

	for ( int i = 0; i < label_array->Length; i++ ) {
		label_array[i]->Width = label_size.Width;
		label_array[i]->Height = label_size.Height;
		this->Controls->Add(label_array[i]);
	}
	this->update();

	//button->Location = System::Drawing::Point(column*this->label_size.Width, bottom_height);

	this->Controls->Add(button);
	
	

}
void LabelTable::delete_button_click_handler(Object^ obj, EventArgs^ evt) {
	DeleteButton^ button = (DeleteButton^)obj;
	Console::WriteLine("remove");
	button->remove();
	this->update();
	this->Refresh();
}


array<Label^>^ LabelTable::createHeaders(array<String^>^ strs) {
	array<Label^>^ string_format_data = gcnew array<Label^>(strs->Length);
	for (int i = 0; i < strs->Length; i++) {
		string_format_data[i] = gcnew Label;
		string_format_data[i]->Text = strs[i];
	}
	return string_format_data;

}