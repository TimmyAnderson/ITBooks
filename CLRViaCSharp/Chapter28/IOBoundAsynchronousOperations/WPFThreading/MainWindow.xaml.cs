using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Runtime.CompilerServices;
//-------------------------------------------------------------------------------------------------------
namespace WPFThreading
{
//-------------------------------------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//-------------------------------------------------------------------------------------------------------
		private readonly SynchronizationContext					MCurrentSynchronizationContext;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();

			MCurrentSynchronizationContext=SynchronizationContext.Current;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void WriteToLog(string Message)
		{
			string												MessageWithTime=string.Format("TIME: [{0}], CALLING THREAD [{1}], {2}",DateTime.Now.ToString("hh:mm:ss"),Thread.CurrentThread.ManagedThreadId,Message);

			MCurrentSynchronizationContext.Post(P => MLSVListView.Items.Add(MessageWithTime),null);
		}
//-------------------------------------------------------------------------------------------------------
		private void SlowFunction()
		{
			WriteToLog("SlowFunction() STARTED !");

			Thread.Sleep(2000);

			WriteToLog("SlowFunction() FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private async Task DeadlockAsychronousFunction()
		{
			WriteToLog("DeadlockAsychronousFunction() STARTED !");

			Task												TestTask=new Task(SlowFunction);

			TestTask.Start();

			WriteToLog("DeadlockAsychronousFunction() AWAITING BEGINS !");

			await TestTask;

			WriteToLog("DeadlockAsychronousFunction() AWAITING ENDS !");

			WriteToLog("DeadlockAsychronousFunction() FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private async Task NoDeadlockAsychronousFunction()
		{
			WriteToLog("NoDeadlockAsychronousFunction() STARTED !");

			Task												TestTask=new Task(SlowFunction);

			TestTask.Start();

			WriteToLog("NoDeadlockAsychronousFunction() AWAITING BEGINS !");

			// !!! Vytvori sa AWAITEBLE CLASS, ktore NEVYUZIVA SYNCHRONIZATION CONTEXT.
			ConfiguredTaskAwaitable								AwaitableTask=TestTask.ConfigureAwait(false);

			// !!!!! Nesposobi DEADLOCK, pretoze OPERATOR AWAIT pouziva ConfiguredTaskAwaitable, vytvoreny volanim METHOD Task.ConfigureAwait(false).
			await AwaitableTask;

			WriteToLog("NoDeadlockAsychronousFunction() AWAITING ENDS !");

			WriteToLog("NoDeadlockAsychronousFunction() FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!!!! Sposobi DEADLOCK.
		private void MBUTDeadlock_Click(object Sender, RoutedEventArgs E)
		{
			WriteToLog("DEADLOCK TEST STARTED !");

			Task												AsynchronousFunctionTask=DeadlockAsychronousFunction();

			// !!!!! Sposobi DEADLOCK.
			AsynchronousFunctionTask.Wait();

			WriteToLog("DEADLOCK TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private void MBUTNoDeadlock_Click(object Sender, RoutedEventArgs E)
		{
			WriteToLog("NO-DEADLOCK TEST STARTED !");

			Task												AsynchronousFunctionTask=NoDeadlockAsychronousFunction();

			// !!!!! Nesposobi DEADLOCK, pretoze ASYNCHRONOUS FUNCTION vola METHOD Task.ConfigureAwait(false).
			AsynchronousFunctionTask.Wait();

			WriteToLog("NO-DEADLOCK TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private void MBUTClear_Click(object Sender, RoutedEventArgs E)
		{
			MLSVListView.Items.Clear();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------