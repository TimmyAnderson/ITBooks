using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace HybridThreadSynchronizationConstructs
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CComplexHybridLock : IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		// Counter udavajuci kolko THREADS caka na vstup do KRITICKEJ SEKCIE.
		// !!! Tato hodnota sa pouziva na implementaciu USER-MODE SYNCHRONIZATION CONSTRUCTS.
        private int												MWaiters;
		// !!! Tato premenna typu AutoResetEvent sa pouziva na implementaciu KERNEL-MODE SYNCHRONIZATION CONSTRUCTS.
        private AutoResetEvent									MWaiterLock;
        // Pocet SPINS, ktore sa spravia, cakajuc ci sa LOCK prideleny inemu THREADU neuvolni, aby nebolo treba pouzit KERNEL-MODE SYNCHRONIZATION CONSTRUCTS.
        private int												MSpinCount;
        // ID THREADU, ktory vlastni LOCK. Tento LOCK si podobne ako MUTEX uchovava informaciou o vlastnikovi LOCK.
        private int												MOwningThreadId;
		// Pocet rekurzivnych volani LOCK TYM ISTYM THREADOM.
		private int												MRecursion;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CComplexHybridLock()
		{
			MWaiters=0;
			MWaiterLock=new AutoResetEvent(false);
			MSpinCount=4000;
			MOwningThreadId=0;
			MRecursion=0;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public void Enter()
		{
            int													ThreadId=Thread.CurrentThread.ManagedThreadId;

            // Ak THREAD vlastni LOCK iba sa INKREMENTUJE MRecursion.
            if (ThreadId==MOwningThreadId)
			{
				// Tu NEMUSIM pouzivat INTERLOCKED metody, lebo inkrementacia sa deje iba v THREADE, ktory uz MA LOCK a teda ku CONTENTION NEDOCHADZA.
				MRecursion++;
				return;
			}

            // CLR trieda implementujuca efektivny SPIN WAIT.
            SpinWait											SW=new SpinWait();

			// Vykonavam tolko SPINS kolko je dane hodnotou MSpinCount.
            for (int SpinCount=0;SpinCount<MSpinCount;SpinCount++)
			{
                // Ak sa LOCK UVOLNIL, tak tento THREAD moze SI PRIRADIT LOCK.
                if (Interlocked.CompareExchange(ref MWaiters,1,0)==0)
				{
					goto GotLock;
				}

                // Robim SPINING.
                SW.SpinOnce();
            }

            // SPINING sa skoncil a skusim este raz, ci nahodou LOCK nie je UVOLNENY.
            if (Interlocked.Increment(ref MWaiters)>1)
			{
                // Ak LOCK NIE JE ANI TERAZ VOLNY, tak prejdem do WAIT STAVU pomocou KERNEL-MODE CONSTRUCTS.
                MWaiterLock.WaitOne();

                // Ked WAIT SKONCI, znamena to, ze LOCK bol tomuto THREADU PRIDELENY.
            }

			GotLock:
				// LOCK bol PRIDELENY TOMUTO THREADU a zapisa sa ID THREADU, ktory LOCK VLASTNI.
				MOwningThreadId=ThreadId;
				MRecursion=1;
        }
//-------------------------------------------------------------------------------------------------------
        public void Leave()
		{
            int													ThreadId=Thread.CurrentThread.ManagedThreadId;

            // Ak THREAD NEVLASTNI LOCK, tak sa HODI EXCEPTION.
            if (ThreadId!=MOwningThreadId)
			{
                throw(new SynchronizationLockException("LOCK is NOT owned by calling THREAD !"));
			}

            // Ked som sa dostal AZ SEM, tak IBA z THREADU, ktory VLASTNI LOCK a preto moze MRecursion DEKREMENTOVAT i bez pouzitia INTERLOCKED metody.
            if (--MRecursion>0)
			{
				return;
			}

			// Ked som sa dostal AZ SEM tak MRecursion==0 a LOCK MOZE BYT UVOLNENY.
            MOwningThreadId=0;

            // Ak ZIADEN INY THREAD NECAKA na LOCK, tak staci metoda moze skoncit.
            if (Interlocked.Decrement(ref MWaiters)==0)
			{
                return;
			}

            // Ak niektory THREAD CAKA na UVOLNENIE LOCK tak UVOLNIM KERNEL-MODE CONSTRUCTS.
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