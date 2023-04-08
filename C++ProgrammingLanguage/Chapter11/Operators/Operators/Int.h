//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
class CInt
{
	private:
		int														MValue;

	public:
		CInt operator+(CInt& RightOperand);
		CInt operator-(CInt& RightOperand);

	public:
		// !!! Moze byt definovany IBA ako MEMBER OPERATOR.
		CInt& operator=(const CInt& RightOperand);

	public:
		// !!! PREFIX OPERATOR.
		CInt& operator++(void);
		// !!! POSTFIX OPERATOR.
		CInt& operator++(int DummyOperand);

	public:
		void Print(void);
		inline int GetValue(void) const {return(MValue);}
		inline void SetValue(int Value) {MValue=Value;}

	public:
		CInt(void);
		CInt(int Value);
		CInt(const CInt& Object);
		virtual ~CInt(void);
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// GLOBALNE OPERATORY.
CInt operator-(CInt& LeftOperand, CInt& RightOperand);
CInt operator-(CInt& LeftOperand, int RightOperand);
// !!! OPERATOR[] MUSI BYT VZDY MEMBER OPERATOR.
//CInt operator[](CInt& LeftOperand, int RightOperand);
CInt operator*(int LeftOperand, CInt& RightOperand);
// !!! PREFIX OPERATOR.
CInt& operator--(CInt& LeftOperand);
// !!! POSTFIX OPERATOR.
CInt& operator--(CInt& LeftOperand, int DummyOperand);
//-------------------------------------------------------------------------------------------------------