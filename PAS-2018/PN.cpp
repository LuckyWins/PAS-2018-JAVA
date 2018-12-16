#include "pch.h"
#include "PN.h"

int PN::prior(char znak)
{
	switch (znak)
	{
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	default:
		return 0;
	}
}

int PN::search(int index, Lexer::LEX *tables) // Expression search
{
	for (int i = index; i < tables->Lextable.size; i++) // Bust of lexemes
	{
		if (tables->Lextable.table[i].lexema == LEX_PLUS || tables->Lextable.table[i].lexema == LEX_MINUS
			|| tables->Lextable.table[i].lexema == LEX_STAR || tables->Lextable.table[i].lexema == LEX_DIRSLASH) // Find operation
		{
			for (; ; i--) // Backward bust of lexemes 
			{
				if (tables->Lextable.table[i].lexema == LEX_EQUAL || tables->Lextable.table[i].lexema == LEX_RIGHTTHESIS)
					return i + 1;
			}
		}
	}
	return -1; // If not found
}

bool PN::CreatePolishNotation(Lexer::LEX *tables)
{
	std::stack <LT::Entry> stack_operators; // Operators storage
	bool build = false;

	int i = 0;
	int j = 0;
	int k = 0;

	while (search(i, tables) != -1)
	{
		j = i = search(i, tables); // First character index after equal symbol
		for (; tables->Lextable.table[i].lexema != LEX_SEPARATOR; i++, k++) // Read before ";" symbol (end of line)
		{
			if (tables->Lextable.table[i].lexema == LEX_LEFTHESIS || tables->Lextable.table[i].lexema == LEX_RIGHTTHESIS) // Found "(" or ")" symbols
			{
				switch (tables->Lextable.table[i].lexema) // Look lexeme
				{
				case LEX_LEFTHESIS:
				{
					if ((tables->Lextable.table[i - 1].idxTI != -1 && tables->IDtable.table[tables->Lextable.table[i - 1].idxTI].idtype == IT::F)
						|| tables->Lextable.table[i - 1].lexema == 'k' || tables->Lextable.table[i - 1].lexema == 'b')  // Return -1 if it isn't a variable
					{
						while (tables->Lextable.table[i - 1].lexema != LEX_RIGHTTHESIS)
						{
							i++;
						}
						break;
					}
					stack_operators.push(tables->Lextable.table[i]); // Fill operators stack (element of Lexemas table) 
					break;
				}
				case LEX_RIGHTTHESIS:
					while (stack_operators.top().lexema != LEX_LEFTHESIS) // Check top item from stack
					{
						result[size++] = stack_operators.top();
						stack_operators.pop(); // Get out top of operators stack
					}
					stack_operators.pop();
					break;
				}
			}
			else
			{
				switch (tables->Lextable.table[i].lexema) // If not "(" and ")" symbol
				{
				case LEX_STAR:
				case LEX_DIRSLASH:
				{
					stack_operators.push(tables->Lextable.table[i]); // Fill operators stack (element of Lexemas table) 
					break;
				}
				case LEX_PLUS:
				case LEX_MINUS:
					if (stack_operators.empty() || prior(tables->Lextable.table[i].lexema) == prior(stack_operators.top().lexema)) // Empty
						stack_operators.push(tables->Lextable.table[i]); // Fill operators stack (element of Lexemas table) 
					else // Operators stack not empty
					{
						while (!stack_operators.empty() && stack_operators.top().lexema != LEX_LEFTHESIS &&
							prior(tables->Lextable.table[i].lexema) < prior(stack_operators.top().lexema)) // If lexema not "(" and priority of operation less or equal to priority in the stack head
						{
							result[size++] = stack_operators.top(); // Fill result (head of stack)
							stack_operators.pop(); // Get out top of operators stack
						}
						if (!stack_operators.empty() && stack_operators.top().lexema == LEX_LEFTHESIS) // Check head of stack
						{
							stack_operators.push(tables->Lextable.table[i]); // Fill operators stack (element of Lexemas table) 
						}
						if (stack_operators.empty()) // Check head of stack
						{
							stack_operators.push(tables->Lextable.table[i]); // Fill operators stack (element of Lexemas table) 
						}
					}
					break;
				default:
					result[size++] = tables->Lextable.table[i]; // Fill result (Lexemas table)
					break;
				}
			}
		}
		for (; !stack_operators.empty(); i++) //выбить все операторы в Выходной стек
		{
			result[size++] = stack_operators.top(); // Fill result (All operators)
			stack_operators.pop();// Get out top of operators stack
		}
		for (int i = 0; i < size; j++, i++, k--) // Fill Lexemas table (for this experession)
		{
			tables->Lextable.table[j].lexema = result[i].lexema;
			tables->Lextable.table[j].idxTI = result[i].idxTI;
			tables->Lextable.table[j].sn = result[i].sn; //нормер стр в инсх тект
			tables->IDtable.table[result[i].idxTI].idxfirstLE;
		}
		for (; k > 0; k--, j++)	// Subtitute items which deleted in the process of creating Polish notation

		{
			tables->Lextable.table[j].lexema = NULL;
			tables->Lextable.table[j].idxTI = NULL;
		}
		size = 0;
		build = true;
	}
	return build;
}