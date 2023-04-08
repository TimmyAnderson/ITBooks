using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using System.Linq;
using System.Text;
//------------------------------------------------------------------------------
#pragma warning disable 0420
//------------------------------------------------------------------------------
namespace LockFreeContainers
{
//------------------------------------------------------------------------------
	public class CLockFreeQueue<T> : IEnumerable<T>
	{
//------------------------------------------------------------------------------
		class Node
		{
			internal T						MValue;
			internal volatile Node			MNext;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private volatile Node				MHead;
		private volatile Node				MTail;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CLockFreeQueue()
		{
			// Sentinel item.
			MHead=MTail=new Node();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public int							Count
		{
			get
			{
				int				Count=0;

				// Prechadzam cely Queue, aby som zistil jeho dlzku.
				for (Node Curr=MHead.MNext;Curr!=null;Curr=Curr.MNext)
					Count++;

				return(Count);
			}
		}
//------------------------------------------------------------------------------
		public bool							IsEmpty
		{
			get
			{
				return(MHead.MNext==null);
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		// Metoda nachadza aktualny Tail.
		private Node GetTailAndCatchUp()
		{
			Node			Tail=MTail;
			Node			Next=Tail.MNext;

			// Robim iteracie pokial nenajdem Tail.
			while (Next!=null)
			{
				Interlocked.CompareExchange(ref MTail,Next,Tail);
				Tail=MTail;
				Next=Tail.MNext;
			}

			return(Tail);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public void Enqueue(T Obj)
		{
			Node			NewNode=new Node();

			NewNode.MValue=Obj;

			// Pridam novy Item za Tail.
			Node			Tail;

			do
			{
				// Najdem Tail.
				Tail=GetTailAndCatchUp();
				// Nastavim Next nasledujuceho Node na Tail.
				NewNode.MNext=Tail.MNext;
			}
			// Opakujem cyklus pokym Tail nie je skutocne Tail. Totizto medzi ziskanim hodnoty Tail a tymto kodom mohol iny Thread Tail zmenit.
			while (Interlocked.CompareExchange(ref Tail.MNext,NewNode,null)!=null);

			// Pousim sa posunut hodnotu MTail.
			// !!! Ak zlyha NIE JE TO PROBLEM, lebo nasledujuca operacie pridania nove Item posunie Tail do spravnej pozicie.
			Interlocked.CompareExchange(ref MTail,NewNode,Tail);
		}
//------------------------------------------------------------------------------
		public bool TryDequeue(out T Value)
		{
			while(true)
			{
				Node		Head=MHead;
				Node		Next=Head.MNext;

				if (Next==null)
				{
					Value=default(T);
					return(false);
				}
				else
				{
					// Akonahle je Head==MHead a teda MHead SKUTOCNE UKAZUJE NA HEAD, tak sa posunie MHead na Next a tym sa de-facto odstani Item.
					if (Interlocked.CompareExchange(ref MHead,Next,Head)==Head)
					{
						// !!!!! Note: this read would be unsafe with a C++ implementation. Another thread may have dequeued and freed 'next' by the time we get here, at which point we would try to dereference a bad pointer. Because we're in a GC-based system, we're OK doing this -- GC keeps it alive.
						Value=Next.MValue;
						return(true);
					}
				}
			}
		}
//------------------------------------------------------------------------------
		public bool TryPeek(out T Value)
		{
			Node			Curr=MHead.MNext;

			if (Curr==null)
			{
				Value=default(T);
				return(false);
			}
			else
			{
				Value=Curr.MValue;
				return(true);
			}
		}
//------------------------------------------------------------------------------
		public IEnumerator<T> GetEnumerator()
		{
			Node			Curr=MHead.MNext;
			Node			Tail=GetTailAndCatchUp();

			while (Curr!=null)
			{
				yield return(Curr.MValue);

				if (Curr==Tail)
					break;

				Curr=Curr.MNext;
			}
		}
//------------------------------------------------------------------------------
		IEnumerator IEnumerable.GetEnumerator()
		{
			return(((IEnumerable<T>)this).GetEnumerator());
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------