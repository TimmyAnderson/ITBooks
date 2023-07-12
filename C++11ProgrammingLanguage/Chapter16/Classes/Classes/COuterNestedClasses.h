//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class COuterNestedClasses final
{
//-----------------------------------------------------------------------------
	public:
		class CNestedClass final
		{
//-----------------------------------------------------------------------------
			private:
				int												MNestedField;

			public:
				int GetNestedField(void) const;
				void PrintNestedField(void) const;
				void PrintOuterField(const COuterNestedClasses& Object) const;

			public:
				CNestedClass(int Value);
				~CNestedClass(void);
//-----------------------------------------------------------------------------
		};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	private:
		int														MOuterField;

	public:
		void PrintNestedField(const CNestedClass& Object) const;
		void PrintOuterField(void) const;

	public:
		COuterNestedClasses(int Value);
		~COuterNestedClasses(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------