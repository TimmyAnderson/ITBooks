//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CStandardLayout final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MField;

	public:
		int GetField(void) const;
		void SetField(int Field);

	public:
		void SomeMethod(void);

	public:
		CStandardLayout(void);
		~CStandardLayout(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------