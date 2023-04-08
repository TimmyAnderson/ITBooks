//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
class CPrimitiveTypeDereferencing
{
	private:
		// !!!!! Vracia POINTER na PRIMITIVNY TYP na ktory vsak NEMA ZIADNE MEMBERS a tak SYTAX [A->B] NIE JE MOZNE POUZIT a jedine pouzitie je syntax [A.operator->()].
		int*													MPointer;

	public:
		int* operator->(void);

	public:
		CPrimitiveTypeDereferencing(int* Pointer);
		virtual ~CPrimitiveTypeDereferencing(void);
};
//-------------------------------------------------------------------------------------------------------