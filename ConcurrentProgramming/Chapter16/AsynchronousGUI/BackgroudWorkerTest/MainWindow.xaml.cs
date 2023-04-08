using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Threading;
using System.ComponentModel;
//------------------------------------------------------------------------------
namespace BackgroudWorkerTest
{
//------------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//------------------------------------------------------------------------------
		private BackgroundWorker					MBW=new BackgroundWorker();
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();

			MBW.DoWork+=new DoWorkEventHandler(MBW_DoWork);
			MBW.RunWorkerCompleted+=new RunWorkerCompletedEventHandler(MBW_RunWorkerCompleted);
			MBW.ProgressChanged+=new ProgressChangedEventHandler(MBW_ProgressChanged);

			MBW.WorkerReportsProgress=true;
			MBW.WorkerSupportsCancellation=true;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void MBW_DoWork(object Sender, DoWorkEventArgs E)
		{
			int			Counter=0;

			while(MBW.CancellationPending==false)
			{
				Counter+=10;
				MBW.ReportProgress(Counter);
				Thread.Sleep(1000);

				if (Counter>=100)
					break;
			}

			E.Cancel=MBW.CancellationPending;
			E.Result="Timmy";
		}
//------------------------------------------------------------------------------
		private void MBW_RunWorkerCompleted(object Sender, RunWorkerCompletedEventArgs E)
		{
			if (E.Cancelled==false)
				MLBXListBox.Items.Add(string.Format("Work finished - Result: [{0}], Cancelled: [{1}], Error: [{2}]",E.Result,E.Cancelled,E.Error));
			else
				MLBXListBox.Items.Add(string.Format("Work finished - Cancelled: [{0}], Error: [{1}]",E.Cancelled,E.Error));

			MBUTButton.IsEnabled=true;
			MBUTCancel.IsEnabled=false;
		}
//------------------------------------------------------------------------------
		private void MBW_ProgressChanged(object Sender, ProgressChangedEventArgs E)
		{
			MLBXListBox.Items.Add(string.Format("Counter [{0}]",E.ProgressPercentage));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void MBUTButton_Click(object Sender, RoutedEventArgs E)
		{
			MLBXListBox.Items.Clear();
			MBUTButton.IsEnabled=false;
			MBUTCancel.IsEnabled=true;
			MLBXListBox.Items.Add("Asynchronous operation in progress !");

			MBW.RunWorkerAsync();
		}
//------------------------------------------------------------------------------
		private void MBUTCancel_Click(object Sender, RoutedEventArgs E)
		{
			MBW.CancelAsync();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------