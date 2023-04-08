//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
class CIntExplicit
{
	private:
		int														MValue;

	public:
		void Print(void);

	public:
		// !!! Pouziva EXPLICITNE CONSTRUCTORS.
		CIntExplicit(void);
		explicit CIntExplicit(int Value);
		explicit CIntExplicit(const CIntExplicit& Value);
		virtual ~CIntExplicit(void);
};
//-------------------------------------------------------------------------------------------------------