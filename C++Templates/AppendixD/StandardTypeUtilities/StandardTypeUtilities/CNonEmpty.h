//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CNonEmpty final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MField;

	public:
		int GetField(void) const;

	public:
		CNonEmpty(int Value);
		~CNonEmpty(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------