using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SCCallbackLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SCCallbackClient
{
//-------------------------------------------------------------------------------------------------------
	public partial class CMainForm:Form
	{
//-------------------------------------------------------------------------------------------------------
		private CSCCallbackWithoutSCProxy						MClient1=null;
		private CSCCallbackWithSCProxy							MClient2=null;
		private NetTcpBinding									MTCPBinding1;
		private NetTcpBinding									MTCPBinding2;
		private CSCCallbackWithoutSCCatcher						MSCCallbackWithoutSCCatcher;
		private CSCCallbackWithSCCatcher						MSCCallbackWithSCCatcher;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMainForm()
		{
			InitializeComponent();

			MTCPBinding1=new NetTcpBinding();
			MTCPBinding2=new NetTcpBinding();

			MTCPBinding1.ReliableSession.Enabled=true;
			MTCPBinding2.ReliableSession.Enabled=true;

			MSCCallbackWithoutSCCatcher=new CSCCallbackWithoutSCCatcher(this,SynchronizationContext.Current);
			MSCCallbackWithSCCatcher=new CSCCallbackWithSCCatcher(this);

			MClient1=new CSCCallbackWithoutSCProxy(MSCCallbackWithoutSCCatcher,MTCPBinding1,"net.tcp://localhost:9001/ISCCallbackWithoutSCContract");
			MClient2=new CSCCallbackWithSCProxy(MSCCallbackWithSCCatcher,MTCPBinding2,"net.tcp://localhost:9002/ISCCallbackWithSCContract");

			MClient1.Connect("Client1");
			MClient2.Connect("Client2");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void EventCaller(object Param)
		{
			string		Data=(string) Param;

			MClient2.DoCallback(Data);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void MBUTWithout_Click(object sender,EventArgs e)
		{
			MClient1.DoCallback("WITHOUT");
		}
//-------------------------------------------------------------------------------------------------------
		private void MBUTWith_Click(object sender,EventArgs e)
		{
			Thread		T=new Thread(new ParameterizedThreadStart(EventCaller));

			T.Start("WITH");
		}
//-------------------------------------------------------------------------------------------------------
		private void MBUTExit_Click(object sender,EventArgs e)
		{
			Close();
		}
//-------------------------------------------------------------------------------------------------------
		private void CMainForm_FormClosed(object sender,FormClosedEventArgs e)
		{
			if (MClient1!=null && MClient1.State!=CommunicationState.Faulted)
			{
				MClient1.Disconnect();
				MClient1.Close();
				MClient1=null;
			}

			if (MClient2!=null && MClient2.State!=CommunicationState.Faulted)
			{
				MClient2.Disconnect();
				MClient2.Close();
				MClient2=null;
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------