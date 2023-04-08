using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace ManagedProducerConsumerList
{
//------------------------------------------------------------------------------
	// Queue kontroluje ako prazdny tak aj PLNY stav a v pripade, ze tak nastane tak je CONSUMER (empty), alebo PRODUCER (full) BLOKOVANY.
	public class CBlockingBoundedQueue<T>
	{
//------------------------------------------------------------------------------
		private Queue<T>					MQueue=new Queue<T>();
		private int							MCapacity;
		private object						MFullEvent=new object();
		private int							MFullWaiters=0;
		private object						MEmptyEvent=new object();
		private int							MEmptyWaiters=0;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CBlockingBoundedQueue(int Capacity)
		{
			MCapacity=Capacity;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public int							Count
		{
			get
			{
				lock (MQueue)
				{
					return(MQueue.Count);
				}
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public void Clear()
		{
			lock (MQueue)
			{
				MQueue.Clear();
			}
		}
//------------------------------------------------------------------------------
		public bool Contains(T Item)
		{
			lock (MQueue)
			{
				return MQueue.Contains(Item);
			}
		}
//------------------------------------------------------------------------------
		public void Enqueue(T Item)
		{
			lock (MQueue)
			{
				while (MQueue.Count==MCapacity)
				{
					MFullWaiters++;

					try
					{
						lock (MFullEvent)
						{
							Monitor.Exit(MQueue);
							Monitor.Wait(MFullEvent);
							Monitor.Enter(MQueue);
						}
					}
					finally
					{
						MFullWaiters--;
					}
				}

				MQueue.Enqueue(Item);
			}

			// Wake consumers who are waiting for a new item.
			if (MEmptyWaiters > 0)
			{
				lock (MEmptyEvent)
				{
					Monitor.Pulse(MEmptyEvent);
				}
			}
		}
//------------------------------------------------------------------------------
		public T Dequeue()
		{
			T				Item;

			lock (MQueue)
			{
				while(MQueue.Count==0)
				{
					// Queue is empty, wait for a new item to arrive.
					MEmptyWaiters++;

					try
					{
						lock (MEmptyEvent)
						{
							Monitor.Exit(MQueue);
							Monitor.Wait(MEmptyEvent);
							Monitor.Enter(MQueue);
						}
					}
					finally
					{
						MEmptyWaiters--;
					}
				}

				Item=MQueue.Dequeue();
			}
			// Wake producers who are waiting to produce.
			if (MFullWaiters > 0)
			{
				lock (MFullEvent)
				{
					Monitor.Pulse(MFullEvent);
				}
			}

			return(Item);
		}
//------------------------------------------------------------------------------
		public T Peek()
		{
			lock (MQueue)
			{
				return(MQueue.Peek());
			}
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------