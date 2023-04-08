//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
class CExceptionTestType
{
	private:
		int														MValue;

	public:
		bool operator<(const CExceptionTestType& Other);
		CExceptionTestType& operator=(const CExceptionTestType& Other);

	public:
		int GetValue(void) const;

	public:
		CExceptionTestType(int Value);
		CExceptionTestType(const CExceptionTestType& Value);
		virtual ~CExceptionTestType(void);
};
//-------------------------------------------------------------------------------------------------------