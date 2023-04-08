//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
class CNonVirtualClass
{
	private:
		int														MSomeInt;

	public:
		// !!! CLASS je NON-VIRTUAL, lebo NEOBSAHUJE ANI 1 VIRTUAL METHOD.
		void Print(void);

	public:
		CNonVirtualClass(void);
		~CNonVirtualClass(void);
};
//-------------------------------------------------------------------------------------------------------