#pragma once
#include "Command.h"
#include "FormLayout.h"
using namespace CommandHandle;
using namespace System::Windows::Forms;
using namespace System;
using namespace FormLayout;
	
	ref class TimerPanel : public Panel {
	private:
		System::Windows::Forms::Timer^ timer;

		Button^ ctrl_button;
		Label^ counter_label;
		int bound;
		int init;

	public:
		TimerPanel(int Width, int Height, System::Drawing::Point& p) {

			//this->AutoSize = false;
			this->Height = Height;
			this->Width = Width;
			this->Location = p;
			this->BackColor = System::Drawing::Color::Green;
			this->timer = gcnew System::Windows::Forms::Timer;
			this->timer->Tick += gcnew EventHandler(this, &TimerPanel::timerEvent);
			this->ctrl_button = gcnew Button;
			this->ctrl_button->AutoSize = false;
			this->ctrl_button->Width = this->Width / 2;
			this->ctrl_button->Height = this->Height / 2;
			this->ctrl_button->Text = "Start";
			this->ctrl_button->Click += gcnew EventHandler(this, &TimerPanel::ctrl_button_evt_handler);

			this->counter_label = gcnew Label;
			this->counter_label->AutoSize = false;
			this->counter_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Font = gcnew System::Drawing::Font("Times New Roman", Height / 4);

			this->counter_label->Height = this->Height;
			this->counter_label->Width = this->Width / 2;
			this->counter_label->Font = gcnew System::Drawing::Font("Times New Roman", this->counter_label->Height / 4);
			this->counter_label->Location = System::Drawing::Point(ctrl_button->Width, 0);

			this->Controls->Add(counter_label);
			this->Controls->Add(ctrl_button);
			//this->Text = Convert::ToString(init);
		}
		void setInterval(int milliseconds) {
			this->timer->Interval = milliseconds;
		}

		void timerEvent(Object^, EventArgs^) {
			if (init >= bound) {
				init = 0;
			}
			else {
				this->init++;
			}
			this->counter_label->Text = Convert::ToString(init);
			Console::WriteLine(counter_label->Text);
		}

		void ctrl_button_evt_handler(Object^, EventArgs^) {
			this->timer->Enabled = !this->timer->Enabled;
			Console::WriteLine("button click");
		}

		void setTimerRange(int init, int bound) {
			this->init = init;
			this->bound = bound;
		}
		void stop() {
			this->timer->Stop();
		}
		void start() {
			this->timer->Start();
		}

	};

	ref class ButtonListPanel : public Panel{
	private:
		List<Button^>^ buttonSet;

		System::Drawing::Size ButtonSize;
		
	public:
		ButtonListPanel(int Width, int Height) {
			buttonSet = gcnew List<Button^>;
			this->AutoSize = false;
			this->Width = Width;
			this->Height = Height;
		}

		void addButton(Button^ button) {
			this->Controls->Add(button);
			/*int reSizeHieght  = (int)( (float)this->Height/(float)(buttonSet->Count + 2)  );
			
			int Y = 0;
			int W = this->Width;
			for each (Button^ u in this->buttonSet) {
				u->Size.Height = reSizeHieght;
				u->Location.Y = Y;
				Y += reSizeHieght;
			}*/
			
			button->Size = System::Drawing::Size(this->Width, 30);
			button->Location = System::Drawing::Point(0, 30 * buttonSet->Count);
			this->buttonSet->Add(button);
		}
	};


	ref class PhraseSelectForm :public Form {
	private:
		RadioButton^ radioButtonRatio, ^radioButtonPi, ^ radioButtonDegree;
		GroupBox^ gpbox;
		Button^ button1, ^button2;
		Label^ label;
		PHRASE phaseState;

		void radioButtonRatio_CheckedChanged(Object^ snder, EventArgs^ arg);
		void radioButtonPi_CheckedChanged(Object^ snder, EventArgs^ arg);
		void radioButtonDegree_CheckedChanged(Object^ snder, EventArgs^ arg);
		void canel_evt(Object^ obj, EventArgs^ arg);

		void InitializeComponent();
	public:
		PhraseSelectForm();
		PHRASE getPhrase() {
			return this->phaseState;
		}
	};


	ref class myForm : public Form {
	private:

		ref class TimerCreateForm :public Form {
		private:
			TextBox^ init_label;
			TextBox^ bound_label;
			TextBox^ interval_label;
			Button^ button;
			myForm^ parentForm;


		public:
			//delegate void dynamic_remove_control(Control^ ctrl);
			TimerCreateForm(myForm^ parentForm);
			void GenNext(Control^ txt1, Control^txt2) {
				txt2->AutoSize = false;
				txt2->Width = txt1->Width;
				txt2->Height = txt2->Height;
				txt2->Location = System::Drawing::Point(txt1->Location.X, txt1->Location.Y + 15);
			}
			void creatTimer_click(Object^, EventArgs^) {
				Console::WriteLine("create timer click");
				try {
					int init = Convert::ToInt32(this->init_label->Text);
					int boune = Convert::ToInt32(this->bound_label->Text);
					int interval = Convert::ToInt32(this->interval_label->Text);
					this->parentForm->addTimers(init, boune, interval);
				}
				catch (FormatException^ ){
					MessageBox::Show("format error\n"+ 
						"Init :"+this->init_label->Text +"\n"+
						"Bound :" + this->bound_label->Text + "\n" +
						"Interval :" + this->interval_label->Text + "\n" );
				}
			}
			void close_event_handler(Object^,EventArgs^ e) {
				this->init_label->Text = "";
				this->bound_label->Text = "";
				this->interval_label->Text = "";
			}

			//void addDynamicControl(Control^ ctrl);
		};

		MenuStrip^ menustrip;
		ToolStripMenuItem^ fileItem;
		ToolStripMenuItem^ mathItem;
		ToolStripMenuItem^ timeItem;

		static array<String^>^ op_str = { "+", "-", "*","[","]" };
		TextBox^ textBox1, ^textBox2;
		Button^ button1, ^button2, ^button3;

		Label^ label;
		PhraseSelectForm^ select;
		PHRASE phrase;
		CommandParser^ parser;
		MathCaculator^ caculator;
		array<TimerPanel^>^ timers;

		ButtonListPanel^ button_container;
		TimerCreateForm^ timerCreator;


		int max_timers;
		int Tcount;

		void InitializeComponent();
		void b1_evt_handler(Object^ snder, EventArgs^ arg);
		void b2_evt_handler(Object^ snder, EventArgs^ arg);
		void b3_evt_handler(Object^ snder, EventArgs^ arg);

		void mathItem_Click(Object^ snder, EventArgs^ ar) {
			Console::WriteLine("math item click");
			addTimers(0, 100, 500);
		}

		void fileItem_Click(Object^ snder, EventArgs^ ar) {
			Console::WriteLine("file item click");
		}

		void timeItem_Click(Object^ snder, EventArgs^ ar) {
			Console::WriteLine("time item click");
			this->timerCreator->ShowDialog();
		}


	public:
		myForm();
		PHRASE getPhase() {
			return this->phrase;
		}
		TextBox^ getTxtBox2() {
			return this->textBox2;
		}

		//void addGridButton(Button^ button);
		//void addMenuItem(String^,EventHandler^);
		

		void addTimers(int init, int bound, int interval) {
			if (Tcount == 20) {
				return;
			}
			TimerPanel^ NewTimer = gcnew TimerPanel(60, 60, System::Drawing::Point(50 + 80 * (Tcount % 5), 200 + 80 * (Tcount / 5)));
			this->timers[Tcount] = NewTimer;
			this->Controls->Add(NewTimer);
			NewTimer->setInterval(interval);
			NewTimer->setTimerRange(init, bound);
			NewTimer->start();
			Tcount++;
		}
	};



	ref class LayoutForm :public Form{
	private:
		MenuStrip^ menustrip ;
		ButtonListPanel^ BtList;

		
		virtual void InitComponent() {
			
		};

		void InitButtonList(AlignType type) {
			this->BtList = gcnew  ButtonListPanel(this->Width*0.15, Height*0.8 );
			this->Controls->Add(BtList);
			FormLayout::Layout::AlignParentForm(this, BtList, type);
		}

		void InitMenuStrip() {
			this->menustrip = gcnew MenuStrip;
			this->Controls->Add(menustrip);
		}
		void InitBoard() {
			TextBox^ box = gcnew TextBox;
			this->Controls->Add(box);

			box->AutoSize = false;

			box->Size = System::Drawing::Size(this->Width*0.6, this->Height*0.6);

			FormLayout::Layout::AlignParentForm(this, box, CENTER);

		}

	public:
		LayoutForm(int Width,int Height) {


			this->AutoSize = false;
			this->Size = System::Drawing::Size(Height, Width);
			
			//InitButtonList(RIGHT);

			InitMenuStrip();
			//InitBoard();

			InitComponent();
		}

		LayoutForm() {
			InitMenuStrip();
			//InitBoard();

			InitComponent();
		}
		
		Button^ addButton(String^ button_text,EventHandler^ evt) {
			Button^ button = gcnew Button;
			button->Text = button_text;
			button->Click += evt;
			this->BtList->addButton(button);
			return button;
		}
		void addMenuItem(String^ str, EventHandler^ evt) {
			ToolStripMenuItem^ item = gcnew ToolStripMenuItem;
			item->Text = str;
			item->Click += evt;
			menustrip->Items->Add(item);
		}
		void addMenuItem(String^ text, ToolStripMenuItem^ item) {
			item->Text = text;
			menustrip->Items->Add(item);
		}
	};

	
// new code 



