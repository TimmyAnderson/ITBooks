using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace Events
{
//-------------------------------------------------------------------------------------------------------
	public class CTimerManager
	{
//-------------------------------------------------------------------------------------------------------
		private readonly object									MLock=new object();
//-------------------------------------------------------------------------------------------------------
		// !!! Ak EXPLICITNE DEFINUJEM EVENT, tak C# NEGENERUJE INSTANCIU DELEGATE EXPLICITNE a musim ju definovat sam.
		private EventHandler<CTimerEventArgs>					MTimeChanged2;
		private EventHandler<CTimerEventArgs>					MTimeChanged3;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public event EventHandler<CTimerEventArgs>				TimeChanged1;
//-------------------------------------------------------------------------------------------------------
		// !!! Explicitne definovana metoda add_TimeChanged2() a remove_TimeChanged2().
		public event EventHandler<CTimerEventArgs>				TimeChanged2
		{
			add
			{
				Console.WriteLine("Method add_TimeChanged2() CALLED !");

				MTimeChanged2+=value;
			}
			remove
			{
				Console.WriteLine("Method remove_TimeChanged2() CALLED !");

				MTimeChanged2-=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Explicitne definovana metoda add_TimeChanged3() a remove_TimeChanged3().
		public event EventHandler<CTimerEventArgs>				TimeChanged3
		{
			add
			{
				Console.WriteLine("Method add_TimeChanged3() CALLED !");

				lock(MLock)
				{
					MTimeChanged3+=value;
				}
			}
			remove
			{
				Console.WriteLine("Method remove_TimeChanged3() CALLED !");

				lock(MLock)
				{
					MTimeChanged3-=value;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected void OnTimeChanged1(CTimerEventArgs TimerEventArgs)
		{
			// !!!!! Aby vykonavanie EVENTS bolo THREAD SAFE je NUTNE ulozit EVENT do TEMPORARY VARIABLE. Tym sa zabrani vzniku [NullReferenceException], ak by po vykonani IF prikazu a vyvolanim EVENT iny THREAD ODSTRANIL EVENT HANDLER a EVENT by mal hodnotu NULL.
			// !!!!! Na priradenie EVENT do TEMPORARY VARIABLE je NUTNE pouzit METHOD Volatile.Read(). To zabrani, aby COMPILER vykonal optimalizaciu, ktora by v RELEASE BUILDS NEVYTVORILA 'Temp1' VARIABLE. Kedze sa vsak pouzije METHOD Volatile.Read(), tak sa TEMPORARY VARIABLE VYTVORI aj v RELEASE BUILDS.
			EventHandler<CTimerEventArgs>						Temp1=Volatile.Read(ref TimeChanged1);

			if (Temp1!=null)
			{
				Temp1(this,TimerEventArgs);
			}
		}
//-------------------------------------------------------------------------------------------------------
		protected void OnTimeChanged2(CTimerEventArgs TimerEventArgs)
		{
			// !!!!! Aby vykonavanie EVENTS bolo THREAD SAFE je NUTNE ulozit EVENT do TEMPORARY VARIABLE. Tym sa zabrani vzniku [NullReferenceException], ak by po vykonani IF prikazu a vyvolanim EVENT iny THREAD ODSTRANIL EVENT HANDLER a EVENT by mal hodnotu NULL.
			// !!!!! Na priradenie EVENT do TEMPORARY VARIABLE je NUTNE pouzit METHOD Volatile.Read(). To zabrani, aby COMPILER vykonal optimalizaciu, ktora by v RELEASE BUILDS NEVYTVORILA 'Temp2' VARIABLE. Kedze sa vsak pouzije METHOD Volatile.Read(), tak sa TEMPORARY VARIABLE VYTVORI aj v RELEASE BUILDS.
			EventHandler<CTimerEventArgs>						Temp2=Volatile.Read(ref MTimeChanged2);

			if (Temp2!=null)
			{
				Temp2(this,TimerEventArgs);
			}
		}
//-------------------------------------------------------------------------------------------------------
		protected void OnTimeChanged3(CTimerEventArgs TimerEventArgs)
		{
			EventHandler<CTimerEventArgs>						Temp3;

			lock(MLock)
			{
				Temp3=MTimeChanged3;
			}

			if (Temp3!=null)
			{
				Temp3(this,TimerEventArgs);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void StartTimer()
		{
			for(int Index=0;Index<5;Index++)
			{
				OnTimeChanged1(new CTimerEventArgs("TimeChanged1",DateTime.Now));
				OnTimeChanged2(new CTimerEventArgs("TimeChanged2",DateTime.Now));
				OnTimeChanged3(new CTimerEventArgs("TimeChanged3",DateTime.Now));

				Thread.Sleep(1000);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------