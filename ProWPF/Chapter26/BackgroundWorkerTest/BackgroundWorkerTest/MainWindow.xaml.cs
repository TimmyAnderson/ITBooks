using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.ComponentModel;
using System.Threading;
using System.Windows;
using System.Windows.Threading;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
// 1. Program demonstruje multithreading v spojitosti s BackgroundWorker.
// 2. BW sluzi na vykonavanie metody v sekundarnom threade, pricom trhead sa vybera z thread pool a preto jeho pouzitie je jednoduche.
// 3. BW ma support pre NOTIFIKACIU O PERCENTE VYKONANIA ci MOZNOST CANCELLATION.
// !!! 4. CANCELLATION sa nedeje automaticky, ale SAM JU MUSIM OPROGRAOVAT testovanim property CancellationPending. Ak je nastavena na TRUE tak JA musim ukoncit funkciu v ktorej sa realizuje kod BW. Rucne musim nastavit Cancel priznak.
// !!! 5. Jednotlive eventy sa volaju v ramci threadu BW a teda su THREAD SAFE.
//------------------------------------------------------------------------
namespace BackgroundWorkerTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		public delegate void DAddToListBox(string Value);
//------------------------------------------------------------------------
		private BackgroundWorker				MBackgroundWorker;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();

			MBackgroundWorker=((BackgroundWorker) this.FindResource("MBackgroundWorker"));
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void AddToListBox(string Value)
		{
			this.MList.Items.Add(Value);
		}
//------------------------------------------------------------------------
		// !!! Tu sa vykonava kod BW.
		private void BackgroundWorker_DoWork(object Sender, DoWorkEventArgs E)
		{
			Debug.WriteLine(string.Format("!!! Input Argument: {0} !",E.Argument));

			int					Counter=10;

			while(Counter>0 && MBackgroundWorker.CancellationPending==false)
			{
				this.Dispatcher.BeginInvoke(DispatcherPriority.Normal,new DAddToListBox(this.AddToListBox),string.Format("Time to GO: {0} seconds remaining !",Counter));
				// !!! Notifikacia o Progress.
				MBackgroundWorker.ReportProgress((10-Counter)*10);
				Thread.Sleep(1000);
				Counter--;
			}

			// !!! Rucne musim nastavit Cancel priznak.
			if (MBackgroundWorker.CancellationPending==true)
				E.Cancel=true;

			E.Result="XYZ";
		}
//------------------------------------------------------------------------
		// Vykona sa ked BW skonci. Je vykonany v ROVNAKOM THREADE ako telo BW.
		private void BackgroundWorker_RunWorkerCompleted(object Sender, RunWorkerCompletedEventArgs E)
		{
			if (E.Cancelled==false)
				Debug.WriteLine(string.Format("!!! FINISHED - Result: {0} !",E.Result));

			Debug.WriteLine(string.Format("!!! FINISHED - Cancelled: {0} !",E.Cancelled));
			Debug.WriteLine(string.Format("!!! FINISHED - Error: {0} !",E.Error));
		}
//------------------------------------------------------------------------
		private void BackgroundWorker_ProgressChanged(object Sender, ProgressChangedEventArgs E)
		{
			Debug.WriteLine(string.Format("!!! PROGRESS at {0}% !",E.ProgressPercentage));
			Debug.WriteLine(string.Format("!!! PROGRESS - UserState: {0} !",E.UserState));
		}
//------------------------------------------------------------------------
		private void OnStartTimerClick(object Sender, RoutedEventArgs E)
		{
			MList.Items.Clear();
			MBackgroundWorker.RunWorkerAsync("ABC");
		}
//------------------------------------------------------------------------
		private void OnCancelClick(object Sender, RoutedEventArgs E)
		{
			// Vykona Cancel.
			MBackgroundWorker.CancelAsync();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------