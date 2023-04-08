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

	// Trieda implementuje Pipeline.
	// !!!!! Pipeline NARAZ VYTVARA VSETKY THREADS, na VSETKYCH STAGES a tie SPRACUVAJU ITEMS z NADRADENYCH STAGES. Threads na danej Stage SU UKONCENE KED SPRACUJU VSETKY Items.
	public class CPipeline<TSrc,TDest>
	{
//------------------------------------------------------------------------------
		private readonly IPipelineStage[]			MStages;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CPipeline(Func<TSrc,TDest> Transform, int Degree)
			: this(new IPipelineStage[0], Transform, Degree)
		{
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		// Copy constructor, ktory prida Stage na koniec existujucej Pipeline.
		internal CPipeline(IPipelineStage[] ToCopy, Func<TSrc,TDest> Transform,int Degree)
		{
			MStages=new IPipelineStage[ToCopy.Length+1];

			Array.Copy(ToCopy, MStages, ToCopy.Length);
			MStages[MStages.Length-1]=new CPipelineStage<TSrc,TDest>(Transform,Degree);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		// Vytvara novu Pipeline pridanim novej Stage na koniec existujucej Pipeline.
		public CPipeline<TSrc,TNew> AddStage<TNew>(Func<TSrc,TNew> Transform, int Degree)
		{
			return(new CPipeline<TSrc,TNew>(MStages, Transform, Degree));
		}
//------------------------------------------------------------------------------
		// !!! Spusta samotny ALGORITMUS PIPELINE.
		public IEnumerator<TDest> GetEnumerator(IEnumerable<TSrc> E)
		{
			// !!!!! Vrateny objekt IEnumerable(CBlockingQueue) je de-facto PREPOJENIM JEDNOTLIVYCH STAGES.
			IEnumerable				EF=E;

			// Nastartuje Threads na VSETKYCH STAGE.
			for (int i = 0; i < MStages.Length; i++)
				EF=MStages[i].Start(EF);

			foreach (TDest Elem in EF)
				yield return(Elem);
		}
//------------------------------------------------------------------------------
	}
*/
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------