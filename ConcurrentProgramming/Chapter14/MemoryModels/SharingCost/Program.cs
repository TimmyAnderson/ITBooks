using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace SharingCost
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static long Run(int P, int RunTimeMs, bool FalseSharing)
		{
			GC.Collect();

			CCounter[]				Counters=new CCounter[P];

			if (FalseSharing==true)
				for (int i=0;i<Counters.Length;i++)
					Counters[i]=new CCounter();

			bool					Stop=false;

			using (ManualResetEvent MRE=new ManualResetEvent(false))
			{
				Thread[]			TT=new Thread[P];

				for (int i=0;i<P;i++)
				{
					int				Idx=i;

					TT[i] = new Thread(delegate()
					{
						CCounter	C;

						if (FalseSharing==true)
							C=Counters[Idx];
						else
							C=Counters[Idx]=new CCounter();

						MRE.WaitOne();

						while (Stop==false)
						{
							for (int j = 0; j < 100; j++)
								C.MCount++;
						}
					});
					TT[i].Start();
				}

				MRE.Set();

				Thread.Sleep(RunTimeMs);

				// Notify threads to stop and then wait.
				Stop=true;

				foreach (Thread T in TT)
					T.Join();
			}

			// Compute the total counts.
			long					Total = 0;

			for (int i=0;i<P;i++)
				Total+=Counters[i].MCount;

			return(Total);
		}
//------------------------------------------------------------------------------
		private static void Test()
		{
			int				P=Environment.ProcessorCount;

			Console.WriteLine("P={0} !", P);

			long			WithSharing = Run(P, 1000, true);

			Console.WriteLine("Sharing   = {0} !", WithSharing);

			// !!!!! Ked NEEPOUZIJEM SHARING, tak ma RYCHLEJSI PRISTUP na MULTI CPU PC.
			long			WOutSharing = Run(P, 1000, false);

			Console.WriteLine("NoSharing = {0} !", WOutSharing);

			Console.WriteLine("%         = {0} !", ((float)WOutSharing/(float)WithSharing));
		}
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------