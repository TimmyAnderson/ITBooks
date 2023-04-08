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
//------------------------------------------------------------------------
namespace EAP
{
//------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//------------------------------------------------------------------------
		private CMyEAPManager									MManager;
//------------------------------------------------------------------------
		public event EventHandler<CXXXCompletedEventArgs>		XXXCompleted;
		public event EventHandler<CXXXProgressChangedEventArgs>	XXXProgressChanged;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();

			MManager=new CMyEAPManager(this);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void WriteToLog(string LogText)
		{
			LBXListBox.Items.Add(LogText);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void Window_Loaded(object Sender, RoutedEventArgs E)
		{
			XXXCompleted+=new EventHandler<CXXXCompletedEventArgs>(MainWindow_XXXCompleted);
			XXXProgressChanged+=new EventHandler<CXXXProgressChangedEventArgs>(MainWindow_XXXProgressChanged);
		}
//------------------------------------------------------------------------
		private void MainWindow_XXXCompleted(object Sender, CXXXCompletedEventArgs E)
		{
			try
			{
				string		Result=E.Result;
				string		Text=string.Format("ACTION: [{0}], RESULT: [{1}] !",E.UserState,Result);

				WriteToLog(Text);
			}
			catch(Exception Ex)
			{
				string		Text=string.Format("ACTION: [{0}], EXCEPTION: [{1}] !",E.UserState,Ex.InnerException.Message);

				WriteToLog(Text);
			}
		}
//------------------------------------------------------------------------
		private void MainWindow_XXXProgressChanged(object Sender, CXXXProgressChangedEventArgs E)
		{
			string		Text=string.Format("ACTION: [{0}], PERCENTAGE: [{1}] !",E.UserState,E.ProgressPercentage);

			WriteToLog(Text);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void BUTStartActionTimmy_Click(object Sender, RoutedEventArgs E)
		{
			bool			IsOK;

			IsOK=MManager.XXXAsync("Timmy","111");

			if (IsOK==false)
				WriteToLog("START Timmy FAILED !");
			else
				WriteToLog("START Timmy OK !");
		}
//------------------------------------------------------------------------
		private void BUTStartActionJenny_Click(object Sender,RoutedEventArgs E)
		{
			bool			IsOK;

			IsOK=MManager.XXXAsync("Jenny","222");

			if (IsOK==false)
				WriteToLog("START Jenny FAILED !");
			else
				WriteToLog("START Jenny OK !");
		}
//------------------------------------------------------------------------
		private void BUTCancelActionTimmy_Click(object Sender,RoutedEventArgs E)
		{
			bool			IsOK;

			IsOK=MManager.XXXCancelAsync("111");

			if (IsOK==false)
				WriteToLog("CANCEL Timmy FAILED !");
			else
				WriteToLog("CANCEL Timmy OK !");
		}
//------------------------------------------------------------------------
		private void BUTCancelActionJenny_Click(object Sender,RoutedEventArgs E)
		{
			bool			IsOK;

			IsOK=MManager.XXXCancelAsync("222");

			if (IsOK==false)
				WriteToLog("CANCEL Jenny FAILED !");
			else
				WriteToLog("CANCEL Jenny OK !");
		}
//------------------------------------------------------------------------
		private void BUTExceptionActionTimmy_Click(object Sender,RoutedEventArgs E)
		{
			bool			IsOK;

			IsOK=MManager.SimulateException("111");

			if (IsOK==false)
				WriteToLog("EXCEPTION Timmy FAILED !");
			else
				WriteToLog("EXCEPTION Timmy OK !");
		}
//------------------------------------------------------------------------
		private void BUTExceptionActionJenny_Click(object Sender,RoutedEventArgs E)
		{
			bool			IsOK;

			IsOK=MManager.SimulateException("222");

			if (IsOK==false)
				WriteToLog("EXCEPTION Jenny FAILED !");
			else
				WriteToLog("EXCEPTION Jenny OK !");
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		internal void OnXXXCompleted(CXXXCompletedEventArgs CC)
		{
			if (XXXCompleted!=null)
				XXXCompleted(this,CC);
		}
//------------------------------------------------------------------------
		internal void OnXXXProgressChanged(CXXXProgressChangedEventArgs PC)
		{
			if (XXXProgressChanged!=null)
				XXXProgressChanged(this,PC);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------