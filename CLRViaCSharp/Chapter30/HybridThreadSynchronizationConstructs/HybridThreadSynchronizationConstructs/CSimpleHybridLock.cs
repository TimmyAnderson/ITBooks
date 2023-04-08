using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace HybridThreadSynchronizationConstructs
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSimpleHybridLock : IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		// Counter udavajuci kolko THREADS caka na vstup do KRITICKEJ SEKCIE.
		// !!! Tato hodnota sa pouziva na implementaciu USER-MODE SYNCHRONIZATION CONSTRUCTS.
		private int												MWaiters;
		// !!! Tato premenna typu AutoResetEvent sa pouziva na implementaciu KERNEL-MODE SYNCHRONIZATION CONSTRUCTS.
		private AutoResetEvent									MWaiterLock;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSimpleHybridLock()
		{
			MWaiters=0;
			MWaiterLock=new AutoResetEvent(false);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Enter()
		{
			// Ak vysledok inkrementacie je 1, tak to znamena, ze NEDOCHADZA ku CONTENTION a THREAD ZISKA LOCK.
			if (Interlocked.Increment(ref MWaiters)==1)
			{
				return;
			}

			// Ak sa dostanem tu, znamena to, ze LOCK uz BOL PRIDELENY a dalsi THREAD MUSI CAKAT.
			MWaiterLock.WaitOne();
		}
//-------------------------------------------------------------------------------------------------------
		public void Leave()
		{
			// Pri LEAVE sa robi DEKREMENTACIA poctu CAKATELOV. Ak je vysledna hodnota rovna 0, tak nie je co robit.
			if (Interlocked.Decrement(ref MWaiters)==0)
			{
				return;
			}

			// Ak niektory THREAD caka na uvolnenie LOCK, tak sa UVOLNENIM AutoResetEvent povoli 1 z CAKAJUCICH THREADS aby pokracoval.
			MWaiterLock.Set();
		}
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			MWaiterLock.Dispose();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------