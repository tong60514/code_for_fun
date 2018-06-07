#pragma once
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

namespace FormLayout {
	enum AlignType {
		LEFT, CENTER, RIGHT, TOP, BOTTOM
	};

	


	ref class Layout {
	public:
		
		virtual void buildLayout()=0;
		virtual void excuteLayout()=0;

		static void Generate(Layout^ lt) {
			lt->buildLayout();
			lt->excuteLayout();
		}
		static void AlignParentForm(Form^ form, Control^ ctrl, AlignType type) {
			System::Drawing::Point p;
			switch (type) {
			case CENTER:
				p.X = ((float)form->Width) / 2 - ((float)ctrl->Width)/2;
				p.Y = ((float)form->Height) / 2 - ((float)ctrl->Height)/2;
				break;
			case LEFT:
				p.X = ((float)form->Width)-((float)ctrl->Width);
				p.Y = ((float)form->Height)/2-((float)ctrl->Height)/2;
				break;
			case TOP:
				p.X = ((float)form->Width)/2-((float)ctrl->Width);
				p.Y = 0;
				break;
			case BOTTOM:
				p.X = ((float)form->Width) / 2 - ((float)ctrl->Width)/2;
				p.Y = ((float)form->Height)-((float)ctrl->Height);
				break;
			case RIGHT:
				p.X = 0;
				p.Y = ((float)form->Height) / 2 - ((float)ctrl->Height) / 2;
				break;
			default:
				throw gcnew Exception;
			}

			ctrl->Location = p;
		}
	};


	delegate Layout^ LayoutBuilder(Form^ form);
	ref class LayoutUnit {
	private:
		Control^ ctrl;
		System::Drawing::Point layout_location;
		System::Drawing::Size layout_size;
	public:
		LayoutUnit(Control^ ctrl) {
			this->ctrl = ctrl;
			layout_location.X = -1;
			layout_size.Width = -1;
		}
		System::Drawing::Point% getLayoutLocation() {
			return layout_location;
		}
		System::Drawing::Point% getCurrentLocation() {
			return this->ctrl->Location;
		}
		System::Drawing::Size% getLayoutSize() {
			return layout_size;
		}
		System::Drawing::Size% getCurrentSize() {
			return this->ctrl->Size;
		}

		void setLayoutLocation(System::Drawing::Point& layout_location) {
			this->layout_location = layout_location;
		}
		void setCurrentLocation() {
			if(layout_location.X>0)
				this->ctrl->Location = layout_location;
		}
		void setLayoutSize(System::Drawing::Size& layout_size) {
			this->layout_size = layout_size;
		}
		void setCurrentSize() {
			if(layout_size.Width>0)
				this->ctrl->Size = layout_size;
		}

	};



	ref class GridLayout :public Layout{
	private:
		List<LayoutUnit^>^ grid;
		int marginWidth = 20;
		Form^ form;
	public :
		GridLayout(Form^ form);
		void addControl(Control^ ctrl);
		virtual void buildLayout() override;
		//void rebuildLayout();
		
		virtual void excuteLayout () override;
		static Layout^ createGridLayout(Form^ form) {
			return gcnew GridLayout(form);
		}
	};
	



	/*void ratioSize(Control^ src,Control^ dst,float Wratio,float Hratio) {
		dst->AutoSize = false;
		dst->Width = (int)((float)src->Width * Wratio);
		dst->Height = (int)((float)src->Height * Hratio);
	}

	void cpySize(Control^ src, Control^ dst) {
		ratioSize(src,dst,1.0,1.0);
	}

	void HNext(Control^ org, Control^ dst, int distance) {
		dst->Location = System::Drawing::Point(org->Location.X+org->Width+distance,org->Location.Y);
	}
	void VNext(Control^ org, Control^ dst, int distance) {
		dst->Location = System::Drawing::Point(org->Location.X , org->Location.Y + org->Height + distance);
	}*/


};