//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <chrono>
#include <thread>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CThreadMethod
{
//-----------------------------------------------------------------------------
	private:
		int														MIndex;

	public:
		void ThreadMethod(int Index)
		{
			wprintf_s(L"THREAD METHOD [%d,%d] STARTED !\n",MIndex,Index);

			// Caka sa 5 sekund.
			std::this_thread::sleep_for(std::chrono::duration<int,std::ratio<1,1>>(5));

			wprintf_s(L"THREAD METHOD [%d,%d] FINISHED !\n",MIndex,Index);
		}

	public:
		CThreadMethod(int Index)
			: MIndex(Index)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------