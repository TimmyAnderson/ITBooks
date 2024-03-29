//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
class CNoDefaultConstructor final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MField;

	public:
		friend std::wostream& operator<<(std::wostream& Stream, const CNoDefaultConstructor& Value);

	public:
		int GetField(void) const noexcept;

	public:
		explicit CNoDefaultConstructor(int Value);
		virtual ~CNoDefaultConstructor(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------