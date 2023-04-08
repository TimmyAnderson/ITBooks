using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Printing;
//------------------------------------------------------------------------
namespace PrintingTest
{
//------------------------------------------------------------------------
	public partial class PrintQueues:Window
	{
//------------------------------------------------------------------------
        private PrintServer				MPrintServer=new PrintServer();
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public PrintQueues()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void Window_Loaded(object Sender, EventArgs E)
        {
            MLSTQueues.DisplayMemberPath="FullName";
            MLSTQueues.SelectedValuePath="FullName";
            MLSTQueues.ItemsSource=MPrintServer.GetPrintQueues();   
        }
//------------------------------------------------------------------------
        private void LstQueues_SelectionChanged(object Sender, SelectionChangedEventArgs E)
        {
            PrintQueue				Queue=MPrintServer.GetPrintQueue(MLSTQueues.SelectedValue.ToString());

            MLBLQueueStatus.Text=string.Format("Queue Status: {0} !", Queue.QueueStatus.ToString());
            MLBLJobStatus.Text="";
            MLSTJobs.DisplayMemberPath="JobName";
            MLSTJobs.SelectedValuePath="JobIdentifier";

            MLSTJobs.ItemsSource=Queue.GetPrintJobInfoCollection();
        }
//------------------------------------------------------------------------
        private void LstJobs_SelectionChanged(object Sender, SelectionChangedEventArgs E)
        {
            if (MLSTJobs.SelectedValue==null)
            {
                MLBLJobStatus.Text="";
            }
            else
            {
                PrintQueue				Queue=MPrintServer.GetPrintQueue(MLSTQueues.SelectedValue.ToString());
                PrintSystemJobInfo		Job=Queue.GetJob((int) MLSTJobs.SelectedValue);

                MLBLJobStatus.Text=string.Format("Job Status: {0} !", Job.JobStatus.ToString());
            }
        }
//------------------------------------------------------------------------
        private void CmdPauseQueue_Click(object Sender, RoutedEventArgs E)
        {            
            if (MLSTQueues.SelectedValue!=null)
            {
                PrintQueue				Queue=MPrintServer.GetPrintQueue(MLSTQueues.SelectedValue.ToString());

                Queue.Pause();
            }
        }
//------------------------------------------------------------------------
        private void CmdResumeQueue_Click(object Sender, RoutedEventArgs E)
        {
            if (MLSTQueues.SelectedValue!=null)
            {
                PrintQueue				Queue=MPrintServer.GetPrintQueue(MLSTQueues.SelectedValue.ToString());

                Queue.Resume();
            }
        }
//------------------------------------------------------------------------
        private void CmdRefreshQueue_Click(object Sender, RoutedEventArgs E)
        {
            if (MLSTQueues.SelectedValue!=null)
            {
                PrintQueue				Queue=MPrintServer.GetPrintQueue(MLSTQueues.SelectedValue.ToString());

                Queue.Refresh();
            }
        }
//------------------------------------------------------------------------
        private void CmdPurgeQueue_Click(object Sender, RoutedEventArgs E)
        {
            if (MLSTQueues.SelectedValue != null)
            {
                PrintQueue				Queue=MPrintServer.GetPrintQueue(MLSTQueues.SelectedValue.ToString());

                Queue.Purge();
            }
        }
//------------------------------------------------------------------------
        private void CmdPauseJob_Click(object Sender, RoutedEventArgs E)
        {
            if (MLSTJobs.SelectedValue != null)
            {
                PrintQueue				Queue=MPrintServer.GetPrintQueue(MLSTQueues.SelectedValue.ToString());
                PrintSystemJobInfo		Job=Queue.GetJob((int) MLSTJobs.SelectedValue);

                Job.Pause();
            }
        }
//------------------------------------------------------------------------
        private void CmdResumeJob_Click(object Sender, RoutedEventArgs E)
        {
            if (MLSTJobs.SelectedValue!=null)
            {
                PrintQueue				Queue=MPrintServer.GetPrintQueue(MLSTQueues.SelectedValue.ToString());
                PrintSystemJobInfo		Job=Queue.GetJob((int) MLSTJobs.SelectedValue);

                Job.Resume();
            }
        }
//------------------------------------------------------------------------
        private void CmdRefreshJob_Click(object Sender, RoutedEventArgs E)
        {
            if (MLSTJobs.SelectedValue!=null)
            {
                PrintQueue				Queue=MPrintServer.GetPrintQueue(MLSTQueues.SelectedValue.ToString());
                PrintSystemJobInfo		Job=Queue.GetJob((int) MLSTJobs.SelectedValue);

                Job.Refresh();
                LstJobs_SelectionChanged(null, null);
            }
        }
//------------------------------------------------------------------------
        private void CmdCancelJob_Click(object Sender, RoutedEventArgs E)
        {
            if (MLSTJobs.SelectedValue!=null)
            {
                PrintQueue				Queue=MPrintServer.GetPrintQueue(MLSTQueues.SelectedValue.ToString());
                PrintSystemJobInfo		Job=Queue.GetJob((int) MLSTJobs.SelectedValue);

                Job.Cancel();

                LstQueues_SelectionChanged(null, null);
            }
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------