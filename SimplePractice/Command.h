#pragma once
#pragma once
#include "Mathobj.h"

using namespace System::Collections;
using namespace math_obj;



#define lex_parse 0
#define op_parse 2
#define vec 1
#define opt 8
#define format_ex -1

namespace CommandHandle {
	ref class command_func;
	ref class ParseTree;
	typedef void(*cmd_func)(command_func^ func);
	ref class CommandParser {
	private:
		
		int cmdcount;
		String^ result;
		array<command_func^>^ table;
		array<String^>^ operators;
		wchar_t parse_op(String^ str);
		ParseTree^ parse_default_cmd(array<String^>^ spilt_str);
		math_obj::MathCaculator^ mathc;

	public:
		void setResualt(String^ str) {
			this->result = gcnew String(str);
		}
		static String^ globalstr;
		int match(array<String^>^ spilt_str);
		static myMath^ toMathFunc(CommandParser^ parser, String ^ func_name);
		String^ normalize(String^ cmd);
		CommandParser(math_obj::MathCaculator^ mathc,int cmds, array<String^>^ operators);
		void help();
		void add(String^ cmd_format, myMath^ mfunc, cmd_func func);
		math_obj::MathCaculator^ getMathCaculator() {
			return mathc;
		}

	};
	ref class command_func {
	public:

		String ^ cmd;
		cmd_func task;
		math_obj::myMath^ mfunc;
		array<String^>^ par_list;
		ArrayList^  par_double;
		ArrayList^ par_int;
		CommandParser^ belongs;
		command_func(CommandParser^ belongs, int i, String ^ cmd, cmd_func func);
		command_func(math_obj::MathCaculator^ mathc, CommandParser^ belongs, int i, String ^ cmd, cmd_func func);
		int index;
		void readInput(array<String^>^ spilt_str);
		void clean();
	};


	ref class ParseTree {
	private:
		ArrayList^ arglist;
		array<wchar_t>^ op_list;
	public:
		ParseTree();
		void excute();
		void addArg(System::Object^ obj);
		void show();
		void op_expr(ArrayList^ arglist);
	};


	void setGlobal(String^ str);
	void CmdInit(CommandParser^ parser, math_obj::MathCaculator^ mathc);

}