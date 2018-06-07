#pragma once
#include "FormLayout.h"
using namespace System;
using namespace FormLayout;

ref class LabelTable :public Panel {
private:
	ref class DeleteButton :public Button {
	public:

		delegate void Remove_Control_handler(Object^);

		Remove_Control_handler^ remove_task;
		DeleteButton(Object^ target, Remove_Control_handler^ remove_task) {
			this->target = target;
			this->Text = "delete";
			this->remove_task = remove_task;
		}
		void remove() {
			remove_task(target);
			LabelTable^ table = (LabelTable^)this->Parent;
			table->button_list->Remove(this);
			table->Controls->Remove(this);
			
		}
	private:
		Object^ target;
		Control^ owner;
	};

	int bottom_height;

	List<Label^>^ list;
	List<DeleteButton^>^ button_list;
	System::Drawing::Size label_size;
	List<array<Label^>^>^ array_label_list;
	int column;

	LabelTable() {}
	
	void setHeader(array<String^>^ string_array);

public:
	LabelTable(array<String^>^ headers,int label_width, int label_height);
	static LabelTable^ LablelMap(array<Label^>^ label_array, System::Drawing::Size& labelSize);
	void update();
	void remove_DeleteButton_handler(Object^ obj);
	void addRow(array<Label^>^ label_array);
	void delete_button_click_handler(Object^ obj, EventArgs^ evt);

	int PointCount() {
		return this->array_label_list->Count;
	}
	static array<Label^>^ createHeaders(array<String^>^ strs);
	

};

