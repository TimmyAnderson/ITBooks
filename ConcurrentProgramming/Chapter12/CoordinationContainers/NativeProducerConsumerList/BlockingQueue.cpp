#include "BlockingQueue.h"
//------------------------------------------------------------------------------
template <typename T>
CBlockingQueue<T>::CBlockingQueue(void)
{
	MPQueue=new queue<T>();

	InitializeCriticalSection(&MExclusiveLock);
	InitializeConditionVariable(&MConsumerEvent);
}
//------------------------------------------------------------------------------
template <typename T>
CBlockingQueue<T>::~CBlockingQueue(void)
{
    DeleteConditionVariable(&MConsumerEvent);
    DeleteCriticalSection(&MExclusiveLock);

    delete(MPQueue);
    MPQueue=NULL;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <typename T>
void CBlockingQueue<T>::Enqueue(T Item)
{
    EnterCriticalSection(&MExclusiveLock);

    MPQueue->push(Item);

    LeaveCriticalSection(&MExclusiveLock);

    // Prebudi MConsumerEvent, ktory sposobi UKONCENIE volania SleepConditionVariableCS().
    WakeConditionVariable(&MConsumerEvent);
}
//------------------------------------------------------------------------------
template <typename T>
T CBlockingQueue<T>::Dequeue(void)
{
    T			Item;

    EnterCriticalSection(&MExclusiveLock);

    while (MPQueue->empty()==TRUE)
	{
		// Uvolni MExclusiveLock a ZAROVEN ATOMICKY da MConsumerEvent do WAIT STATE.
        SleepConditionVariableCS(&MConsumerEvent, &MExclusiveLock, INFINITE);
	}

    Item=MPQueue->pop();

    LeaveCriticalSection(&MExclusiveLock);

    return(Item);
}
//------------------------------------------------------------------------------