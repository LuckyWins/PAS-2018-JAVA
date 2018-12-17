#include "pch.h"
#include "In.h"
#include "LexAnalize.h"
#include "Log.h"
#include "Error.h"
#include "Parm.h"
#include "IT.h"
#include "LT.h"
#include "FST.h"
#include "Generation.h"
#include "MFST.h"
#include "GRB.h"
#include "PN.h"

int _tmain(int argc, wchar_t *argv[])
{
	setlocale(LC_CTYPE, "Russian");
	Log::LOG log;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv); // Get options
		log = Log::getstream(parm.log); // Open thread
		Log::writeLog(log); // Fill log (date, time)
		Log::writeParm(log, parm); // Fill log (using options)
		In::IN in = In::getin(log.stream, parm.in); // Start input symbols control
		in.tokens = In::parsOfToken(in.tokens, in.text, in.code); // Get words from the read file for Lexical analyzer
		Lexer::LEX tables = Lexer::Fill_LTIT(in, log, parm); // Start Lexical analyzer
		MFST::Mfst mfst(tables, GRB::getGreibach()); // Initialization Syntax analyzer

		if (Log::Error) // If no errors
		{
			Log::writeIn(log, in); // Fill log (file read info)
			Log::writeLexTable(log, tables.Lextable); // Fill log (Tokens table)
			Log::writeIDtable(log, tables.IDtable); // Fill log (Identifiers table)
			if (parm.ITtable == true)
			{
				writeIDTableConsole(log, tables.IDtable); // Fill console (Identifiers table)
			}
			if (parm.LTtable == true)
			{
				Log::writeLexTableConsole(log, tables.Lextable); // Fill console (Lexeme table)
			}
			Log::writeIntermediateCode(log, tables.Lextable); // Fill log (Intermediate code)
		}
		if (Log::Error)
		{
			MFST_TRACE_START(log); // Head
			mfst.start(log); // Start Syntax alalyzer
			mfst.savededucation(); // Save output rules
			mfst.printrules(log); // Fill log (Parse tree)
		}
		if (Log::flaw == false)
		{
			Generation(tables.Lextable, in.tokens);// Generation a Java code file
			PN polishNatation;
			if (polishNatation.CreatePolishNotation(&tables))
			{
				*log.stream << endl << endl << "Polish Notation";
				Log::writeIntermediateCode(log, tables.Lextable);
			}
		}
		Log::Close(log); // Close thread
	}
	catch (Error::ERROR e)
	{
		Log::writeError(log.stream, e); // Errors
	}
}