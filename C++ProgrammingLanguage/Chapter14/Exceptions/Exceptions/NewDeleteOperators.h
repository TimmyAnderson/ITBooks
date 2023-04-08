//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
class CNewDeleteOperators
{
	public:
		void* operator new(size_t Size);
		void operator delete(void* Object);

	public:
		CNewDeleteOperators(void);
		virtual ~CNewDeleteOperators(void);
};
//-------------------------------------------------------------------------------------------------------