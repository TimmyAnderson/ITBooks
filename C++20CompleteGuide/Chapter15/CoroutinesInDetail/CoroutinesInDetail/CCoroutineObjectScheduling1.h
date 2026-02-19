//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <iostream>
#include <map>
#include "ECoroutineSchedulingMode.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CCoroutineObjectSchedulingScheduler1;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectSchedulingPromiseType1 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!! Ulozi sa SCHEDULER OBJECT, aby bol pristupny pre AWAITER, ktory ma pristup k PROMISE TYPE OBJECT.
		CCoroutineObjectSchedulingScheduler1*					MScheduler;

	public:
		TCoroutineObject get_return_object(void);
		std::suspend_always initial_suspend(void);
		void unhandled_exception(void);
		void return_void(void);
		std::suspend_always final_suspend(void) noexcept;

	public:
		CCoroutineObjectSchedulingScheduler1* GetScheduler(void) noexcept;
		void SetScheduler(CCoroutineObjectSchedulingScheduler1* Scheduler) noexcept;

	public:
		SCoroutineObjectSchedulingPromiseType1(void);
		~SCoroutineObjectSchedulingPromiseType1(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectSchedulingPromiseType1<TCoroutineObject>::SCoroutineObjectSchedulingPromiseType1(void)
	: MScheduler(nullptr)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectSchedulingPromiseType1<TCoroutineObject>::~SCoroutineObjectSchedulingPromiseType1(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
TCoroutineObject SCoroutineObjectSchedulingPromiseType1<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectSchedulingPromiseType1>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectSchedulingPromiseType1<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectSchedulingPromiseType1<TCoroutineObject>::unhandled_exception(void)
{
	std::wcout << L"!!!!! UNHANDLED EXCEPTION DETECTED. !!!!!" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectSchedulingPromiseType1<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectSchedulingPromiseType1<TCoroutineObject>::SCoroutineObjectSchedulingPromiseType1::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
CCoroutineObjectSchedulingScheduler1* SCoroutineObjectSchedulingPromiseType1<TCoroutineObject>::GetScheduler(void) noexcept
{
	return(MScheduler);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectSchedulingPromiseType1<TCoroutineObject>::SetScheduler(CCoroutineObjectSchedulingScheduler1* Scheduler) noexcept
{
	MScheduler=Scheduler;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COROUTINE OBJECT NEIMPLEMENTUJE COROUTINE OBJECT INTERFACE, pretoze ten implementuje CLASS [CoroutineObjectSchedulingScheduler], ktora robi manazment viacerych COROUTINES.
class [[nodiscard]] CCoroutineObjectScheduling1 final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectSchedulingPromiseType1<CCoroutineObjectScheduling1>;

	private:
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectScheduling1& operator=(const CCoroutineObjectScheduling1&)=delete;
		CCoroutineObjectScheduling1& operator=(CCoroutineObjectScheduling1&& Other) noexcept;

	public:
		std::coroutine_handle<promise_type> GetHandle(void) noexcept;

	public:
		CCoroutineObjectScheduling1(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectScheduling1(const CCoroutineObjectScheduling1&)=delete;
		CCoroutineObjectScheduling1(CCoroutineObjectScheduling1&& Other) noexcept;
		~CCoroutineObjectScheduling1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje CUSTOM AWAITER.
class CCoroutineObjectSchedulingAwaiter1 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		ECoroutineSchedulingMode								MSchedulingMode;

	public:
		bool await_ready(void) const noexcept;
		void await_suspend(std::coroutine_handle<CCoroutineObjectScheduling1::promise_type> CoroutineHandle) noexcept;
		void await_resume(void) const noexcept;

	public:
		CCoroutineObjectSchedulingAwaiter1(ECoroutineSchedulingMode SchedulingMode);
		~CCoroutineObjectSchedulingAwaiter1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CCoroutineObjectSchedulingScheduler1 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::multimap<int,CCoroutineObjectScheduling1>			MCoroutineObjects;

	public:
		// !!! METHOD ulozi COROUTINE OBJECT do MULTIMAP.
		void StartCoroutine(CCoroutineObjectScheduling1&& CoroutineObject);
		// !!! METHOD vykona RESUME MOST PRIOR COROUTINE OBJECT zo vsetkych COROUTINE OBJECTS v MULTIMAP.
		bool ResumeCoroutine(void);
		// !!! METHOD nastavuje PRIORITY daneho COROUTINE OBJECT.
		bool ChangeCoroutinePriority(std::coroutine_handle<CCoroutineObjectScheduling1::promise_type> CoroutineHandle, ECoroutineSchedulingMode SchedulingMode);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------