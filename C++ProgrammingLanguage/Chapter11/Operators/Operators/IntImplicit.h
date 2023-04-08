//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
class CIntImplicit
{
	private:
		int														MValue;

	public:
		void Print(void);

	public:
		CIntImplicit(void);
		CIntImplicit(int Value);
		CIntImplicit(const CIntImplicit& Value);
		virtual ~CIntImplicit(void);
};
//-------------------------------------------------------------------------------------------------------