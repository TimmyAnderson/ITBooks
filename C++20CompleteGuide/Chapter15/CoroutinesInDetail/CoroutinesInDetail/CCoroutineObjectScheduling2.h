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
class CCoroutineObjectSchedulingScheduler2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectSchedulingPromiseType2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MID;
		// !!! Ulozi sa SCHEDULER OBJECT, aby bol pristupny pre AWAITER, ktory ma pristup k PROMISE TYPE OBJECT.
		CCoroutineObjectSchedulingScheduler2*					MScheduler;

	public:
		TCoroutineObject get_return_object(void);
		std::suspend_always initial_suspend(void);
		void unhandled_exception(void);
		void return_void(void);
		std::suspend_always final_suspend(void) noexcept;

	public:
		// !!!!! METHOD je volana ak ma byt COROUTINE SUSPENDED.
		std::suspend_always await_transform(ECoroutineSchedulingMode SchedulingMode);

	public:
		CCoroutineObjectSchedulingScheduler2* GetScheduler(void) noexcept;
		void SetScheduler(CCoroutineObjectSchedulingScheduler2* Scheduler) noexcept;

	public:
		SCoroutineObjectSchedulingPromiseType2(int ID, int);
		~SCoroutineObjectSchedulingPromiseType2(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectSchedulingPromiseType2<TCoroutineObject>::SCoroutineObjectSchedulingPromiseType2(int ID, int)
	: MID(ID), MScheduler(nullptr)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectSchedulingPromiseType2<TCoroutineObject>::~SCoroutineObjectSchedulingPromiseType2(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
TCoroutineObject SCoroutineObjectSchedulingPromiseType2<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectSchedulingPromiseType2>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectSchedulingPromiseType2<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectSchedulingPromiseType2<TCoroutineObject>::unhandled_exception(void)
{
	std::wcout << L"!!!!! UNHANDLED EXCEPTION DETECTED. !!!!!" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectSchedulingPromiseType2<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectSchedulingPromiseType2<TCoroutineObject>::SCoroutineObjectSchedulingPromiseType2::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
CCoroutineObjectSchedulingScheduler2* SCoroutineObjectSchedulingPromiseType2<TCoroutineObject>::GetScheduler(void) noexcept
{
	return(MScheduler);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectSchedulingPromiseType2<TCoroutineObject>::SetScheduler(CCoroutineObjectSchedulingScheduler2* Scheduler) noexcept
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
class [[nodiscard]] CCoroutineObjectScheduling2 final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectSchedulingPromiseType2<CCoroutineObjectScheduling2>;

	private:
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectScheduling2& operator=(const CCoroutineObjectScheduling2&)=delete;
		CCoroutineObjectScheduling2& operator=(CCoroutineObjectScheduling2&& Other) noexcept;

	public:
		std::coroutine_handle<promise_type> GetHandle(void) noexcept;

	public:
		CCoroutineObjectScheduling2(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectScheduling2(const CCoroutineObjectScheduling2&)=delete;
		CCoroutineObjectScheduling2(CCoroutineObjectScheduling2&& Other) noexcept;
		~CCoroutineObjectScheduling2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CCoroutineObjectSchedulingScheduler2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::multimap<int,CCoroutineObjectScheduling2>			MCoroutineObjects;

	public:
		// !!! METHOD ulozi COROUTINE OBJECT do MULTIMAP.
		void StartCoroutine(CCoroutineObjectScheduling2&& CoroutineObject);
		// !!! METHOD vykona RESUME MOST PRIOR COROUTINE OBJECT zo vsetkych COROUTINE OBJECTS v MULTIMAP.
		bool ResumeCoroutine(void);
		// !!! METHOD nastavuje PRIORITY daneho COROUTINE OBJECT.
		bool ChangeCoroutinePriority(std::coroutine_handle<CCoroutineObjectScheduling2::promise_type> CoroutineHandle, ECoroutineSchedulingMode SchedulingMode);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectSchedulingPromiseType2<TCoroutineObject>::await_transform(ECoroutineSchedulingMode SchedulingMode)
{
	std::wcout << L"!!!!! COROUTINE [" << MID << L"] - METHOD AWAIT TRANSFORM is CALLED." << std::endl;

	std::coroutine_handle<CCoroutineObjectScheduling2::promise_type>	CoroutineHandle=std::coroutine_handle<CCoroutineObjectScheduling2::promise_type>::from_promise(*this);
	
	// !!!!! Pri SUSPEND sa prepocita priorita danej COROUTINE.
	MScheduler->ChangeCoroutinePriority(CoroutineHandle,SchedulingMode);

	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------