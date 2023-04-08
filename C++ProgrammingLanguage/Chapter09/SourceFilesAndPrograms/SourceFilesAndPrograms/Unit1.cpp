//-------------------------------------------------------------------------------------------------------
#include "Unit1.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
// Deklaracia i DEFINICIA (priradenie pamate) premennej.
int																Variable1=50;
//-------------------------------------------------------------------------------------------------------
// Mozem deklarovat i 2 CONSTANTS s ROVNAKYM MENOM v 2 ROZLICNYCH COMPILATION UNITS.
const int														CONST=99;
// DEKLARACIA i DEFINICIA (priradenie pamate) EXTERNEJ CONST.
extern const int												EXTERN_CONST=10;
//-------------------------------------------------------------------------------------------------------
// Trieda je definovana v 3 CPP suboroch, pricom v kazdom je definovana TROCHU ODLISNE.
class CStrangeClass
{
	public:
		wstring													TextInUnit1CPP;
};
//-------------------------------------------------------------------------------------------------------
void Unit1Print(void)
{
	wcout << L"Unit1Print():\n";
	wcout << L"Variable1: " << Variable1 << L" !\n";
}
//-------------------------------------------------------------------------------------------------------
inline void Inline1(void)
{
	wcout << L"Inline1() in Unit1.cpp !\n";
}
//-------------------------------------------------------------------------------------------------------
inline void Inline2(void)
{
	wcout << L"Inline2() in Unit1.cpp !\n";
}
//-------------------------------------------------------------------------------------------------------
void Print1Const(void)
{
	wcout << L"Print1Const(): CONST - " << CONST << L" !\n";
}
//-------------------------------------------------------------------------------------------------------
void Print1CStrangeClass(CStrangeClass& StrangeClass)
{
	// !!! Pouziva sa LOKALNU VERZIA CLASS 'CStrangeClass'.
	wcout << L"Print1CStrangeClass(): " << StrangeClass.TextInUnit1CPP << L" !\n";
}
//-------------------------------------------------------------------------------------------------------