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
namespace WinFormsTest
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
		private void AsynchornousOperationFinished(int Value)
		{
			MLABLabel.Text=string.Format("Asynchronous operation {0} FINISHED !",Value);
			MBUTButton.Enabled=true;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void ThreadFunction()
		{
			Thread.Sleep(3*1000);

			ISynchronizeInvoke		SI=this;

			MCounter++;

			SI.Invoke(new Action<int>(AsynchornousOperationFinished),new object[]{MCounter});
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void MBUTButton_Click(object Sender, EventArgs E)
		{
			MBUTButton.Enabled=false;
			MLABLabel.Text="Asynchronous operation in progress !";

			Thread					T=new Thread(ThreadFunction);

			T.Start();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------