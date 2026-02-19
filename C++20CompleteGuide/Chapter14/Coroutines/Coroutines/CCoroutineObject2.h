//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PROMISE TYPE je na zaciatku DEFINICIE COROUTINE OBJECT rono DEFINOVANY.
class [[nodiscard]] CCoroutineObject2 final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		struct SCoroutineObject2PromiseType final
		{
//----------------------------------------------------------------------------------------------------------------------
			public:
				CCoroutineObject2 get_return_object(void);
				std::suspend_always initial_suspend(void);
				void unhandled_exception(void);
				void return_void(void);
				std::suspend_always final_suspend(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
		};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

	public:
		// !!! COROUTINE OBJECT musi definovat TYPE s NAME [promise_type].
		using													promise_type=SCoroutineObject2PromiseType;

	private:
		// !!! FIELD reprezentuje COROUTINE HANDLE, ktorym reprezentuje COROUTINE. COROUTINE HANDLE umoznuje ovladat beh COROUTINES.
		std::coroutine_handle<SCoroutineObject2PromiseType>		MHandle;

	public:
		CCoroutineObject2& operator=(const CCoroutineObject2&)=delete;
		CCoroutineObject2& operator=(CCoroutineObject2&& Other) noexcept=delete;

	public:
		// !!! CUSTOM METHOD vykonava RESUME danej COROUTINE a zaroven vracia informaciu ci COROUTINE uz skoncila.
		bool Resume(void) const;

	public:
		CCoroutineObject2(std::coroutine_handle<SCoroutineObject2PromiseType> Handle);
		CCoroutineObject2(const CCoroutineObject2&)=delete;
		CCoroutineObject2(CCoroutineObject2&& Other) noexcept=delete;
		~CCoroutineObject2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------