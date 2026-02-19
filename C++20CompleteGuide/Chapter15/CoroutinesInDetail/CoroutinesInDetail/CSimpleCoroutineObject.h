//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <exception>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SSimpleCoroutineObjectPromiseType final
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
TCoroutineObject SSimpleCoroutineObjectPromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle<SSimpleCoroutineObjectPromiseType>	Handle=std::coroutine_handle<SSimpleCoroutineObjectPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SSimpleCoroutineObjectPromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SSimpleCoroutineObjectPromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::terminate();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SSimpleCoroutineObjectPromiseType<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SSimpleCoroutineObjectPromiseType<TCoroutineObject>::SSimpleCoroutineObjectPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CSimpleCoroutineObject final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SSimpleCoroutineObjectPromiseType<CSimpleCoroutineObject>;

	private:
		std::coroutine_handle<SSimpleCoroutineObjectPromiseType<CSimpleCoroutineObject>>	MHandle;

	public:
		CSimpleCoroutineObject& operator=(const CSimpleCoroutineObject&)=delete;
		CSimpleCoroutineObject& operator=(CSimpleCoroutineObject&& Other) noexcept;

	public:
		bool Resume(void) const;

	public:
		CSimpleCoroutineObject(std::coroutine_handle<SSimpleCoroutineObjectPromiseType<CSimpleCoroutineObject>> Handle);
		CSimpleCoroutineObject(const CSimpleCoroutineObject&)=delete;
		CSimpleCoroutineObject(CSimpleCoroutineObject&& Other) noexcept;
		~CSimpleCoroutineObject(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------