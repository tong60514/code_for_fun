#pragma once
using namespace System;
using namespace System::Windows::Forms;


namespace TaskConfiguration {
	delegate void ConfigHandlerTriger(Object^, EventArgs^);
	delegate void StringConfig(String^);
	delegate void IntegerConfig(int integer);
	delegate void FloatConfig(float flt);

	/*
		
	*/
	ref class ConfigControls{
		StringConfig^ strConfig;
		IntegerConfig^ intConfig;
		FloatConfig^  fltConfig;
	public :
		ConfigControls(Control^);
		ConfigControls(Button^);
		ConfigControls(TextBox^);
		ConfigControls(GroupBox^,array<RadioButton^>^);
		
		void setConfig(StringConfig^);
		void setConfig(IntegerConfig^);
		void setConfig(FloatConfig^);

	};
	ref class ConfigForm : public Form {
	private:
		ConfigForm() {}
	public:
		ConfigForm(Form^ fm);
		void configTriger(Object^, EventArgs^);
		void addStringConfig(ConfigControls^,StringConfig^);
		void addIntegerConfig(ConfigControls^, IntegerConfig^);
		void addFloatConfig(ConfigControls^, FloatConfig^);
	};

	/*
		Composite this class in the Form you want to parametize your task by another form.

		call setConfig to add the form you design to get the Configuration

		the function getTriggerHandler can implement the config event in the form you design

	*/
	ref class selector {
	private:
		ConfigHandlerTriger^ handler;
		ConfigForm^ configforms;
	public:
		selector(Form^ parent);
		void setConfig(ConfigForm^ configforms,ConfigHandlerTriger^ handler);
		void getTriggerHandler();
	};

}