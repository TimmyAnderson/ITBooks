//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
//----------------------------------------------------------------------------------------------------------------------
constexpr size_t												MY_ARRAY_SIZE=5;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! ARRAY bez BOUNDS je INCOMPLETE TYPE.
extern int														MyArray[];
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tu je TYPE [ECompleteVsIncompleteTypes] este INCOMPLETE TYPE, pretoze je iba DECLARED.
enum class ECompleteVsIncompleteTypes;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tu je uz TYPE [ECompleteVsIncompleteTypes] COMPLETE TYPE, pretoze je DEFINED.
enum class ECompleteVsIncompleteTypes
{
//----------------------------------------------------------------------------------------------------------------------
	E_ONE=1,
	E_TWO=1,
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tu je TYPE [CCompleteVsIncompleteTypes] este INCOMPLETE TYPE, pretoze je iba DECLARED.
class CCompleteVsIncompleteTypes;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Toto je POINTER na INCOMPLETE TYPE, ktory je automaticky INCOMPLETE TYPE.
extern const CCompleteVsIncompleteTypes*						PointerToCompleteVsIncompleteTypes;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Toto je ARRAY na INCOMPLETE TYPE, ktory je automaticky INCOMPLETE TYPE.
extern CCompleteVsIncompleteTypes								ArrayToCompleteVsIncompleteTypes[3];
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tu je uz TYPE [CCompleteVsIncompleteTypes] COMPLETE TYPE, pretoze je DEFINED.
class CCompleteVsIncompleteTypes final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MField;

	public:
		void Print(void) const;

	public:
		CCompleteVsIncompleteTypes(int Field);
		virtual ~CCompleteVsIncompleteTypes(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------