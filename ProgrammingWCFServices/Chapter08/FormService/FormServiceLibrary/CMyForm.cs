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
//--------------------------------------------------------------------------------------------------------------------------------
namespace FormServiceLibrary
{
//--------------------------------------------------------------------------------------------------------------------------------
	public partial class CMyForm:Form
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private CServiceHostWrapperCollection					MServiceHostWrapperCollection;
		private CServiceHostWrapper<CFormServiceService>		MService;
		private NetTcpBinding									MTCPBinding;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMyForm()
		{
			Console.WriteLine(string.Format("TID - CMyForm(): {0} !",Thread.CurrentThread.ManagedThreadId));
			InitializeComponent();

			MServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			MService=new CServiceHostWrapper<CFormServiceService>();
			MTCPBinding=new NetTcpBinding();

			MServiceHostWrapperCollection.AddServiceHostWrapper(MService);

			// Nastavim reliability na session.
			MTCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			MTCPBinding.TransactionFlow=true;

			MService.AddServiceEndpoint<IFormServiceContract>(MTCPBinding,"net.tcp://localhost:9001/IFormServiceContract");

			MService.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

			// Otvaram service.
			MServiceHostWrapperCollection.StartServices();
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public int Counter
		{
			get
			{
				Console.WriteLine(string.Format("TID - Counter.get(): {0} !",Thread.CurrentThread.ManagedThreadId));
				return(Convert.ToInt32(MLABCounter.Text));
			}
			set
			{
				Console.WriteLine(string.Format("TID - Counter.set(): {0} !",Thread.CurrentThread.ManagedThreadId));
				MLABCounter.Text=value.ToString();
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void MBUTExit_Click(object sender,EventArgs e)
		{
			this.Close();
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void CMyForm_FormClosed(object sender,FormClosedEventArgs e)
		{
			// Zatvaram service.
			MServiceHostWrapperCollection.StopServices();
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------