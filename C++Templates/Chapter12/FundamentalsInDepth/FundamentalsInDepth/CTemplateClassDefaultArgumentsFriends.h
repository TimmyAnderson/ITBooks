//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateClassDefaultArgumentsFriends final
{
//----------------------------------------------------------------------------------------------------------------------
	/*
	// !!!!! COMPILER hodi ERROR, pretoze TEMPLATE CLASS FRIEND CLASS DECLARATIONS NESMU mat DEFAULT TEMPLATE ARGUMENTS.
	template<typename TLocalType1, typename TLocalType2=int>
	friend class CTemplateClassDefaultArgumentsFriendsFriend;
	*/

	template<typename TLocalType1, typename TLocalType2>
	friend class CTemplateClassDefaultArgumentsFriendsFriend;

	// !!!!! TEMPLATE CLASS FRIEND FUNCTION DECLARATION.
	// !!!!! COMPILER hodi ERROR, pretoze TEMPLATE CLASS FRIEND FUNCTION DECLARATIONS NESMU mat DEFAULT TEMPLATE ARGUMENTS.
	//template<typename TLocalType1, typename TLocalType2=int>
	template<typename TLocalType1, typename TLocalType2>
	friend void FriendPrint1(const CTemplateClassDefaultArgumentsFriends<TLocalType1,TLocalType2>& Object);

	// !!!!! TEMPLATE CLASS FRIEND FUNCTION DEFINITION MOZE mat DEFAULT TEMPLATE ARGUMENTS.
	template<typename TLocalType1, typename TLocalType2=int>
	friend void FriendPrint2(const CTemplateClassDefaultArgumentsFriends<TLocalType1,TLocalType2>& Object)
	{
		std::wcout << L"FRIEND FUNCTION 2 - FIELD 1 [" << Object.MField1 << L"] FIELD 2 [" << Object.MField2 << L"]." << std::endl;
	}

	private:
		TType1													MField1;
		TType2													MField2;

	public:
		const TType1& GetField1(void) const noexcept;
		const TType2& GetField2(void) const noexcept;

	public:
		CTemplateClassDefaultArgumentsFriends(TType1 Field1, TType2 Field2);
		virtual ~CTemplateClassDefaultArgumentsFriends(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDefaultArgumentsFriends<TType1,TType2>::CTemplateClassDefaultArgumentsFriends(TType1 Field1, TType2 Field2)
	: MField1(Field1), MField2(Field2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDefaultArgumentsFriends<TType1,TType2>::~CTemplateClassDefaultArgumentsFriends(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType1& CTemplateClassDefaultArgumentsFriends<TType1,TType2>::GetField1(void) const noexcept
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType2& CTemplateClassDefaultArgumentsFriends<TType1,TType2>::GetField2(void) const noexcept
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateClassDefaultArgumentsFriendsFriend final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CTemplateClassDefaultArgumentsFriends<TType1,TType2>	MField;

	public:
		void Print(void) const;

	public:
		CTemplateClassDefaultArgumentsFriendsFriend(CTemplateClassDefaultArgumentsFriends<TType1,TType2> Field);
		virtual ~CTemplateClassDefaultArgumentsFriendsFriend(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDefaultArgumentsFriendsFriend<TType1,TType2>::CTemplateClassDefaultArgumentsFriendsFriend(CTemplateClassDefaultArgumentsFriends<TType1,TType2> Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDefaultArgumentsFriendsFriend<TType1,TType2>::~CTemplateClassDefaultArgumentsFriendsFriend(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void CTemplateClassDefaultArgumentsFriendsFriend<TType1,TType2>::Print(void) const
{
	std::wcout << L"FRIEND CLASS - FIELD 1 [" << MField.MField1 << L"] FIELD 2 [" << MField.MField2 << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE CLASS FRIEND FUNCTION DEFINITION.
template<typename TLocalType1, typename TLocalType2>
void FriendPrint1(const CTemplateClassDefaultArgumentsFriends<TLocalType1,TLocalType2>& Object)
{
	std::wcout << L"FRIEND FUNCTION 1 - FIELD 1 [" << Object.MField1 << L"] FIELD 2 [" << Object.MField2 << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------