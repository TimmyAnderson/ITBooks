//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
// !!! PRVA FUNCTION DECLARATION.
void LookUpArgumentDependentFriendFunction1(void);
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CLookUpArgumentDependentFriend final
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! OPAKOVANA FUNCTION DECLARATION.
	friend void LookUpArgumentDependentFriendFunction1(void);
	// !!!!! PRVA FUNCTION DECLARATION.
	friend void LookUpArgumentDependentFriendFunction2(void);
	// !!!!! PRVA FUNCTION DECLARATION a zaroven aj FUNCTION DEFINITION.
	friend void LookUpArgumentDependentFriendFunction3(const CLookUpArgumentDependentFriend<TType>& Field)
	{
		std::wcout << L"LOOKUP ARGUMENT DEPENDENT FRIEND FUNCTION 3 CALLED. VALUE [" << Field.GetField() << L"]." << std::endl;
	}

	private:
		TType													MField;

	public:
		const TType& GetField(void) const noexcept;

	public:
		CLookUpArgumentDependentFriend(const TType& Field);
		virtual ~CLookUpArgumentDependentFriend(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CLookUpArgumentDependentFriend<TType>::CLookUpArgumentDependentFriend(const TType& Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CLookUpArgumentDependentFriend<TType>::~CLookUpArgumentDependentFriend(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CLookUpArgumentDependentFriend<TType>::GetField(void) const noexcept
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------