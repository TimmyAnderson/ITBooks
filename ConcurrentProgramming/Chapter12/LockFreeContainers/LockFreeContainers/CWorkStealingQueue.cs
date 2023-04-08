using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
#pragma warning disable 0420
//------------------------------------------------------------------------------
namespace LockFreeContainers
{
//------------------------------------------------------------------------------
	public class CWorkStealingQueue<T>
	{
//------------------------------------------------------------------------------
		private const int					INITIAL_SIZE=32;
//------------------------------------------------------------------------------
		private T[]							MArray=new T[INITIAL_SIZE];
		private int							MMask=INITIAL_SIZE - 1;
		private volatile int				MHeadIndex=0;
		private volatile int				MTailIndex=0;
		private object						MForeignLock=new object();
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public bool							IsEmpty
		{
			get
			{
				return(MHeadIndex>=MTailIndex);
			}
		}
//------------------------------------------------------------------------------
		public int							Count
		{
			get
			{
				return(MTailIndex-MHeadIndex);
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public void LocalPush(T Obj)
		{
			int				Tail=MTailIndex;

			// When there is space, we can take the fast path.
			if (Tail<(MHeadIndex+MMask))
			{
				MArray[Tail&MMask]=Obj;
				MTailIndex=Tail+1;
			}
			else
			{
				// We need to contend with foreign pops, so we lock.
				lock(MForeignLock)
				{
					int		Head=MHeadIndex;

					// If there is still space (one left), add the element.
					if (Tail<(Head+MMask))
					{
						MArray[Tail&MMask]=Obj;
						MTailIndex=Tail+1;
					}
					else
					{
						// Otherwise, we're full; expand the queue by doubling its size (ignoring overflow).
						T[]	NewArray=new T[MArray.Length<<1];

						for (int i=0;i<MArray.Length;i++)
							NewArray[i]=MArray[(i+Head)&MMask];

						// Reset the field values, incl. the mask.
						MArray=NewArray;
						MHeadIndex=0;
						MTailIndex=Tail-MMask;
						MMask=(MMask<<1)|1;

						// Now place the new value.
						MArray[Tail&MMask]=Obj;
						MTailIndex=Tail+1;
					}
				}
			}
		}
//------------------------------------------------------------------------------
		public bool LocalPop(out T Obj)
		{
			// Decrement the tail using a fence to ensure the subsequent read doesn't come before.
			int				Tail=MTailIndex-1;

			Interlocked.Exchange(ref MTailIndex,Tail);

			// If there is no interaction with a take, do the fast path.
			if (MHeadIndex<=Tail)
			{
				Obj=MArray[Tail&MMask];
				return(true);
			}
			else
			{
				// Interaction with takes: 0 or 1 elements left.
				lock(MForeignLock)
				{
					if (MHeadIndex<=Tail)
					{
						// Element still available. Take it.
						Obj=MArray[Tail&MMask];
						return(true);
					}
					else
					{
						// We lost the race, element was stolen, restore.
						MTailIndex=Tail+1;
						Obj=default(T);
						return(false);
					}
				}
			}
		}
//------------------------------------------------------------------------------
		public bool TrySteal(out T Obj)
		{
			return(TrySteal(out Obj, 0));
		}
//------------------------------------------------------------------------------
		private bool TrySteal(out T Obj, int MillisecondsTimeout)
		{
			if (Monitor.TryEnter(MForeignLock, MillisecondsTimeout)==true)
			{
				try
				{
					// Increment head, and ensure read of tail doesn't move before it (fence).
					int		Head=MHeadIndex;

					Interlocked.Exchange(ref MHeadIndex,Head+1);

					if (Head<MTailIndex)
					{
						Obj=MArray[Head&MMask];
						return(true);
					}
					else
					{
						// Failed, restore head.
						MHeadIndex=Head;
					}
				}
				finally
				{
					Monitor.Exit(MForeignLock);
				}
			}

			Obj=default(T);
			return(false);
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------