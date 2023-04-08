#pragma once
//------------------------------------------------------------------------------
#include <windows.h>
#include <queue>
//------------------------------------------------------------------------------
template <typename T>
class CBlockingQueue
{
//------------------------------------------------------------------------------
	private:
		std::queue<T>					*MPQueue;
		CRITICAL_SECTION				MExclusiveLock;
		// Pouziva CONDITION_VARIABLE a preto sa da spustit IBA VO VISTE.
		CONDITION_VARIABLE				MConsumerEvent;

	public:
		void Enqueue(T Item);
		T Dequeue(void);

	public:
		CBlockingQueue(void);
		~CBlockingQueue(void);
//------------------------------------------------------------------------------
};
//------------------------------------------------------------------------------