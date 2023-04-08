using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace ManagedProducerConsumerList
{
//------------------------------------------------------------------------------
	public class CBlockingQueue<T>
	{
//------------------------------------------------------------------------------
		private Queue<T>						MQueue=new Queue<T>();
		private int								MWaitingConsumers=0;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public int								Count
		{
			get
			{
				lock (MQueue)
				{
					return MQueue.Count;
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
				return(MQueue.Contains(Item));
			}
		}
//------------------------------------------------------------------------------
		public void Enqueue(T Item)
		{
			lock (MQueue)
			{
				MQueue.Enqueue(Item);

				// Ak niektory Consumer caka, tak volanim Monitor.Pulse() ho PREBUDIM.
				if (MWaitingConsumers > 0)
					Monitor.Pulse(MQueue);

				// !!! Az tu PO OPUSTENI lock(){} BLOKU je volanie Monitor.Wait() vykonane v separatnom Threade UKONCENE.
			}
		}
//------------------------------------------------------------------------------
		public T Dequeue()
		{
			lock (MQueue)
			{
				while (MQueue.Count == 0)
				{
					MWaitingConsumers++;

					try
					{
						// Ked je Queue prazdna tak caka, nato kym sa naplni co je signalizovane volanim Monitor.Pulse().
						// !!! Volanie Monitor.Wait() skonci HNED POTOM, ako Thread, ktory VOLAL Monitor.Pulse() VYSKOCI zo svojho lock(){} BLOKU.
						Monitor.Wait(MQueue);
					}
					finally
					{
						MWaitingConsumers--;
					}
				}

				return(MQueue.Dequeue());
			}
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