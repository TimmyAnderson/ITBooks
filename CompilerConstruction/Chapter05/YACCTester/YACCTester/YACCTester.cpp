#include <stdio.h>
#include <conio.h>
#include "YACC\Expressions.h"
//-------------------------------------------------------------------------------------------------------
// Funkcia importovana z Expressions.c, ktora spusta PARSER.
extern "C" int yyparse(void);
extern "C" int yydebug;
//-------------------------------------------------------------------------------------------------------
void wmain(int argc, wchar_t **argv)
{
	wprintf_s(L"Parsing STARTED !\n");

	// Zapne TRACE vypisy z YACC. Funguje vsak iba ak v Expressions.c je YYDEBUG nastaveny na 1.
	//yydebug=1;

	yyparse();

	wprintf_s(L"Parsing FINISHED !\n");

	_getch();
}
//-------------------------------------------------------------------------------------------------------