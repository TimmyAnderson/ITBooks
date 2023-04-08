//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
class CBase
{
	public:
		virtual void PrintError(void);

	public:
		CBase(void);
		CBase(const CBase& Original);
		virtual ~CBase(void);
};
//-------------------------------------------------------------------------------------------------------