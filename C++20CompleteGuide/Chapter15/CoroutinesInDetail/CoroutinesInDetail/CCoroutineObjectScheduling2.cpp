//----------------------------------------------------------------------------------------------------------------------
#include "CCoroutineObjectScheduling2.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const static int												DEFAULT_PRIOIRTY=20;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectScheduling2::CCoroutineObjectScheduling2(coroutine_handle<promise_type> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectScheduling2::CCoroutineObjectScheduling2(CCoroutineObjectScheduling2&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectScheduling2::~CCoroutineObjectScheduling2(void) noexcept
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
CCoroutineObjectScheduling2& CCoroutineObjectScheduling2::operator=(CCoroutineObjectScheduling2&& Other) noexcept
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
coroutine_handle<CCoroutineObjectScheduling2::promise_type> CCoroutineObjectScheduling2::GetHandle(void) noexcept
{
	return(MHandle);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CCoroutineObjectSchedulingScheduler2::StartCoroutine(CCoroutineObjectScheduling2&& CoroutineObject)
{
	CCoroutineObjectScheduling2::promise_type&					PromiseTypeObject=CoroutineObject.GetHandle().promise();

	PromiseTypeObject.SetScheduler(this);
	
	MCoroutineObjects.emplace(DEFAULT_PRIOIRTY,move(CoroutineObject));
}
//----------------------------------------------------------------------------------------------------------------------
bool CCoroutineObjectSchedulingScheduler2::ResumeCoroutine(void)
{
	if (MCoroutineObjects.empty()==true)
	{
		return(false);
	}

	multimap<int,CCoroutineObjectScheduling2>::iterator			Iterator=MCoroutineObjects.begin();
	coroutine_handle<CCoroutineObjectScheduling2::promise_type>	CurrentCoroutineHandle=Iterator->second.GetHandle();

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
bool CCoroutineObjectSchedulingScheduler2::ChangeCoroutinePriority(std::coroutine_handle<CCoroutineObjectScheduling2::promise_type> CoroutineHandle, ECoroutineSchedulingMode SchedulingMode)
{
	for(multimap<int,CCoroutineObjectScheduling2>::iterator Iterator=MCoroutineObjects.begin();Iterator!=MCoroutineObjects.end();++Iterator)
	{
		coroutine_handle<CCoroutineObjectScheduling2::promise_type>	CurrentCoroutineHandle=Iterator->second.GetHandle();

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
				multimap<int,CCoroutineObjectScheduling2>::node_type	Node=MCoroutineObjects.extract(Iterator);
				
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