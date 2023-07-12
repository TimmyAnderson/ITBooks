//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CNonStandardLayout final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MField1;

	protected:
		// !!!!! STANDARD LAYOUT CLASS TYPE NESMIE mat FIELDS s roznymi ACCESS RIGHTS.
		int														MField2;

	public:
		int GetField1(void) const;
		void SetField1(int Field1);
		int GetField2(void) const;
		void SetField2(int Field2);

	public:
		void SomeMethod(void);

	public:
		// !!! TYPE s DEFAULT CONSTRUCTOR NIE JE TRIVIAL.
		CNonStandardLayout(void);
		// !!! TYPE s DESTRUCTOR NIE JE TRIVIAL.
		~CNonStandardLayout(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------