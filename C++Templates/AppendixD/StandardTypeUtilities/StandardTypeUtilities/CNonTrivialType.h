//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS NIE JE TRIVIAL, pretoze ma definovany CONSTRUCTOR a ma takisto definovany VIRTUAL DESTRUCTOR.
class CNonTrivialType final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MField1;
		double													MField2;

	public:
		int GetField1(void) const;
		double GetField2(void) const;
		void SetField1(int Field1);
		void SetField2(double Field2);

	public:
		void SomeMethod(void);

	public:
		CNonTrivialType(int Field1, double Field2);
		virtual ~CNonTrivialType(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------