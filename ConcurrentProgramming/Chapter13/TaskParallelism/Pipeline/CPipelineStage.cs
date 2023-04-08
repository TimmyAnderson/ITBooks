using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace Pipeline
{
/*
//------------------------------------------------------------------------------
	// TENTO KOD NIE JE KOMPILOVATELNY.

	// Trieda implementuje Pipeline Stage.
	public class CPipelineStage<TInput,TOutput> : IPipelineStage
	{
//------------------------------------------------------------------------------
		private readonly Func<TInput,TOutput>		MTransform;
		private readonly int						MDegree;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CPipelineStage(Func<TInput,TOutput> Transform, int Degree)
		{
			MTransform=Transform;
			MDegree=Degree;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public IEnumerable Start(IEnumerable Src)
		{
			// Vytvorim Threads, ktore budu realizovat danu Stage.
			Thread[]					Threads=new Thread[MDegree];

			CBlockingQueue<TOutput>		Dest=new CBlockingQueue<TOutput>();
			IEnumerator<TInput>			SharedSrc=((IEnumerable<TInput>)Src).GetEnumerator();
			int							Active=Threads.Length;

			for (int i=0;i<Threads.Length;i++)
			{
				Threads[i] = new Thread(delegate()
				{
					// Drain the source.
					TInput				Elem;

					// !!! Vyberam novy Item z Queue. MoveNext() by mala THREAD SAFE vybera Item z Queue a vracat TRUE, alebo FALSE podla toho ci je Queue prazdna. BOHUZIAL TATO METODA NIE JE IMPLEMENTOVANA.
					while (SharedSrc.MoveNext(out Elem))
					{
						// Spracujem Input na TEJTO STAGE a TRANSFORMUJEM ho na OUTPUT.
						TOutput			NewElem=MTransform(Elem);

						// !!! Zaradim OUTPUT do VYSTUPNEJ QUEUE, ktora JE VEZBOU MEDZI STAGES.
						// !!!!! VEZBENIE MEDZI STAGES JE REALIZOVANE ZDIELANYMI CBlockingQueues.
						Dest.Enqueue(NewElem);
					}

					// Ak pocitadlo Threads klesne na 0, tak OZNACIM CBlockingQueue sa SKONCENU.
					if (Interlocked.Decrement(ref Active)==0)
						Dest.IsDone=true;
				});

				Threads[i].Start();
			}

			return(Dest);
		}
//------------------------------------------------------------------------------
	}
*/
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------