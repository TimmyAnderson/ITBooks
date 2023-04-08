using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
#pragma warning disable 0420
//------------------------------------------------------------------------------
namespace Promise
{
//------------------------------------------------------------------------------
	public class CPromise<T>
	{
//------------------------------------------------------------------------------
		// Stav Promise: 0=unstarted, 1=running, 2=done.
		private volatile int				MState=0;
		// Vypocitana hodnota Promise.
		private T							MValue;
		// Exception, ktora vznikne pri vypocte hodnoty.
		private volatile Exception			MException;
		// KO na notifikaciu o konci vypoctu Future.
		private AutoResetEvent				MEvent=new AutoResetEvent(false);
		// Zoznam CALLBACKS, ktore sa volaju po vypocitani hodnoty Promise.
		private Queue<Action<T>>			MResolveActions=new Queue<Action<T>>();
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CPromise()
		{
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public T							Value
		{
			get
			{
				// !!! Ak este hodnota nie je k dispozicii, tak CAKAM NA JEJ VYPOCITANIE.
				if (MState!=2)
					MEvent.WaitOne();

				// Ak vypocet hodnoty hodil Exception, tak ju hodim tiez.
				if (MException!=null)
					throw(MException);

				return(MValue);
			}
			set
			{
				// !!! Nastavujem hodnotu Promise.
				Set(value, null);
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void Set(T Value, Exception Exception)
		{
			// Thread safe sposobom nastavim hodnotu Promise.
			if (MState == 0 && Interlocked.CompareExchange(ref MState, 1, 0)==0)
			{
				MValue=Value;
				MException=Exception;

				// Signalizujem stav, ze hodnota Promise bola vypocitana.
				MState=2;
				MEvent.Set();

				lock (MResolveActions)
				{
					if (MException == null)
					{
						// Notifikujem registrovane CALLBACKS o vypocitani hodnoty.
						foreach (Action<T> A in MResolveActions)
						{
							ThreadPool.QueueUserWorkItem(delegate
							{
								A(MValue);
							});
						}
					}

					MResolveActions.Clear();
				}
			}
			else
			{
				// !!! Hodnotu je mozne nastavit IBA RAZ.
				throw new InvalidOperationException("Can only set once");
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public void Fail(Exception Exception)
		{
			Set(default(T), Exception);
		}
//------------------------------------------------------------------------------
		public void When(Action<T> ResolveAction)
		{
			lock (MResolveActions)
			{
				if (MState==2 && MException==null)
				{
					ThreadPool.QueueUserWorkItem(delegate
					{
						ResolveAction(MValue);
					});
				}
				else
					MResolveActions.Enqueue(ResolveAction);
			}
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------