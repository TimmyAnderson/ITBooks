using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Threading;
using System.Windows.Forms;
//-------------------------------------------------------------------------------------------------------
namespace SCGUILibrary
{
//-------------------------------------------------------------------------------------------------------
	public partial class CMyForm:Form
	{
//-------------------------------------------------------------------------------------------------------
		private SynchronizationContext							MMySynchronizationContext;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMyForm()
		{
			Console.WriteLine(string.Format("TID - CMyForm(): {0} !",Thread.CurrentThread.ManagedThreadId));
			InitializeComponent();
			MMySynchronizationContext=SynchronizationContext.Current;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public SynchronizationContext	MySynchronizationContext
		{
			get
			{
				return(MMySynchronizationContext);
			}
		}
//-------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void MBUTExit_Click(object sender,EventArgs e)
		{
			this.Close();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------