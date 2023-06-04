//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ostream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CNonMemberOperator2
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		// !!!!! DECLARATION NON-MEMEBER OPERATOR.
		// !!!!! OPERATOR<< je NON-MEMBER METHOD, ktora je definovana MIMO SCOPE TEMPLATE CLASS.
		// !!!!! KEYWORD [friend] je NUTNE pouzit, aby bolo zrejme, ze je to NON-MEMBER METHOD, a nie MEMBER METHOD. A MEMBER OPERATOR<< ma iba 1 PARAMETER, a nie 2.
		// !!!!! Kedze sa jedna o NON-MEMBER METHOD, je NUTNE DEFINOVAT SEPARATNY TEMPLATE PARAMETER, ktory sa lisi od TEMPLATE PARAMETERS CLASS.
		template<typename TTypeLocal>
		friend std::wostream& operator<<(std::wostream& Stream, const CNonMemberOperator2<TTypeLocal>& Value);

	public:
		const TType& Get(void) const noexcept
		{
			return(MValue);
		}

	public:
		CNonMemberOperator2(const TType& Value)
			: MValue(Value)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DEFINITION NON-MEMEBER OPERATOR.
template<typename TType>
std::wostream& operator<<(std::wostream& Stream, const CNonMemberOperator2<TType>& Value)
{
	Stream << Value.MValue;

	return(Stream);
}
//----------------------------------------------------------------------------------------------------------------------