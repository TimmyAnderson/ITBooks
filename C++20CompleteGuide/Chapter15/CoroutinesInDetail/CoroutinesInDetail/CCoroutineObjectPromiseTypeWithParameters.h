//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <exception>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectPromiseTypeWithParametersPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MValue1;
		double													MValue2;

	public:
		TCoroutineObject get_return_object(void);
		std::suspend_always initial_suspend(void);
		void unhandled_exception(void);
		void return_void(void);
		std::suspend_always final_suspend(void) noexcept;

	public:
		// !!!!! Ak ma PROMISE TYPE NON-DEFAULT CONSTRUCTOR, musi sa pocet a poradie PARAMETER zhodovat s poctom a poradim COROUTINE PARAMETERS.
		SCoroutineObjectPromiseTypeWithParametersPromiseType(int Value1, double Value2);
		~SCoroutineObjectPromiseTypeWithParametersPromiseType(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectPromiseTypeWithParametersPromiseType<TCoroutineObject>::SCoroutineObjectPromiseTypeWithParametersPromiseType(int Value1, double Value2)
	: MValue1(Value1), MValue2(Value2)
{
	std::wcout << L"PROMISE TYPE CONSTRUCTOR CALLED. VALUE 1 [" << MValue1 << L"] VALUE 2 [" << MValue2 << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectPromiseTypeWithParametersPromiseType<TCoroutineObject>::~SCoroutineObjectPromiseTypeWithParametersPromiseType(void) noexcept
{
	std::wcout << L"PROMISE TYPE DESTRUCTOR CALLED. VALUE 1 [" << MValue1 << L"] VALUE 2 [" << MValue2 << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
TCoroutineObject SCoroutineObjectPromiseTypeWithParametersPromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectPromiseTypeWithParametersPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectPromiseTypeWithParametersPromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectPromiseTypeWithParametersPromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::terminate();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectPromiseTypeWithParametersPromiseType<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectPromiseTypeWithParametersPromiseType<TCoroutineObject>::SCoroutineObjectPromiseTypeWithParametersPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CCoroutineObjectPromiseTypeWithParameters final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectPromiseTypeWithParametersPromiseType<CCoroutineObjectPromiseTypeWithParameters>;

	private:
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectPromiseTypeWithParameters& operator=(const CCoroutineObjectPromiseTypeWithParameters&)=delete;
		CCoroutineObjectPromiseTypeWithParameters& operator=(CCoroutineObjectPromiseTypeWithParameters&& Other) noexcept;

	public:
		bool Resume(void) const;

	public:
		CCoroutineObjectPromiseTypeWithParameters(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectPromiseTypeWithParameters(const CCoroutineObjectPromiseTypeWithParameters&)=delete;
		CCoroutineObjectPromiseTypeWithParameters(CCoroutineObjectPromiseTypeWithParameters&& Other) noexcept;
		~CCoroutineObjectPromiseTypeWithParameters(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------