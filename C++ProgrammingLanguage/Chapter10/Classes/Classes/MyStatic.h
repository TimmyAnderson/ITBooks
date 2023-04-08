//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "MyText.h"
//-------------------------------------------------------------------------------------------------------
class CMyStatic
{
	private:
		static const CMyText									MStaticConstName;
		static CMyText											MStaticName;

	public:
		static void PrintStatic(void);

	public:
		void PrintNonStatic(void);

	public:
		CMyStatic(void);
		virtual ~CMyStatic(void);
};
//-------------------------------------------------------------------------------------------------------