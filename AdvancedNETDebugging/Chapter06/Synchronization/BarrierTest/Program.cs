using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace BarrierTest
{
//-------------------------------------------------------------------------------------------------------
	class BarrierDemo
	{
//-------------------------------------------------------------------------------------------------------
		static void Main()
		{
			int					Count = 0;

			// Vytvorim BARRIER s 3 PARTICIPANTS.
			// Poskytnem POST-PHASE ACTION, ktora sa vola pri skonceni danej PHASE.
			// !!! Len na simulaciu chyby hodim EXCEPTION, ked PHASE==2.
			Barrier				MyBarrier=new Barrier(3, (B)=>
			{
				// Toto je akcia, ktora sa vola VZDY po SKONCENI PHASE - teda, kde do danej PHASE dorazia VSETCI PARTICIPANTS.
				Console.WriteLine("Post-Phase action: Count=[{0}], Phase=[{1}] !", Count, B.CurrentPhaseNumber);

				if (B.CurrentPhaseNumber==2)
					throw new Exception("My EXCEPTION !");
			});

			// Pridam dalsich 2 PARTICIPANTS.
			MyBarrier.AddParticipants(2);

			// Odstranim 1 PARTICIPANT - cize celkovo ma 4.
			MyBarrier.RemoveParticipant();

			// Operacia vykonavana vsetkymi PARTICIPANTS.
			Action				Action=() =>
			{
				Interlocked.Increment(ref Count);

				// Signalizujem skoncenie PHASE 0.
				MyBarrier.SignalAndWait();

				Interlocked.Increment(ref Count);

				// Signalizujem skoncenie PHASE 1.
				MyBarrier.SignalAndWait();

				Interlocked.Increment(ref Count);

				try
				{
					// Signalizujem skoncenie PHASE 2.
					// !!! Kedze v POST-PHASE hadzem pri skonceni PHASE 2 EXCEPTION, tak ju zachytim.
					MyBarrier.SignalAndWait();
				}
				catch (BarrierPostPhaseException BPPE)
				{
					Console.WriteLine(string.Format("Caught BarrierPostPhaseException: [{0}] !",BPPE.Message));
				}

				Interlocked.Increment(ref Count);

				// Signalizujem skoncenie PHASE 3.
				MyBarrier.SignalAndWait();
			};

			// Now launch 4 parallel actions to serve as 4 participants
			Parallel.Invoke(Action, Action, Action, Action);

			// Nasledujuci prikaz by hodil EXCEPTION, kedze pocet PARTICIPANTS==4.
			//Parallel.Invoke(Action, Action, Action, Action, Action);

			// Uvolnim BARRIER.
			MyBarrier.Dispose();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------