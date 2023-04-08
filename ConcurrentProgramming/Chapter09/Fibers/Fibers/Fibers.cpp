//------------------------------------------------------------------------------
#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
PVOID			PFiber1;
PVOID			PFiber2;
PVOID			PFiber3;
HANDLE			PSwappedOutEvent;
//------------------------------------------------------------------------------
// THREAD T2.
DWORD CALLBACK Thread2Proc(PVOID PParameter)
{
	// Asociujem THREAD T2 s FIBER F3.
    PFiber3=ConvertThreadToFiber(NULL);

	printf("T: [%d], F: [%d] - Thread2Proc(): Wait for swap notification !\n", GetCurrentThreadId(),GetCurrentFiber());

	// Cakam na kym Thread T2 NEZACNE VYKONAVAT FIBER F1.
    WaitForSingleObject(PSwappedOutEvent, INFINITE);

    printf("T: [%d], F: [%d] - Thread2Proc(): Resuming main !\n", GetCurrentThreadId(),GetCurrentFiber());

    // Prepnem Thread T2 na vykonavanie FIBER F1.
	// !!!!! Kod funkcie RunOtherFiber() je to ZASTAVENY a CELY KOD POKRACUJE VYKONAVANIM funkcie main() - POKRACUJE VYKONAVANIE FIBER F1.
    SwitchToFiber(PFiber1);

	// !!!!! Tento kod sa NIKDY NEVYKONA.
    printf("T: [%d], F: [%d] - Thread2Proc(): THIS CODE IS NEVER CALLED !\n", GetCurrentThreadId(),GetCurrentFiber());

    return(0);
}
//------------------------------------------------------------------------------
// Kod funkcie vykonavany vo FIBER 2.
VOID CALLBACK Fiber2Main(PVOID PParameter)
{
    printf("T: [%d], F: [%d] - Fiber2Main(): Notify and wait for ack !\n", GetCurrentThreadId(),GetCurrentFiber());
	
    SetEvent(PSwappedOutEvent);

    printf("T: [%d], F: [%d] - Fiber2Main(): Done !\n", GetCurrentThreadId(),GetCurrentFiber());
}
//------------------------------------------------------------------------------
// THREAD T1 - MAIN THREAD.
void Thread1Proc(void)
{
	// Asociujem THREAD T1 (MAIN THREAD) s FIBER F1.
    PFiber1=ConvertThreadToFiber(NULL);

    printf("T: [%d], F: [%d] - Thread1Proc(): Starting main !\n", GetCurrentThreadId(),GetCurrentFiber());

    PSwappedOutEvent=CreateEvent(NULL, FALSE, FALSE, NULL);

	// Vytvorim THREAD T2.
    HANDLE		HThread=CreateThread(NULL, 0, &Thread2Proc, NULL, 0, NULL);

    // Vytvorim FIBER F2, ktory vsak ZATIAL NIE JE SPUSTENY.
    PFiber2=CreateFiber(0, &Fiber2Main, NULL);

    printf("T: [%d], F: [%d] - Thread1Proc(): Before F2 is started !\n", GetCurrentThreadId(),GetCurrentFiber());

    // Preklopim sa do FIBER F2, pricom FIBER F1 je POZASAVENY.
	// !!!!! Kod funkcie main() je to ZASTAVENY a CELY KOD POKRACUJE VYKONAVANIM funkcie FIBER F2 - FiberMain().
    SwitchToFiber(PFiber2);

	// !!!!! Tento kod je VYKONAVANY VO FIBER F1.
    printf("T: [%d], F: [%d] - Thread1Proc(): Ending main !\n", GetCurrentThreadId(),GetCurrentFiber());

    CloseHandle(HThread);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	Thread1Proc();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------