using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace MySynchronizationContext
{
//-------------------------------------------------------------------------------------------------------
	internal class CWorkerThread : IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private object											MSyn=new object();
		private SynchronizationContext							MSynchronizationContext;
		private Thread											MThread;
		private AutoResetEvent									MExitEvent;
		private AutoResetEvent									MNewItemEvent;
		private Queue<CWorkItem>								MQueue;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CWorkerThread(SynchronizationContext SC)
		{
			MSynchronizationContext=SC;
			MThread=new Thread(new ThreadStart(WorkerThread));
			MExitEvent=new AutoResetEvent(false);
			MNewItemEvent=new AutoResetEvent(false);
			MQueue=new Queue<CWorkItem>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void WorkerThread()
		{
			SynchronizationContext.SetSynchronizationContext(MSynchronizationContext);

			WaitHandle[]		WH=new WaitHandle[2];

			WH[0]=MExitEvent;
			WH[1]=MNewItemEvent;

			while(true)
			{
				int				Index=WaitHandle.WaitAny(WH);

				if (Index==0)
					break;

				while(true)
				{
					if (MExitEvent.WaitOne(0,false)==true)
						break;

					CWorkItem	WorkItem=Pop();

					if (WorkItem==null)
						break;

					WorkItem.DoCall();
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private CWorkItem Pop()
		{
			lock(MSyn)
			{
				if (MQueue.Count>0)
					return(MQueue.Dequeue());
				else
					return(null);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal void Push(CWorkItem WorkItem)
		{
			lock(MSyn)
			{
				MQueue.Enqueue(WorkItem);
				MNewItemEvent.Set();
			}
		}
//-------------------------------------------------------------------------------------------------------
		internal void Start()
		{
			lock(MSyn)
			{
				MThread.Start();
			}
		}
//-------------------------------------------------------------------------------------------------------
		internal void Stop()
		{
			lock(MSyn)
			{
				MExitEvent.Set();
				MThread.Join();
				MThread=null;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Stop();

			if (MExitEvent!=null)
			{
				MExitEvent.Close();
				MExitEvent=null;
			}

			if (MNewItemEvent!=null)
			{
				MNewItemEvent.Close();
				MNewItemEvent=null;
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------