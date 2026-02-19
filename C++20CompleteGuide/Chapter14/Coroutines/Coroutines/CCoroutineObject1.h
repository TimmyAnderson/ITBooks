//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PROMISE TYPE je v COROUTINE OBJECT iba DEKLAROVANY a jeho definicia moze byt bud na konci definicie COROUTINE OBJECT, alebo externe mimo COROUTINE OBJECT.
class [[nodiscard]] CCoroutineObject1 final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		struct SCoroutineObject1PromiseType;

	public:
		// !!! COROUTINE OBJECT musi definovat TYPE s NAME [promise_type].
		using													promise_type=SCoroutineObject1PromiseType;

	private:
		// !!! FIELD reprezentuje COROUTINE HANDLE, ktorym reprezentuje COROUTINE. COROUTINE HANDLE umoznuje ovladat beh COROUTINES.
		std::coroutine_handle<SCoroutineObject1PromiseType>		MHandle;

	public:
		CCoroutineObject1& operator=(const CCoroutineObject1&)=delete;
		CCoroutineObject1& operator=(CCoroutineObject1&& Other) noexcept=delete;

	public:
		// !!! CUSTOM METHOD vykonava RESUME danej COROUTINE a zaroven vracia informaciu ci COROUTINE uz skoncila.
		bool Resume(void) const;

	public:
		CCoroutineObject1(std::coroutine_handle<SCoroutineObject1PromiseType> Handle);
		CCoroutineObject1(const CCoroutineObject1&)=delete;
		CCoroutineObject1(CCoroutineObject1&& Other) noexcept=delete;
		~CCoroutineObject1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct CCoroutineObject1::SCoroutineObject1PromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		CCoroutineObject1 get_return_object(void);
		std::suspend_always initial_suspend(void);
		void unhandled_exception(void);
		void return_void(void);
		std::suspend_always final_suspend(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------