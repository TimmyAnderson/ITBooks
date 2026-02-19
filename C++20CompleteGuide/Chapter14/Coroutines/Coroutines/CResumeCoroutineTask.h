//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CResumeCoroutineTask final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		struct SPromiseType;

	public:
		// !!! COROUTINE OBJECT musi definovat TYPE s NAME [promise_type].
		using													promise_type=SPromiseType;

	private:
		// !!! FIELD reprezentuje COROUTINE HANDLE, ktorym reprezentuje COROUTINE. COROUTINE HANDLE umoznuje ovladat beh COROUTINES.
		std::coroutine_handle<SPromiseType>						MHandle;

	public:
		CResumeCoroutineTask& operator=(const CResumeCoroutineTask&)=delete;
		CResumeCoroutineTask& operator=(CResumeCoroutineTask&& Other) noexcept=delete;

	public:
		// !!! CUSTOM METHOD vykonava RESUME danej COROUTINE a zaroven vracia informaciu ci COROUTINE uz skoncila.
		bool Resume(void) const;

	public:
		CResumeCoroutineTask(std::coroutine_handle<SPromiseType> Handle);
		CResumeCoroutineTask(const CResumeCoroutineTask&)=delete;
		CResumeCoroutineTask(CResumeCoroutineTask&& Other) noexcept=delete;
		~CResumeCoroutineTask(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct CResumeCoroutineTask::SPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		CResumeCoroutineTask get_return_object(void);
		std::suspend_always initial_suspend(void);
		void unhandled_exception(void);
		void return_void(void);
		std::suspend_always final_suspend(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------