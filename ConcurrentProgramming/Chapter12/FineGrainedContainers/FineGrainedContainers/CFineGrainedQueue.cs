using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//------------------------------------------------------------------------------
namespace FineGrainedContainers
{
//------------------------------------------------------------------------------
	public class CFineGrainedQueue<T>
	{
//------------------------------------------------------------------------------
		private const int						INITIAL_SIZE = 32;
		private T[]								MArray=new T[INITIAL_SIZE];
		private int								MHead=0;
		private int								MTail=0;
		private object							MEnqLock=new object();
		private object							MDeqLock=new object();
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void Resize()
		{
			// MEnqLock je uz drzany, lebo metoda je volana z Enqueue().
			lock (MDeqLock)
			{
				T[]					NewArray=new T[MArray.Length*2];

				Array.Copy(MArray,MHead,NewArray,0,MArray.Length-MHead);
				Array.Copy(MArray,0,NewArray,MArray.Length-MHead,MHead);
				MArray=NewArray;

				if (MTail<MHead)
					MTail+=MArray.Length-MHead;
				else
					MTail-=MHead;

				MHead=0;
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public void Enqueue(T Obj)
		{
			lock (MEnqLock)
			{
				int					NewTail=MTail+1;

				if (NewTail==MArray.Length)
					NewTail=0;

				// Ak je Array plny robim resize.
				if (NewTail==MHead)
				{
					Resize();

					// Znova vypocitam poziciu noveho Tail.
					NewTail=MTail+1;
				}

				MArray[MTail]=Obj;
				MTail=NewTail;
			}
		}
//------------------------------------------------------------------------------
		public T Dequeue()
		{
			lock (MDeqLock)
			{
				if (MHead==MTail)
					throw(new Exception("Empty !!!"));

				T					Value=MArray[MHead];

				if (default(T)==null)
					// Oznacim na default(T), aby ak sa jedna o objekt mohol byt zlikvidovany GC.
					MArray[MHead]=default(T);

				int					NewHead=MHead+1;

				if (NewHead==MArray.Length)
					NewHead=0;

				MHead=NewHead;

				return(Value);
			}
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------