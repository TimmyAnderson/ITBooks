//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CNonUniqueObjectRepresentations final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MField1;
		// !!!!! FIELD TYPE [float] sposobi, ze TYPE NEMA UNIQUE OBJECT REPRESENTATION.
		float													MField2;

	public:
		int GetField1(void) const;
		float GetField2(void) const;
		void SetField1(int Field1);
		void SetField2(float Field2);

	public:
		void SomeMethod(void);

	public:
		// !!! TYPE s DEFAULT CONSTRUCTOR JE TRIVIALLY COPYABLE.
		CNonUniqueObjectRepresentations(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------