#include "Command.h"
using namespace CommandHandle;
command_func::command_func(CommandParser^ belongs, int i, String ^ cmd, cmd_func func) {
	this->index = i;
	this->cmd = cmd;
	this->task = func;
	this->par_int = gcnew ArrayList;
	this->par_double = gcnew ArrayList;
	this->belongs = belongs;
}

command_func::command_func(
	math_obj::MathCaculator^ mathc,CommandParser^ belongs, 
	int i,String ^ cmd, cmd_func func)
	:command_func( belongs, i, cmd, func){
	this->index = i;
	this->cmd = cmd;
	this->task = func;
	this->par_int = gcnew ArrayList;
	this->par_double = gcnew ArrayList;
	this->belongs = belongs;
}

void command_func::clean() {
	delete this->par_double;
	delete this->par_int;
	this->par_int = gcnew ArrayList;
	this->par_double = gcnew ArrayList;
}

ParseTree::ParseTree() {
	arglist = gcnew ArrayList;
}

void ParseTree::addArg(System::Object^ obj) {
	this->arglist->Add(obj);
}

void ParseTree::show() {
	MyVector^ v;
	for (int i = 0; i < arglist->Count; i++) {
		v = (MyVector^)arglist[i];
		v->out();
	}
	for (int i = 0; i < this->op_list->GetLength(0); i++) {
		Console::WriteLine(op_list[i]);
	}
}

void ParseTree::op_expr(ArrayList^ arglist) {
	this->op_list = gcnew array<wchar_t>(arglist->Count);
	for (int i = 0; i < arglist->Count; i++) {
		op_list[i] = (wchar_t)arglist[i];
	}
}

wchar_t CommandParser::parse_op(String^ str) {
	for (int i = 0; i < operators->GetLength(0); i++) {
		if (str->Equals(operators[i]))
			return Convert::ToChar(operators[i]);
	}
	return ' ';
}

String^ CommandParser::normalize(String^ cmd) {
	for (int i = 0; i < this->operators->GetLength(0); i++) {
		cmd = cmd->Replace(this->operators[i], " " + this->operators[i] + " ");
	}
	return cmd;
}

CommandParser::CommandParser(math_obj::MathCaculator^ mathc, int cmds, array<String^>^ operators) {
	table = gcnew array<command_func^>(cmds);
	this->cmdcount = 0;
	this->operators = operators;
	this->mathc = mathc;
}

void CommandParser::help() {
	Console::WriteLine("--------------------------------------------------- ");
	Console::WriteLine();
	Console::WriteLine();
	for (int i = 0; i < this->cmdcount; i++) {
		Console::Write(this->table[i]->cmd);
		for (int j = 1; j < this->table[i]->par_list->GetLength(0); j++) {
			Console::Write(" [ " + this->table[i]->par_list[j] + " ]");
		}
		Console::WriteLine(" ");
		Console::WriteLine(" ");
	}

	Console::WriteLine("vector + :[x1,x2,....xn]+[y1,y2....yn]");
	Console::WriteLine();
	Console::WriteLine();
	Console::WriteLine("vector inner product  :[x1,x2,...xn]*[y1,y2...yn]");
	Console::WriteLine();
	Console::WriteLine();
	Console::WriteLine("--------------------------------------------------- ");
}

void CommandParser::add(String^ cmd_format, myMath^ mfunc, cmd_func func) {
	array<wchar_t>^ saper = { '_' };
	array<String^>^ str_list = cmd_format->Split(saper);
	this->table[cmdcount] = gcnew command_func(this, cmdcount, str_list[0], func);
	this->table[cmdcount]->mfunc = mfunc;
	this->table[cmdcount]->par_list = str_list;
	cmdcount++;
}

void command_func::readInput(array<String^>^ spilt_str) {
	try {

		for (int i = 1; i < par_list->GetLength(0); i++) {
			if (par_list[i]->Equals("Double")) {
				this->par_double->Add(Convert::ToDouble(spilt_str[i]));
				continue;
			}

			if (par_list[i]->Equals("Int")) {
				this->par_int->Add(Convert::ToInt32(spilt_str[i]));
				continue;
			}
			if (par_list[i]->Equals("Func")) {
				this->mfunc = CommandParser::toMathFunc(this->belongs, spilt_str[i]);
				Console::WriteLine(spilt_str[i]);
				if (this->mfunc == nullptr)
					throw gcnew Exception;
				continue;
			}

		}
	}
	catch (FormatException^ ex) {
		throw ex;
	}
	catch (Exception^ ex) {
		throw ex;
	}
}











int CommandParser::match(array<String^>^ spilt_str) {
	int count = 0;
	ParseTree^ tree;
	try {
		tree = parse_default_cmd(spilt_str);
		try {
			tree->excute();
		}
		catch (Exception^ ex) {
			return -1;
		}
		return 0;
	}
	catch (FormatException^ ex) {
		goto HandleAdditionalCommand;
	}

HandleAdditionalCommand:
	for (int i = 0; i < this->table->GetLength(0); i++) {
		if (spilt_str[0]->Equals(this->table[i]->cmd)) {
			try {
				this->table[i]->readInput(spilt_str);
			}
			catch (FormatException^ ex) {
				throw;
			}
			try {
				this->table[i]->task(this->table[i]);
			}
			catch (Exception^ ex) {
				throw;
			}
			this->table[i]->clean();
			return count;
		}
		count++;
	}
	return -1;
}

