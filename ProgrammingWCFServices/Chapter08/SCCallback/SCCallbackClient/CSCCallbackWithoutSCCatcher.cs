using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SCCallbackLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SCCallbackClient
{
//-------------------------------------------------------------------------------------------------------
	[CallbackBehavior(ConcurrencyMode=ConcurrencyMode.Single,UseSynchronizationContext=false)]
	class CSCCallbackWithoutSCCatcher : ISCCallbackWithoutSCCallback
	{
//-------------------------------------------------------------------------------------------------------
		private CMainForm										MMainForm;
		private SynchronizationContext							MSynchronizationContext;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSCCallbackWithoutSCCatcher(CMainForm MainForm, SynchronizationContext SynchronizationContext)
		{
			MMainForm=MainForm;
			MSynchronizationContext=SynchronizationContext;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void SetListBoxText(object Param)
		{
			string		Data=(string) Param;

			MMainForm.MLBXRecords.Items.Add(string.Format("SetListBoxText() - THREAD {0}: {1} !",Thread.CurrentThread.ManagedThreadId,Data));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void OnCallback(string Message)
		{
			SendOrPostCallback	SetText=new SendOrPostCallback(SetListBoxText);

			MSynchronizationContext.Post(SetText,Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------