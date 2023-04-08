#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
//------------------------------------------------------------------------------
LPVOID			MainFiber;
LPVOID			WorkerFiber1;
LPVOID			WorkerFiber2;
//------------------------------------------------------------------------------
void WINAPI Fiber1_Routine(void* FiberParameter)
{
	// 5. Zacal som vykonavat FIBER 1.
	WriteDebugText(L"FIBER 1 - PHASE 1 - going to SWITCH to FIBER 2 !\n");

	// 6. Skocim do FIBER 2. TU SA KOD ZASTAVI a skoci sa na KOD FIBER 1 - co znamena ZACAT FUNKCIU Fiber2_Routine().
	SwitchToFiber(WorkerFiber2);

	// 9. Pokracujem vo vykonavani FIBER 1.
	WriteDebugText(L"FIBER 1 - PHASE 2 - going to SWITCH to MAIN FIBER !\n");

	// 10. Skocim do MAIN FIBER. TU SA KOD ZASTAVI a skoci do Test1() AZ ZA SwitchToFiber().
	SwitchToFiber(MainFiber);

	// !!! Tu sa uz KOD NIKDY NEDOSTANE.
}
//------------------------------------------------------------------------------
void WINAPI Fiber2_Routine(void* FiberParameter)
{
	// 7. Zacal som vykonavat FIBER 1.
	WriteDebugText(L"FIBER 2 - PHASE 1 - going to SWITCH to FIBER 1 !\n");

	// 8. Skocim SPAT do FIBER 1. TU SA KOD ZASTAVI a skoci SPAT do funkcie Fiber2_Routine(), avsak NIE NA JEJ ZACIATOK, ale az ZA PRVE VOLANIE SwitchToFiber().
	SwitchToFiber(WorkerFiber1);

	// !!! Pri spusteni Test2() sa kod dostane sem - NA KONIEC FIBER FUNKCIE co znamena AUTOMATICKE ZAVOLANIE ExitThread() zo strany fiber infrastruktury.
	WriteDebugText(L"FIBER 2 - PHASE 2 - going to FINISH FIBER FUNCTION - MAIN THREAD will be TERMINATED !\n");
	_getch();
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// !!! Cislami udavam PORADIE VYKONAVANIA KODU.
void Test1(void)
{
	// 1. Konvertujem thread na FIBER.
	MainFiber=ConvertThreadToFiber(L"MAIN fiber");

	WriteDebugText(L"MAIN FIBER - WORKER 1 fiber CREATED !\n");

	// 2. Vytvorim Worker 1 Fiber.
	WorkerFiber1=CreateFiber(0,Fiber1_Routine,L"WORKER 1 fiber");

	WriteDebugText(L"MAIN FIBER - WORKER 2 fiber CREATED !\n");

	// 3. Vytvorim Worker 2 Fiber.
	WorkerFiber2=CreateFiber(0,Fiber2_Routine,L"WORKER 2 fiber");

	WriteDebugText(L"MAIN FIBER - GOING to SWITCH to WORKER 1 fiber !\n");

	// 4. Skocim do FIBER 1. TU SA KOD ZASAVI a skoci sa na KOD FIBER 1 - co znamena ZACAT FUNKCIU Fiber1_Routine().
	SwitchToFiber(WorkerFiber1);

	// 11. Sem sa dostanem z FIBER 1.
	WriteDebugText(L"MAIN FIBER - BACK !\n");

	// 12. Ukoncim FIBER 1.
	DeleteFiber(WorkerFiber1);
	WriteDebugText(L"MAIN FIBER - WORKER 1 fiber DELETED !\n");

	// 13. Ukoncim FIBER 2.
	DeleteFiber(WorkerFiber2);
	WriteDebugText(L"MAIN FIBER - WORKER 2 fiber DELETED !\n");

	// 14. Ukoncim MAIN FIBER jeho SPATNOU konverziu na THREAD.
	ConvertFiberToThread();
	WriteDebugText(L"MAIN FIBER - MAIN fiber DELETED !\n");
}
//------------------------------------------------------------------------------
void Test2(void)
{
	// Konvertujem thread na FIBER.
	MainFiber=ConvertThreadToFiber(L"MAIN fiber");

	WriteDebugText(L"MAIN FIBER - WORKER 1 fiber CREATED !\n");

	// Vytvorim Worker 1 Fiber.
	WorkerFiber1=CreateFiber(0,Fiber1_Routine,L"WORKER 1 fiber");

	WriteDebugText(L"MAIN FIBER - WORKER 2 fiber CREATED !\n");

	// Vytvorim Worker 2 Fiber.
	WorkerFiber2=CreateFiber(0,Fiber2_Routine,L"WORKER 2 fiber");

	WriteDebugText(L"MAIN FIBER - GOING to SWITCH to WORKER 1 fiber !\n");

	SwitchToFiber(WorkerFiber1);

	WriteDebugText(L"MAIN FIBER - BACK !\n");

	WriteDebugText(L"MAIN FIBER - GOING to SWITCH to WORKER 2 fiber !\n");

	SwitchToFiber(WorkerFiber2);

	// Ukoncim WORKER 1.
	DeleteFiber(WorkerFiber1);
	WriteDebugText(L"MAIN FIBER - WORKER 1 fiber DELETED !\n");

	// Ukoncim WORKER 2.
	DeleteFiber(WorkerFiber2);
	WriteDebugText(L"MAIN FIBER - WORKER 2 fiber DELETED !\n");

	ConvertFiberToThread();
	WriteDebugText(L"MAIN FIBER - MAIN fiber DELETED !\n");
}
//------------------------------------------------------------------------------
void Test3(void)
{
	WriteDebugText(L"Before ConvertThreadToFiber()!\n");
	_getch();

	// Konvertujem thread na FIBER.
	MainFiber=ConvertThreadToFiber(L"MAIN fiber");

	WriteDebugText(L"Before DeleteFiber()!\n");
	_getch();

	// !!!!! Ukocnim MAIN FIBER v ktorom PRAVE BEZIM. DeleteFiber() vtedy zavola ExitrThread() a UKONCI THREAD.
	DeleteFiber(MainFiber);

	// !!! Tento kod sa uz NEVYKONA.
	WriteDebugText(L"After DeleteFiber()!\n");
	_getch();
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	//Test1();
	Test2();
	//Test3();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------