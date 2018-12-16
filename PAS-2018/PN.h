#pragma once
#include "pch.h"
#include "LexAnalize.h"
#include "FST.h"

struct PN
{
	LT::Entry result[LT_MAXSIZE]; // ������ ��������������� ��������� � �������� �������
	int size = 0;
	enum { LH = '(', RH = ')', PLUS = '+', MINUS = '-', MULT = '*', DEV = '/', EQUAL = '=' };

	//std::vector <LT::Entry> result;	

	int prior(char operation); // ��������� ��������
	int search(int number, Lexer::LEX *tables); // ����� ������ ��������� � ������� ������
	bool CreatePolishNotation(Lexer::LEX *tables);
};