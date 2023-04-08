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
//------------------------------------------------------------------------------
namespace WPFTest
{
//------------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//------------------------------------------------------------------------------
		private int						MCounter=0;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void AsynchornousOperationFinished(int Value)
		{
			MLABLabel.Content=string.Format("Asynchronous operation {0} FINISHED !",Value);
			MBUTButton.IsEnabled=true;
		}
//------------------------------------------------------------------------------
		private void ThreadFunction()
		{
			Thread.Sleep(3*1000);

			DispatcherObject		DO=this;
			Dispatcher				D=DO.Dispatcher;

			MCounter++;

			D.Invoke(new Action<int>(AsynchornousOperationFinished),new object[]{MCounter});
		}
//------------------------------------------------------------------------------
		private void MBUTButton_Click(object Sender, RoutedEventArgs E)
		{
			MBUTButton.IsEnabled=false;
			MLABLabel.Content="Asynchronous operation in progress !";

			Thread					T=new Thread(ThreadFunction);

			T.Start();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------