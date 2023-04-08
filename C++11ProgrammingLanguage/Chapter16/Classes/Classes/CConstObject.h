//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CConstObject final
{
//-----------------------------------------------------------------------------
	private:
		const int												MConstField;
		int														MNonConstField;

	public:
		int GetConstField(void) const noexcept
		{
			return(MConstField);
		}

		void SetNonConstField(int Value) noexcept
		{
			MNonConstField=Value;
		}

		int GetNonConstField(void) const noexcept
		{
			// CONST METHODS NESMU modifikovat FIELDS.
			//MNonConstField++;

			return(MNonConstField);
		}

	public:
		void Method(void)
		{
			std::wcout << L"NON-CONST METHOD CALLED !" << std::endl;
		}

		void Method(void) const
		{
			std::wcout << L"CONST METHOD CALLED !" << std::endl;
		}

	public:
		CConstObject(int ConstField, int NonConstField)
			: MConstField(ConstField), MNonConstField(NonConstField)
		{
		}

		~CConstObject(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------