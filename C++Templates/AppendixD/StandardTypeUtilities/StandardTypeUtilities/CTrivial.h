//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CTrivial final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MField;

	public:
		int GetField(void) const;
		void SetField(int Field);

	public:
		void SomeMethod(void);

	/*
	public:
		// !!! TYPE s DEFAULT CONSTRUCTOR NIE JE TRIVIAL.
		CTrivial(void);
		// !!! TYPE s DESTRUCTOR NIE JE TRIVIAL.
		~CTrivial(void) noexcept;
	*/
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------