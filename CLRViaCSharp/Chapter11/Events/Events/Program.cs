using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.ExceptionServices;
using System.ComponentModel;
//-------------------------------------------------------------------------------------------------------
namespace Events
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Action1(string Param)
		{
			Console.WriteLine(string.Format("ACTION 1 CALLED with PARAMETER [{0}] !",Param));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Action2(string Param1, string Param2)
		{
			Console.WriteLine(string.Format("ACTION 2 CALLED with PARAMETER_1 [{0}] and PARAMETER_2 [{0}] !",Param1,Param2));
		}
//-------------------------------------------------------------------------------------------------------
		private static void TimerCallback(object Sender, CTimerEventArgs EventArgs)
		{
			Console.WriteLine(string.Format("ID: [{0}], Time: [{1}] !",EventArgs.ID,EventArgs.ActualTime));
		}
//-------------------------------------------------------------------------------------------------------
		private static void CurrentDomain_FirstChanceException(object Sender, FirstChanceExceptionEventArgs E)
		{
			Console.WriteLine(string.Format("FIRST TIME EXCEPTION [{0}] was DETECTED !",E.Exception.Message));
		}
//-------------------------------------------------------------------------------------------------------
		private static void DerivedClassWithEvents_VirtualEvent(object Sender, EventArgs E)
		{
			Console.WriteLine(string.Format("VIRTUAL EVENT CALLED !"));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			AppDomain.CurrentDomain.FirstChanceException+=CurrentDomain_FirstChanceException;

			try
			{
				throw(new Exception("Some EXCEPTION 1 !"));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] was CAUGHT !",E.Message));
			}

			AppDomain.CurrentDomain.FirstChanceException-=CurrentDomain_FirstChanceException;

			try
			{
				throw(new Exception("Some EXCEPTION 2 !"));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] was CAUGHT !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CTimerManager										TM=new CTimerManager();

			TM.TimeChanged1+=TimerCallback;
			TM.TimeChanged2+=TimerCallback;
			TM.TimeChanged3+=TimerCallback;

			TM.StartTimer();

			TM.TimeChanged1-=TimerCallback;
			TM.TimeChanged2-=TimerCallback;
			TM.TimeChanged3-=TimerCallback;
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			CBaseClassWithEvents								ClassWithEvents=new CDerivedClassWithEvents();

			// !!! EVENT je OVERRIDEN v CDerivedClassWithEvents CLASS.
			ClassWithEvents.VirtualEvent+=DerivedClassWithEvents_VirtualEvent;

			ClassWithEvents.SimulateEvent();

			ClassWithEvents.VirtualEvent-=DerivedClassWithEvents_VirtualEvent;
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			EventHandlerList									TestEventHandlerList=new EventHandlerList();
			string												KEY1="Key1";
			string												KEY2="Key2";
			Delegate											Delegate11=new Action<string>(Action1);
			Delegate											Delegate12=new Action<string>(Action1);
			Delegate											Delegate21=new Action<string,string>(Action2);
			Delegate											Delegate22=new Action<string,string>(Action2);

			TestEventHandlerList.AddHandler(KEY1,Delegate11);
			TestEventHandlerList.AddHandler(KEY1,Delegate12);
			TestEventHandlerList.AddHandler(KEY2,Delegate21);
			TestEventHandlerList.AddHandler(KEY2,Delegate22);

			TestEventHandlerList[KEY1].DynamicInvoke("Timmy");

			TestEventHandlerList[KEY2].DynamicInvoke("Timmy","Anderson");

			TestEventHandlerList.RemoveHandler(KEY1,Delegate11);
			TestEventHandlerList.RemoveHandler(KEY1,Delegate12);
			TestEventHandlerList.RemoveHandler(KEY2,Delegate21);
			TestEventHandlerList.RemoveHandler(KEY2,Delegate22);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			Test4();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------