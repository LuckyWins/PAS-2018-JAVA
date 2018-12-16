#include "pch.h"
#include "Generation.h"

ofstream fout("Gen.java");
void Head()
{
	fout << "public class Gen {" << endl;
}
void Down()
{
	fout << "}";
	fout.close();
}
int tab_count = 1; // Счетчик кол-ва символов табуляции
string Tab()
{
	string tb;
	for (int i = 0; i < tab_count; i++)
	{
		tb.append("\t");
	}
	return tb;
}

void Generation(LT::LexTable &Lextable, In::StToken *tokens)
{
	Head();
	
	for (int i = 0; i < Lextable.size; i++)
	{
		switch (Lextable.table[i].lexema)
		{
		case LEX_START:
			fout << Tab() << "public static void main(String args[])";
			//tab_count++;
			break;
		case LEX_PLUS:
		case LEX_STAR:
		case LEX_MINUS:
		case LEX_DIRSLASH:
		case LEX_EQUAL:
		{
			fout << " " << Lextable.table[i].lexema << " ";
			break;
		}
		case LEX_COMMA:
		case SPACE:
		{
			fout << Lextable.table[i].lexema << " ";
			break;
		}

		case LEX_RIGHTTHESIS:
		case LEX_LEFTHESIS:
		{
			fout << Lextable.table[i].lexema;
			break;
		}
		case LEX_LEFTBRACE:
		{
			fout << " " << Lextable.table[i].lexema << endl;
			tab_count++;
			break;
		}
		case LEX_BRACELET:
		{
			tab_count--;
			fout << Tab() << Lextable.table[i].lexema << endl;
			if (Lextable.size - i != 1)
			{
				fout << endl;
			}
			break;
		}
		case LEX_SEPARATOR:
		{
			fout << Lextable.table[i].lexema << endl;
			break;
		}
		case  LEX_CREATE:
		{
			// not now
			//fout << Lextable.table[i+1].lexema << " ";
			break;
		}
		case LEX_ID_TYPE_I:
			if (Lextable.table[i + 1].lexema != LEX_FUNCTION)
			{
				if (Lextable.table[i - 1].lexema != LEX_LEFTHESIS)
				{
					fout << Tab();
				}
				fout << "int ";
			}
			break;
		case LEX_ID_TYPE_W:
			if (Lextable.table[i + 1].lexema != LEX_FUNCTION)
			{
				if (Lextable.table[i - 1].lexema != LEX_LEFTHESIS)
				{
					fout << Tab();
				}
				fout << "String ";
			}
			break;
		case LEX_LITERAL:
		case LEX_ID:
		{
			if (Lextable.table[i - 1].lexema == LEX_SEPARATOR) {
				fout << Tab();
			}
			fout << tokens[i].token;
			break;
		}
		case LEX_OUT:
		{
			fout << Tab() << "System.out.println";
			break;
		}
		case tochka:
		{
			fout << endl;
			break;
		}
		case LEX_FUNCTION:
		{
			fout << Tab() << "public static ";
			switch (Lextable.table[i - 1].lexema)
			{
			case LEX_ID_TYPE_I:
				fout << "int ";
				break;
			case LEX_ID_TYPE_W:
				fout << "String ";
				break;
			case LEX_BRACELET:
				fout << "void ";
				break;
			}
			break;
		}
		case LEX_RETURN:
		{
			fout << Tab() << "return ";
			break;
		}
		case LEX_LIB:
		{	
			fout << "import mylib.MyLib";
			break;
		}
		case LEX_SQRT:
		{
			fout << "MyLib.sqrt";
			break;
		}
		case LEX_STEP:
		{
			fout << "MyLib.pow";
			break;
		}
		}
	}
	Down();

}