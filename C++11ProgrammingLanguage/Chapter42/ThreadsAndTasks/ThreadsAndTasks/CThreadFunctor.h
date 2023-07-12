//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <chrono>
#include <thread>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CThreadFunctor
{
//-----------------------------------------------------------------------------
	private:
		int														MIndex;

	public:
		void operator()(int Index)
		{
			wprintf_s(L"THREAD OPERATOR() [%d,%d] STARTED !\n",MIndex,Index);

			// Caka sa 5 sekund.
			std::this_thread::sleep_for(std::chrono::duration<int,std::ratio<1,1>>(5));

			wprintf_s(L"THREAD OPERATOR() [%d,%d] FINISHED !\n",MIndex,Index);
		}

	public:
		CThreadFunctor(int Index)
			: MIndex(Index)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------