myMath^ CommandParser::toMathFunc(CommandParser^ parser, String ^ func_name) {
	int count = 0;
	for (int i = 0; i < parser->table->GetLength(0); i++) {
		if (func_name->Equals(parser->table[i]->cmd))
			return (parser->table[i]->mfunc);
		count++;
	}
	return nullptr;
}


ParseTree^ CommandParser::parse_default_cmd(array<String^>^ spilt_str) {
	ParseTree^ pstree = gcnew ParseTree;
	ArrayList^ op_list = gcnew ArrayList;

	int state = lex_parse;
	int ptr = 0;
	int cmd_len = spilt_str->GetLength(0);
tran:

	if (ptr == cmd_len) {
		delete op_list;
		pstree->op_expr(op_list);
		return pstree;
	}
	switch (state) {

	case lex_parse:
		if (spilt_str[ptr]->Equals("[")) {
			state = vec;
			goto tran;
		}
		state = format_ex;
		goto tran;
	case op_parse:
		goto operator_parse;
	case vec:
		goto vec_parse;
	case format_ex:
		throw gcnew FormatException;
	}


vec_parse:
	try {
		MyVector^ vec_1 = gcnew MyVector(spilt_str, ptr);
		pstree->addArg(vec_1);
		state = op_parse;
		ptr += (vec_1->len() + 2);
	}
	catch (FormatException^ ex) {
		state = format_ex;
	}

	goto tran;
operator_parse:
	wchar_t op = parse_op(spilt_str[ptr]);
	switch (op) {
	case '+':
	case '*':
	case '-':
		ptr++;
		state = lex_parse;
		op_list->Add(op);
		break;
	case ' ':
	default:
		state = format_ex;
	}

	goto tran;
}
void CommandHandle::setGlobal(String^ str) {
	CommandParser::globalstr = gcnew String(str);
}
void ParseTree::excute() {
	int state = opt;
	int op_ptr = 0;
	int arg_ptr = 1;
	int arg_len = arglist->Count;
	double f_res;
	MyVector^ v_res = (MyVector^)arglist[0];
	if (arglist->Count != 2 | op_list->GetLength(0) != 1)
		throw gcnew FormatException;

	switch (op_list[op_ptr]) {
	case '+':
		v_res->add((MyVector^)arglist[arg_ptr]);
		Console::Write(" := ");
		v_res->out();
		Console::WriteLine();
		break;
	case '*':
		MyVector^ v_vec2 = (MyVector^)arglist[arg_ptr];
		if (v_res->len() != v_vec2->len())
			throw gcnew FormatException;
		f_res = v_res->dot((MyVector^)arglist[arg_ptr]);
		Console::WriteLine(" := " + f_res);

	}
	return;
}

void CommandHandle::CmdInit(CommandParser^ parser,MathCaculator^ mathc) {

	parser->add("sin_Double", gcnew math_obj::myMath(mathc,&MathCaculator::sin), [](command_func^ cmd) {
		setGlobal("sin(" + (double)cmd->par_double[0] + ") = " + cmd->mfunc((double)cmd->par_double[0]));
	});

	parser->add("cos_Double", gcnew math_obj::myMath(mathc, &MathCaculator::cos), [](command_func^ cmd) {
		setGlobal("cos(" + (double)cmd->par_double[0] + ") = " + cmd->mfunc((double)cmd->par_double[0]));
	});
	parser->add("exp_Double", gcnew math_obj::myMath(mathc, &MathCaculator::exp), [](command_func^ cmd) {
		setGlobal("exp(" + (double)cmd->par_double[0] + ") = " + cmd->mfunc((double)cmd->par_double[0]));
	});
	parser->add("pow_Double_Double", nullptr, [](command_func^ cmd) {
		throw gcnew Exception;
	});
	auto feight = [](command_func^ cmd) {
		setGlobal("actan(" + (double)cmd->par_double[0] + ") = " + cmd->mfunc((double)cmd->par_double[0]));
	};
	parser->add("actan_Double", gcnew math_obj::myMath(mathc, &MathCaculator::actan), feight);

	parser->add("sinc_Double", gcnew math_obj::myMath(mathc, &MathCaculator::sinc), [](command_func^ cmd) {
		setGlobal("sinc(" + (double)cmd->par_double[0] + ") = " + cmd->mfunc((double)cmd->par_double[0]));
	});
	parser->add("quit", nullptr, [](command_func^ cmd) {
		throw gcnew Exception;
	});
	parser->add("array", nullptr, [](command_func^ cmd) {
		throw gcnew Exception;
	});
	parser->add("expand_Func_Double_Int", nullptr, [](command_func^ cmd) {
		Caculator* cac = new Caculator();
		cac->expand(cmd->belongs->getMathCaculator(),cmd->mfunc, (int)cmd->par_int[0], (double)cmd->par_double[0]);
		setGlobal(cac->getRes());
		delete cac;
	});
	parser->add("help", nullptr, [](command_func^ cmd) {
		cmd->belongs->help();
		//Console::WriteLine("sinc(" + (double)cmd->par_double[0] + ") = " + math_obj::sinc((double)cmd->par_double[0]));
	});
}