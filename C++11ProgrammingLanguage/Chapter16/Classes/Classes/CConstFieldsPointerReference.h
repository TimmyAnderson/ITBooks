//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CConstFieldsField.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CConstFieldsPointerReference final
{
//-----------------------------------------------------------------------------
	private:
		CConstFieldsField										MValueField;
		CConstFieldsField*										MPointerField;
		CConstFieldsField&										MReferenceField;

	public:
		int GetValueField(void) const noexcept
		{
			return(MValueField.GetField());
		}

		int GetPointerField(void) const noexcept
		{
			return(MPointerField->GetField());
		}

		int GetReferenceField(void) const noexcept
		{
			return(MReferenceField.GetField());
		}

		void SetValues(int PointerValue, int ReferenceValue) const
		{
			// !!! CONST METHODS NEMOZU modifikovat FIELDS.
			//MValueField.SetField(100);

			// !!!!! CONST METHODS MOZU volat NON-CONST METHODS POINTER FIELDS.
			MPointerField->SetField(PointerValue);

			// !!!!! CONST METHODS MOZU volat NON-CONST METHODS REFERENCE FIELDS.
			MReferenceField.SetField(ReferenceValue);
		}

	public:
		CConstFieldsPointerReference(int Value, CConstFieldsField* PointerField, CConstFieldsField& ReferenceField)
			: MValueField(Value), MPointerField(PointerField), MReferenceField(ReferenceField)
		{
		}

		~CConstFieldsPointerReference(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------