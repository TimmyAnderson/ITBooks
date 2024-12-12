//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "CMemoryOperators.h"
#include "ETimerAttributes.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
typedef VOID TypeTimerCallback(PVOID Context);
typedef VOID TypeTimerDeleteCallback(PVOID Context);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CTimerGlobal final : public CMemoryOperators
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		PEX_TIMER												MTimer;
		TypeTimerCallback*										MTimerCallback;
		TypeTimerDeleteCallback*								MTimerDeleteCallback;
		PVOID													MCallbackData;

	private:
		static VOID StaticTimerCallbackMethod(PEX_TIMER Timer, PVOID Context);
		static VOID StaticDeleteTimerCallbackMethod(PVOID Context);

	private:
		VOID TimerCallbackMethod(void);
		VOID TimerDeleteCallbackMethod(void);

	public:
		PEX_TIMER GetTimer(void);

	public:
		BOOLEAN SetTimer(LONGLONG DueTime, LONGLONG Period=0ULL, LONGLONG NoWakeTolerance=0ULL);
		BOOLEAN CancelTimer(void);

	public:
		BOOLEAN Init(TypeTimerCallback* TimerCallback, TypeTimerDeleteCallback* TimerDeleteCallback, ETimerAttributes Attributes, PVOID CallbackData);
		BOOLEAN Destroy(BOOLEAN Cancel, BOOLEAN Wait);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------