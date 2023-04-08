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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Threading;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace SynchronizationContextTaskScheduler
{
//-------------------------------------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//-------------------------------------------------------------------------------------------------------
		private CancellationTokenSource							MCTS;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! Tato TASK METHOD sa vykonava v THREAD POOL THREADE.
		private static int SumTaskWithCancellation(object Param)
		{
			CancellationToken									CT=(CancellationToken) Param;
			int													Ret=0;
			
			for (int i=0;i<300;i++)
			{
				if (CT.WaitHandle.WaitOne(10)==true)
				{
					// !!! Vykonanie CANCELLATION oznamujem vratenim OperationCanceledException.
					throw(new OperationCanceledException("Operation WAS CANCELLED !",CT));
				}

				Ret++;
			}

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! Tato TASK METHOD sa vykonava v GUI THREADE.
		private void TaskSucceeded(Task<int> Task)
		{
			MBUTStart.IsEnabled=true;
			MBUTCancel.IsEnabled=false;
			MLSTList.Items.Add(string.Format("TASK FINISHED SUCCESSFULLY with RESULT: [{0}] !",Task.Result));
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Tato TASK METHOD sa vykonava v GUI THREADE.
		private void TaskFailed(Task<int> Task)
		{
			MBUTStart.IsEnabled=true;
			MBUTCancel.IsEnabled=false;
			MLSTList.Items.Add("TASK FAILED !");
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Tato TASK METHOD sa vykonava v GUI THREADE.
		private void TaskCanceled(Task<int> Task)
		{
			MBUTStart.IsEnabled=true;
			MBUTCancel.IsEnabled=false;
			MLSTList.Items.Add("TASK WAS CANCELLED !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void MBUTStart_Click(object Sender, RoutedEventArgs E)
		{
			MBUTStart.IsEnabled=false;
			MBUTCancel.IsEnabled=true;

			MCTS=new CancellationTokenSource();

			// !!! Tento TASK pouziva STANDARDNY SCHEDULER a teda je vykonavany v TP THREADE.
			Task<int>											SomeTask=new Task<int>(SumTaskWithCancellation,MCTS.Token,MCTS.Token);

			TaskScheduler										SynchronizationContextTaskScheduler=TaskScheduler.FromCurrentSynchronizationContext();

			// !!! Tieto TASKS UZ BUDU SPUSTENE cez SYNCHRONIZATION CONTEXT TASK SCHEDULER a teda budu vykonavane v MAIN GUI THREADE.
			SomeTask.ContinueWith(TaskSucceeded,CancellationToken.None,TaskContinuationOptions.OnlyOnRanToCompletion,SynchronizationContextTaskScheduler);
			SomeTask.ContinueWith(TaskFailed,CancellationToken.None,TaskContinuationOptions.OnlyOnFaulted,SynchronizationContextTaskScheduler);
			SomeTask.ContinueWith(TaskCanceled,CancellationToken.None,TaskContinuationOptions.OnlyOnCanceled,SynchronizationContextTaskScheduler);

			MLSTList.Items.Add("ALL TASKS CREATED !");

			SomeTask.Start();

			MLSTList.Items.Add("Main TASK STARTED !");
		}
//-------------------------------------------------------------------------------------------------------
		private void MBUTCancel_Click(object Sender, RoutedEventArgs E)
		{
			MBUTCancel.IsEnabled=false;
			MCTS.Cancel();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------