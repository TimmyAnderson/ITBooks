//-------------------------------------------------------------------------------------------------------
#include "Unit1.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
// Deklaracia ODKAZU na premennu definovanu v Unit1.cpp.
extern int														Variable1;
//-------------------------------------------------------------------------------------------------------
// Mozem deklarovat i 2 CONSTANTS s ROVNAKYM MENOM v 2 ROZLICNYCH COMPILATION UNITS.
const int														CONST=33;
//-------------------------------------------------------------------------------------------------------
// !!! INLINE funkcia MUSI BYT DEFINOVANA v MODULE, kde je DEKLAROVANA.
//extern inline void Inline1(void);
//-------------------------------------------------------------------------------------------------------
// Trieda je definovana v 3 CPP suboroch, pricom v kazdom je definovana TROCHU ODLISNE.
class CStrangeClass
{
	public:
		wstring													TextInUnit2CPP;
};
//-------------------------------------------------------------------------------------------------------
void Unit2Print(void)
{
	wcout << L"Unit2Print():\n";
	wcout << L"Variable1: " << Variable1 << L" !\n";

	//Inline1();
}
//-------------------------------------------------------------------------------------------------------
inline void Inline2(void)
{
	wcout << L"Inline2() in Unit2.cpp !\n";
}
//-------------------------------------------------------------------------------------------------------
void Print2Const(void)
{
	wcout << L"Print2Const(): CONST - " << CONST << L" !\n";
}
//-------------------------------------------------------------------------------------------------------
void Print2CStrangeClass(CStrangeClass& StrangeClass)
{
	// !!! Pouziva sa LOKALNU VERZIA CLASS 'CStrangeClass'.
	wcout << L"Print2CStrangeClass(): " << StrangeClass.TextInUnit2CPP << L" !\n";
}
//-------------------------------------------------------------------------------------------------------