using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
//------------------------------------------------------------------------------
namespace WinFormsSCTest
{
//------------------------------------------------------------------------------
	public partial class MFRMMainForm:Form
	{
//------------------------------------------------------------------------------
		private int							MCounter=0;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public MFRMMainForm()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void AsynchronousOperationFinished(object Param)
		{
			int				Value=(int) Param;

			MLABLabel.Text=string.Format("Asynchronous operation {0} FINISHED !",Value);
			MBUTButton.Enabled=true;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void ThreadFunction(object Param)
		{
			SynchronizationContext	SC=(SynchronizationContext) Param;

			// !!! Instalujem SC.
			SynchronizationContext.SetSynchronizationContext(SC);

			Thread.Sleep(3*1000);

			MCounter++;

			SynchronizationContext.Current.Post(AsynchronousOperationFinished,MCounter);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void MBUTButton_Click(object Sender, EventArgs E)
		{
			MBUTButton.Enabled=false;
			MLABLabel.Text="Asynchronous operation in progress !";

			Thread					T=new Thread(ThreadFunction);

			SynchronizationContext	SC=SynchronizationContext.Current.CreateCopy();

			T.Start(SC);
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------