//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CUniqueObjectRepresentations final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MField1;
		int														MField2;

	public:
		int GetField1(void) const;
		int GetField2(void) const;
		void SetField1(int Field1);
		void SetField2(int Field2);

	public:
		void SomeMethod(void);

	public:
		// !!! TYPE s DEFAULT CONSTRUCTOR JE TRIVIALLY COPYABLE.
		CUniqueObjectRepresentations(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------