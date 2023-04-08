//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
class CVirtualClass
{
	private:
		int														MSomeInt;

	public:
		// !!! CLASS je VIRTUAL, lebo obsahuje aspon 1 VIRTUAL METHOD.
		virtual void Print(void);

	public:
		CVirtualClass(void);
		~CVirtualClass(void);
};
//-------------------------------------------------------------------------------------------------------