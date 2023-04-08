//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
// !!! CLASS obsahujuca informacie pre implementaciu PARAMETRICKEHO MANIPULATOR.
class CCustomManipulatorWriteNCharacters
{
//-----------------------------------------------------------------------------
	private:
		int														MNumberOfCharacters;
		wchar_t													MFillCharacter;

	public:
		int GetNumberOfCharacters(void) const noexcept
		{
			return(MNumberOfCharacters);
		}

		wchar_t GetFillCharacter(void) const noexcept
		{
			return(MFillCharacter);
		}

	public:
		CCustomManipulatorWriteNCharacters(int NumberOfCharacters, wchar_t FillCharacter)
			: MNumberOfCharacters(NumberOfCharacters), MFillCharacter(FillCharacter)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! Pre implementaciu CUSTOM MANIPULATORS je nutne implementovat OPERATOR<<, alebo OPERATOR>>.
template<typename TCharacter, typename TTraits>
inline std::basic_ostream<TCharacter,TTraits>& operator<<(std::basic_ostream<TCharacter,TTraits>& Stream, const CCustomManipulatorWriteNCharacters& Manipulator)
{
	for(int Index=0;Index<Manipulator.GetNumberOfCharacters();Index++)
	{
		Stream.put(Manipulator.GetFillCharacter());
	}

	return(Stream);
}
//-----------------------------------------------------------------------------