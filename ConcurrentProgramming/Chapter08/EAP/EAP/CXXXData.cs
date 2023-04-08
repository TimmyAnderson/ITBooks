using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Diagnostics;
//------------------------------------------------------------------------
namespace EAP
{
//------------------------------------------------------------------------
	public class CXXXData
	{
//------------------------------------------------------------------------
		private const int						MAX_COUNT=10;
//------------------------------------------------------------------------
		private object							MObject;
		private string							MInputValue;
		private SynchronizationContext			MSC;
		private SendOrPostCallback				MWindowCompletedCallback;
		private SendOrPostCallback				MWindowProgressChangedCallback;
//------------------------------------------------------------------------
		private ManualResetEvent				MCancelEvent;
		private ManualResetEvent				MSimulateExceptionEvent;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CXXXData(object Object, string InputValue, SynchronizationContext SC, SendOrPostCallback WindowCompletedCallback, SendOrPostCallback WindowProgressChangedCallback)
		{
			MCancelEvent=new ManualResetEvent(false);
			MSimulateExceptionEvent=new ManualResetEvent(false);

			MObject=Object;
			MInputValue=InputValue;
			MSC=SC;
			MWindowCompletedCallback=WindowCompletedCallback;
			MWindowProgressChangedCallback=WindowProgressChangedCallback;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void ThreadMethod(object State)
		{
			Debug.WriteLine(string.Format("!!! ACTION: [{0}] STARTED !",MInputValue));

			int				Count=0;
			bool			WasCancelled=false;
			Exception		ThrowException=null;
			// Simulujem nejaku navratovu hodnotu.
			string			OutpuValue=MInputValue.ToUpper();

			while(Count<MAX_COUNT)
			{
				Console.WriteLine(string.Format("ACTION: [{0}], Count: {1} !",MInputValue,Count+1));

				if (MCancelEvent.WaitOne(1000,true)==true)
				{
					Debug.WriteLine(string.Format("!!! ACTION: [{0}] IS GOING TO BE CANCELLED !",MInputValue));
					WasCancelled=true;
					break;
				}

				if (MSimulateExceptionEvent.WaitOne(0,true)==true)
				{
					Debug.WriteLine(string.Format("??? ACTION: [{0}] IS GOINT TO THROW EXCEPTION !",MInputValue));
					ThrowException=new Exception(string.Format("ACTION: [{0}] THROWN EXCEPTION !",MInputValue));
					break;
				}
				
				int									Percent=(100*Count)/MAX_COUNT;

				// Posielam info o progrese.
				CXXXProgressChangedEventArgs		PC=new CXXXProgressChangedEventArgs(Percent,MObject,MInputValue);

				MSC.Post(MWindowProgressChangedCallback,PC);
				Count++;
			}

			CXXXCompletedEventArgs		EA=new CXXXCompletedEventArgs(ThrowException,WasCancelled,MObject,OutpuValue);

			MSC.Post(MWindowCompletedCallback,EA);

			Debug.WriteLine(string.Format("!!! ACTION: [{0}] FINISHED !",MInputValue));
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public void StartWork()
		{
			ThreadPool.QueueUserWorkItem(this.ThreadMethod,null);
		}
//------------------------------------------------------------------------
		public void Cancel()
		{
			MCancelEvent.Set();
		}
//------------------------------------------------------------------------
		public void SimulateException()
		{
			MSimulateExceptionEvent.Set();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------