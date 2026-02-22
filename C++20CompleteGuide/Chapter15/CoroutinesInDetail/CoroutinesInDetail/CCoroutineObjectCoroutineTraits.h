//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectCoroutineTraitsPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!!!! Pri pouziti COROUTINE TRAITS, sa METHOD NIKDY NEVOLA, pretoze COROUTINE OBJECT je vytvorena priamo v CALLER FUNCTION.
		void get_return_object(void);
		std::suspend_always initial_suspend(void);
		void unhandled_exception(void);
		void return_void(void);
		std::suspend_always final_suspend(void) noexcept;

	public:
		// !!!!! Pri pouziti COROUTINE TRAITS, je nutne definovat CONSTRUCTOR, ktory ma rovnake PARAMETERS ako COROUTINE OBJECT.
		SCoroutineObjectCoroutineTraitsPromiseType(TCoroutineObject& CoroutineObject, int Parameter1, double Parameter2);
		~SCoroutineObjectCoroutineTraitsPromiseType(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectCoroutineTraitsPromiseType<TCoroutineObject>::SCoroutineObjectCoroutineTraitsPromiseType(TCoroutineObject& CoroutineObject, int Parameter1, double Parameter2)
{
	(void)Parameter1;
	(void)Parameter2;

	std::coroutine_handle<SCoroutineObjectCoroutineTraitsPromiseType<TCoroutineObject>>	Handle=std::coroutine_handle<SCoroutineObjectCoroutineTraitsPromiseType<TCoroutineObject>>::from_promise(*this);

	CoroutineObject.SetCoroutineHandle(Handle);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectCoroutineTraitsPromiseType<TCoroutineObject>::~SCoroutineObjectCoroutineTraitsPromiseType(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCoroutineTraitsPromiseType<TCoroutineObject>::get_return_object(void)
{
	// EMTPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectCoroutineTraitsPromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCoroutineTraitsPromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::wcout << L"!!!!! UNHANDLED EXCEPTION DETECTED. !!!!!" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCoroutineTraitsPromiseType<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectCoroutineTraitsPromiseType<TCoroutineObject>::SCoroutineObjectCoroutineTraitsPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CCoroutineObjectCoroutineTraits final
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! COROUTINE OBJECT nemusi mat definovany PUBLIC TYPE [promise_type].

	template<typename TCoroutineObject>
	friend struct SCoroutineObjectCoroutineTraitsPromiseType;

	private:
		using													TPromiseType=SCoroutineObjectCoroutineTraitsPromiseType<CCoroutineObjectCoroutineTraits>;

	private:
		std::coroutine_handle<TPromiseType>						MHandle;

	public:
		CCoroutineObjectCoroutineTraits& operator=(const CCoroutineObjectCoroutineTraits&)=delete;
		CCoroutineObjectCoroutineTraits& operator=(CCoroutineObjectCoroutineTraits&& Other) noexcept;

	private:
		void SetCoroutineHandle(std::coroutine_handle<TPromiseType> Handle);

	public:
		bool Resume(void) const;

	public:
		CCoroutineObjectCoroutineTraits(void);
		CCoroutineObjectCoroutineTraits(const CCoroutineObjectCoroutineTraits&)=delete;
		CCoroutineObjectCoroutineTraits(CCoroutineObjectCoroutineTraits&& Other) noexcept;
		~CCoroutineObjectCoroutineTraits(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Definuje sa TEMPLATE SPECIALIZATION COROUTINE TRAIT pre COROUTINE.
// !!!!! TEMPLATE SPECIALIZATION COROUTINE TRAIT musi ma tie iste RETURN VALUE TYPE a PARAMETERS, ako COROUTINE.
template<>
struct std::coroutine_traits<void,CCoroutineObjectCoroutineTraits&,int,double>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!!!! COROUTINE TRAIT MUSI definovat TYPE [promise_type].
		using													promise_type=SCoroutineObjectCoroutineTraitsPromiseType<CCoroutineObjectCoroutineTraits>;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------