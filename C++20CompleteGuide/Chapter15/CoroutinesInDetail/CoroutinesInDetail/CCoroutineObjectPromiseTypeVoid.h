//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <exception>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectPromiseTypeVoidPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		TCoroutineObject get_return_object(void);
		std::suspend_always initial_suspend(void);
		void unhandled_exception(void);
		void return_void(void);
		std::suspend_always final_suspend(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
TCoroutineObject SCoroutineObjectPromiseTypeVoidPromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle<SCoroutineObjectPromiseTypeVoidPromiseType>	Handle=std::coroutine_handle<SCoroutineObjectPromiseTypeVoidPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectPromiseTypeVoidPromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectPromiseTypeVoidPromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::terminate();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectPromiseTypeVoidPromiseType<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectPromiseTypeVoidPromiseType<TCoroutineObject>::SCoroutineObjectPromiseTypeVoidPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CCoroutineObjectPromiseTypeVoid final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectPromiseTypeVoidPromiseType<CCoroutineObjectPromiseTypeVoid>;

	private:
		// !!! Ak METHOD [TPromiseType& promise(void) const] nie je potrebna, je mozne pouzit TEMPLATE CLASS SPECIALIZATION [coroutine_handle<void>].
		std::coroutine_handle<void>								MHandle;

	public:
		CCoroutineObjectPromiseTypeVoid& operator=(const CCoroutineObjectPromiseTypeVoid&)=delete;
		CCoroutineObjectPromiseTypeVoid& operator=(CCoroutineObjectPromiseTypeVoid&& Other) noexcept;

	public:
		bool Resume(void) const;

	public:
		CCoroutineObjectPromiseTypeVoid(std::coroutine_handle<void> Handle);
		CCoroutineObjectPromiseTypeVoid(const CCoroutineObjectPromiseTypeVoid&)=delete;
		CCoroutineObjectPromiseTypeVoid(CCoroutineObjectPromiseTypeVoid&& Other) noexcept;
		~CCoroutineObjectPromiseTypeVoid(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------