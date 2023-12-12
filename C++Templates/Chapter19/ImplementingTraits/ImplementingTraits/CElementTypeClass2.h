//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS MA vytiahnuty ako USING TYPE svojho FIELD co zjednodusuje vytvaranie GENERIC ALGORITHMS.
class CElementTypeClass2 final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													FieldType=int;

	private:
		FieldType												MValue;

	public:
		FieldType GetValue(void) const noexcept;

	public:
		CElementTypeClass2(FieldType Value);
		virtual ~CElementTypeClass2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------