using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace DynamicDecomposition
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static Random					MRND=new Random();
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void ParallelKnownSize(int Lo, int Hi, Action<int,int> Body, int P)
		{
			const int			Chunk = 2;

			// Shared variable.
			int					Current=Lo;

			// Schedule the threads to run in parallel
			for (int i=0;i<P;i++)
			{
				ThreadPool.QueueUserWorkItem(delegate(object ProcId)
				{
					int					J;

					// Kedze pristupujem k shared variablem musim pouzit interlocked operaciu.
					while ((J=(Interlocked.Add(ref Current,Chunk)-Chunk))<Hi)
					{
						for (int k=0;k<Chunk && (J+k)<Hi; k++)
						{
							Body(J+k,(int) ProcId);
						}
					}

					Console.WriteLine(string.Format("Signal that THREAD: {0} finished !",ProcId));
				}, i);
			}

			Console.WriteLine("Task scheduled !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
		static void ParallelUnknownSize(IEnumerable<int> E, Action<int,int> Body, int P)
		{
			const int					Chunk=2;
			IEnumerator<int>			En=E.GetEnumerator();

			for (int i=0;i<P;i++)
			{
				ThreadPool.QueueUserWorkItem(delegate(object ProcId)
				{
					int[]				Elems=new int[Chunk];
					int					ElemsCount=0;

					do
					{
						// Kedze iterator standardne nie je trhead safe musim z neho jednotlive items vyberat thread safe sposobom.
						lock (En)
						{
							// Pridelim 'chunk' iteracii danemu threadu.
							for (ElemsCount=0;ElemsCount<Chunk;ElemsCount++)
							{
								// Ked MoveNext() vrati FALSE - som na konci kolekcie.
								if (En.MoveNext()==false)
									break;

								Elems[ElemsCount]=En.Current;
							}
						}

						// Vykonam pridelene iteracie.
						for (int j=0;j<ElemsCount; j++)
						{
							Body(Elems[j],(int) ProcId);
						}
					}
					while (ElemsCount==Chunk);

					Console.WriteLine(string.Format("Signal that THREAD: {0} finished !",ProcId));
				}, i);
			}

			Console.WriteLine("Task scheduled !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
		private static void TaskRND(int TaskID, int ThreadID)
		{
			Thread.Sleep(MRND.Next(1000,3000));
			Console.WriteLine(string.Format("TASK: {0} finished by THREAD: {1} !",TaskID,ThreadID));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void TestParallelKnownSize()
		{
			ParallelKnownSize(1,16,TaskRND,3);
		}
//------------------------------------------------------------------------------
		private static void TestParallelUnknownSize()
		{
			List<int>			Values=new List<int>();

			for (int i=0;i<15;i++)
				Values.Add(i+1);

			ParallelUnknownSize(Values,TaskRND,3);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//TestParallelKnownSize();
			TestParallelUnknownSize();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------