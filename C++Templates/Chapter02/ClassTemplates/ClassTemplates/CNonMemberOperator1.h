//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ostream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CNonMemberOperator1
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		// !!!!! DECLARATION a DEFINITION NON-MEMEBER OPERATOR.
		// !!!!! OPERATOR<< je NON-MEMBER METHOD, ktora je vsak definovana v SCOPE TEMPLATE CLASS.
		// !!!!! KEYWORD [friend] je NUTNE pouzit, aby bolo zrejme, ze je to NON-MEMBER METHOD, a nie MEMBER METHOD. A MEMBER OPERATOR<< ma iba 1 PARAMETER, a nie 2.
		friend std::wostream& operator<<(std::wostream& Stream, const CNonMemberOperator1<TType>& Value)
		{
			Stream << Value.MValue;

			return(Stream);
		}

	public:
		const TType& Get(void) const noexcept
		{
			return(MValue);
		}

	public:
		CNonMemberOperator1(const TType& Value)
			: MValue(Value)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------