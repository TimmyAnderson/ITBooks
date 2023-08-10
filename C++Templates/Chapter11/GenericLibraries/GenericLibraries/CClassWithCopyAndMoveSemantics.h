//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CClassWithCopyAndMoveSemantics final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MField1;
		double													MField2;

	public:
		CClassWithCopyAndMoveSemantics& operator=(const CClassWithCopyAndMoveSemantics& Other);
		CClassWithCopyAndMoveSemantics& operator=(CClassWithCopyAndMoveSemantics&& Other) noexcept;

	public:
		int GetField1(void) const noexcept;
		double GetField2(void) const noexcept;

	public:
		CClassWithCopyAndMoveSemantics(void);
		CClassWithCopyAndMoveSemantics(int Field1, double Field2);
		CClassWithCopyAndMoveSemantics(const CClassWithCopyAndMoveSemantics& Other);
		CClassWithCopyAndMoveSemantics(CClassWithCopyAndMoveSemantics&& Other) noexcept;
		~CClassWithCopyAndMoveSemantics(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------