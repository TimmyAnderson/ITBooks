//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
template<typename TType>
class CWrapper
{
//-------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		TType GetValue(void)
		{
			wprintf_s(L"METHOD CWrapper<TType>::GetValue() CALLED !\n");

			return(MValue);
		}

		void SetValue(TType Value)
		{
			wprintf_s(L"METHOD CWrapper<TType>::SetValue() CALLED !\n");

			MValue=Value;
		}

	public:
		CWrapper(TType Value)
			: MValue(Value)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION pre TYPE [void*].
template<>
class CWrapper<void*>
{
//-------------------------------------------------------------------------------------------------------
	private:
		void*													MValue;

	public:
		void* GetValue(void)
		{
			wprintf_s(L"METHOD CWrapper<void*>::GetValue() CALLED !\n");

			return(MValue);
		}

		void SetValue(void* Value)
		{
			wprintf_s(L"METHOD CWrapper<void*>::SetValue() CALLED !\n");

			MValue=Value;
		}

		bool IsNULL(void)
		{
			wprintf_s(L"METHOD CWrapper<void*>::IsNULL() CALLED !\n");

			if (MValue==nullptr)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}

	public:
		CWrapper(void* Value)
			: MValue(Value)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION pre TYPE [TType*].
// !!!!! TEMPLATE SPECIALIZATION dedi z TEMPLATE SPECIALIZATION [CWrapper<void*>] a tym padom NEMUSI definovat MEMBERS, pretoze tie zdedil z TEMPLATE SPECIALIZATION [CWrapper<void*>].
template<typename TType>
class CWrapper<TType*> : public CWrapper<void*>
{
//-------------------------------------------------------------------------------------------------------
	public:
		bool SpecialIsNULL(void)
		{
			wprintf_s(L"METHOD CWrapper<TType*>::SpecialIsNULL() CALLED !\n");

			if (GetValue()==nullptr)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}

	public:
		CWrapper(TType* Value)
			: CWrapper<void*>(Value)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------