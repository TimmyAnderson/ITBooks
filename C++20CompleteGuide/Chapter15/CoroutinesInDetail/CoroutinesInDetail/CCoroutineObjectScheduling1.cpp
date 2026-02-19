//----------------------------------------------------------------------------------------------------------------------
#include "CCoroutineObjectScheduling1.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const static int												DEFAULT_PRIOIRTY=10;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectScheduling1::CCoroutineObjectScheduling1(coroutine_handle<promise_type> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectScheduling1::CCoroutineObjectScheduling1(CCoroutineObjectScheduling1&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectScheduling1::~CCoroutineObjectScheduling1(void) noexcept
{
	if (static_cast<bool>(MHandle)==true)
	{
		MHandle.destroy();
		MHandle=nullptr;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectScheduling1& CCoroutineObjectScheduling1::operator=(CCoroutineObjectScheduling1&& Other) noexcept
{
	if (this!=&Other)
	{
		if (static_cast<bool>(MHandle)==true)
		{
			MHandle.destroy();
			MHandle=nullptr;
		}

		MHandle=move(Other.MHandle);

		Other.MHandle=nullptr;
	}

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
coroutine_handle<CCoroutineObjectScheduling1::promise_type> CCoroutineObjectScheduling1::GetHandle(void) noexcept
{
	return(MHandle);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectSchedulingAwaiter1::CCoroutineObjectSchedulingAwaiter1(ECoroutineSchedulingMode SchedulingMode)
	: MSchedulingMode(SchedulingMode)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectSchedulingAwaiter1::~CCoroutineObjectSchedulingAwaiter1(void) noexcept
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CCoroutineObjectSchedulingAwaiter1::await_ready(void) const noexcept
{
	return(false);
}
//----------------------------------------------------------------------------------------------------------------------
void CCoroutineObjectSchedulingAwaiter1::await_suspend(coroutine_handle<CCoroutineObjectScheduling1::promise_type> CoroutineHandle) noexcept
{
	CCoroutineObjectScheduling1::promise_type&					PromiseTypeObject=CoroutineHandle.promise();
	CCoroutineObjectSchedulingScheduler1*						Scheduler=PromiseTypeObject.GetScheduler();

	// !!!!! Pri SUSPEND sa prepocita priorita danej COROUTINE.
	Scheduler->ChangeCoroutinePriority(CoroutineHandle,MSchedulingMode);
}
//----------------------------------------------------------------------------------------------------------------------
void CCoroutineObjectSchedulingAwaiter1::await_resume(void) const noexcept
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CCoroutineObjectSchedulingScheduler1::StartCoroutine(CCoroutineObjectScheduling1&& CoroutineObject)
{
	CCoroutineObjectScheduling1::promise_type&					PromiseTypeObject=CoroutineObject.GetHandle().promise();

	PromiseTypeObject.SetScheduler(this);
	
	MCoroutineObjects.emplace(DEFAULT_PRIOIRTY,move(CoroutineObject));
}
//----------------------------------------------------------------------------------------------------------------------
bool CCoroutineObjectSchedulingScheduler1::ResumeCoroutine(void)
{
	if (MCoroutineObjects.empty()==true)
	{
		return(false);
	}

	multimap<int,CCoroutineObjectScheduling1>::iterator			Iterator=MCoroutineObjects.begin();
	coroutine_handle<CCoroutineObjectScheduling1::promise_type>	CurrentCoroutineHandle=Iterator->second.GetHandle();

	// !!! Hlada sa prvy COROUTINE OBJECT, ktory ma platny COROUTINE HANDLE.
	while(static_cast<bool>(CurrentCoroutineHandle)==false || CurrentCoroutineHandle.done()==true)
	{
		++Iterator;

		if (Iterator==MCoroutineObjects.end())
		{
			return(false);
		}

		CurrentCoroutineHandle=Iterator->second.GetHandle();
	}

	// !!!!! COROUTINE bude RESUMED.
	CurrentCoroutineHandle.resume();

	if (CurrentCoroutineHandle.done()==true)
	{
		MCoroutineObjects.erase(Iterator);
	}

	if (MCoroutineObjects.empty()==false)
	{
		// !!! Stale existuju COROUTINE OBJECTS, ktore mozu byt RESUMED.
		return(true);
	}
	else
	{
		// !!! Neexistuju COROUTINE OBJECTS, ktore mozu byt RESUMED.
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
bool CCoroutineObjectSchedulingScheduler1::ChangeCoroutinePriority(std::coroutine_handle<CCoroutineObjectScheduling1::promise_type> CoroutineHandle, ECoroutineSchedulingMode SchedulingMode)
{
	for(multimap<int,CCoroutineObjectScheduling1>::iterator Iterator=MCoroutineObjects.begin();Iterator!=MCoroutineObjects.end();++Iterator)
	{
		coroutine_handle<CCoroutineObjectScheduling1::promise_type>	CurrentCoroutineHandle=Iterator->second.GetHandle();

		if (CoroutineHandle==CurrentCoroutineHandle)
		{
			int													OriginalPriority=Iterator->first;
			int													NewPriority=OriginalPriority;

			if (SchedulingMode==ECoroutineSchedulingMode::E_DEFAULT)
			{
				NewPriority=DEFAULT_PRIOIRTY;
			}
			else if (SchedulingMode==ECoroutineSchedulingMode::E_SAME)
			{
				// EMPTY.
			}
			else if (SchedulingMode==ECoroutineSchedulingMode::E_LESS)
			{
				++NewPriority;
			}
			else if (SchedulingMode==ECoroutineSchedulingMode::E_MORE)
			{
				--NewPriority;
			}

			if (OriginalPriority!=NewPriority)
			{
				// !!! Odstrani NODE z MULTIMAP.
				multimap<int,CCoroutineObjectScheduling1>::node_type	Node=MCoroutineObjects.extract(Iterator);
				
				// !!! Pre NODE sa nastavi novy KEY.
				Node.key()=NewPriority;
				
				// !!! Vlozi NODE do MULTIMAP.
				MCoroutineObjects.insert(move(Node));
			}

			return(true);
		}
	}

	return(false);
}
//----------------------------------------------------------------------------------------------------------------------