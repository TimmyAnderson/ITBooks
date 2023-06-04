//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ostream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CNonMemberOperator3;
// !!!!! DECLARATION NON-MEMEBER OPERATOR.
template<typename TType>
std::wostream& operator<<(std::wostream& Stream, const CNonMemberOperator3<TType>& Value);
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CNonMemberOperator3
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		// !!!!! DECLARATION NON-MEMEBER OPERATOR TEMPLATE SPECIALIZATION.
		// !!!!! OPERATOR<< je NON-MEMBER METHOD, ktora je definovana MIMO SCOPE TEMPLATE CLASS.
		// !!!!! KEYWORD [friend] je NUTNE pouzit, aby bolo zrejme, ze je to NON-MEMBER METHOD, a nie MEMBER METHOD. A MEMBER OPERATOR<< ma iba 1 PARAMETER, a nie 2.
		// !!!!! METHOD je v skutocnosti TEMPLATE SPECIALIZATION pre TEMPLATE FUNCTION, ktora bola deklarovana vyssie.
		friend std::wostream& operator<< <TType>(std::wostream& Stream, const CNonMemberOperator3<TType>& Value);

	public:
		const TType& Get(void) const noexcept
		{
			return(MValue);
		}

	public:
		CNonMemberOperator3(const TType& Value)
			: MValue(Value)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DEFINITION NON-MEMEBER OPERATOR TEMPLATE SPECIALIZATION.
template<typename TType>
std::wostream& operator<<(std::wostream& Stream, const CNonMemberOperator3<TType>& Value)
{
	Stream << Value.MValue;

	return(Stream);
}
//----------------------------------------------------------------------------------------------------------------------