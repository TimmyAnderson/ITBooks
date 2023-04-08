//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
class CIntArray
{
	private:
		int														MSize;
		int*													MArray;

	public:
		int operator[](int Index);

	public:
		void SetValue(int Index, int Value);
		inline int GetSize(void) const {return(MSize);}

	public:
		CIntArray(int Size);
		virtual ~CIntArray(void);
};
//-------------------------------------------------------------------------------------------------------