%{
#include <stdio.h>
#include <ctype.h>
/* Je tu nazov suboru, kde je EXPRESSION, ktory chcem parsovat. */
#include "..\SourceCodeFilename.h"
%}

%token NUMBER

/* V UNION definujem VSETKY TYPY, ktore mozu RULES vracat a dam im meno (Val, Op). */
/* !!! Ak zmenim hodnotu 'double' na 'int' musim nizsie vo funkciach i BNF ACTIONS zmenit '%lf' na '%d'. */
%union 
{
	double			Val;
	char			Op;
}

/* Jednotlivym menam v UNION priradim RULES BNF, cim urcim aky typ ma dany RULE vracat. */
/* !!! V tomto pripade budu 'EXP TERM FACTOR NUMBER' vracat DOUBLE a ADDOP bude vracat CHAR. */
%type <Val>			EXP TERM FACTOR NUMBER
%type <Op>			ADDOP

%%

COMMAND	:	EXP						{printf("!!!!! Value: [%lf] !\n",$1);}
		|	error					{printf("!!!!! INCORRECT EXPRESSION !!!!!\n");}
		;

EXP		:	EXP ADDOP TERM			{
										if ($2=='+')
											$$=$1+$3;
										else
											$$=$1-$3;
									}
		|	TERM					{$$=$1;}
		;

ADDOP	:	'+'						{$$='+'}
		|	'-'						{$$='-'}
		;

TERM	:	TERM '*' FACTOR			{$$=$1*$3;}
		|	TERM 					{printf("EMBEDDED ACTION - DIVISION !\n");}
			'/' FACTOR				{$$=$1/$4;}
		|	FACTOR					{$$=$1;}
		|	error					{$$=0;}
		;

FACTOR	:	NUMBER					{$$=$1;}
		|	'(' EXP ')'				{$$=$2;}
		;
%%
/*-----------------------------------------------------------------------------------------------------*/
FILE*				FP=NULL;
/*-----------------------------------------------------------------------------------------------------*/
/* Tuto rutinu zavola BISON aby vykonal SCANING. Musim ju preto doplnit do kodu. */
/* Rutina vracia bud NOVY ZNAK, alebo 0, ak sa jedna o koniec SOURCE CODE. */
int yylex(void)
{
	int				Char;

	if (FP==NULL)
	{
		errno_t		Error=fopen_s(&FP,Filename,"r");

		if (Error!=0)
		{
			printf("!!!!! Can't open FILE [%s], Error: [%d] !\n",Filename,Error);
			return(0);
		}
	}

	/* Ignorujem medzery. */
	while((Char=getc(FP))==' ')
		;

	printf("!!!!! Char: [%c] !\n",Char);

	/* Zistim ci sa jedna o TOKEN NUMBER a ak ano, tak vratim 'NUMBER' co je TOKEN deklarovany v .Y subore v DECLARATION casti. */
	if (isdigit(Char)!=0)
	{
		ungetc(Char,FP);
		fscanf_s(FP,"%lf",&yylval);

		/* Vratim TOKEN 'NUMBER'. */
		return(NUMBER);
	}

	/* Ak sa jedna o koniec suboru MUSIM VRATIT 0, aby PARSER vedel, ze ma skoncit. */
	if (Char==EOF)
	{
		fclose(FP);
		FP=NULL;

		/* Ukoncim SCANER. */
		return(0);
	}

	return(Char);
}
/*-----------------------------------------------------------------------------------------------------*/
/* Tuto rutinu zavola BISON pri vyskyte ERROR. Musim ju preto doplnit do kodu. */
int yyerror(char *S)
{
	/* Vypisem chybu na ERROR vystup. */
	fprintf(stderr,"!!!!! ERROR: [%s] !\n",S);
	return(0);
}
/*-----------------------------------------------------------------------------------------------------*/