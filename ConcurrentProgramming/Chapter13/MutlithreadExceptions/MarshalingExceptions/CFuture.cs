using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
#pragma warning disable 0420
//------------------------------------------------------------------------------
namespace MarshalingExceptions
{
//------------------------------------------------------------------------------
	public class CFuture<T>
	{
//------------------------------------------------------------------------------
		private static WaitCallback				MSCallback=Run;
//------------------------------------------------------------------------------
		// Stav Future: 0=unstarted, 1=running, 2=done.
		private volatile int					MState=0; 
		// Vypocitana hodnota Future.
		private T								MValue;
		// Exception, ktora vznikne pri vypocte hodnoty.
		private volatile Exception				MException;
		// Funkcia, ktora zabezpeci vypocet hodnoty Future.
		private Func<T>							MFunc;
		// KO na notifikaciu o konci vypoctu Future.
		private AutoResetEvent					MEvent=new AutoResetEvent(false);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CFuture(Func<T> Func)
		{
			MFunc=Func;
			ThreadPool.QueueUserWorkItem(MSCallback,this);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public T								Value
		{
			get
			{
				// !!! Ak este hodnota nie je k dispozicii, tak sa ju pokusim vypocitat.
				if (MState != 2 && TryRun()==false)
				{
					Console.WriteLine("Waiting for value computing to finish !");
					MEvent.WaitOne();
				}

				// Ak vypocet hodnoty hodil Exception, tak ju hodim tiez.
				if (MException!=null)
					throw(MException);

				return(MValue);
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Run(object Obj)
		{
			// !!! Tento kod je spusteny v PARALELNOM THREADE a robi VYPOCET HODNOTY na POZADI.
			((CFuture<T>)Obj).TryRun();
		}
//------------------------------------------------------------------------------
		private bool TryRun()
		{
			// Iba ak som bol v stave 0, tak realizujem vypocet.
			if (MState==0 && Interlocked.CompareExchange(ref MState,1,0)==0)
			{
				try
				{
					MValue=MFunc();
				}
				catch (Exception E)
				{
					MException=E;
				}
				finally
				{
					Console.WriteLine("FUTURE was calculated !");

					// Nastavim state DONE - vypocet bol skonceny.
					MState=2;
					MEvent.Set();
				}

				return(true);
			}

			return(false);
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------