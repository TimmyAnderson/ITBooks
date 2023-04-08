using System;
using System.Collections.Generic;
using System.Diagnostics;
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
//------------------------------------------------------------------------
namespace ApplicationClassTest
{
//------------------------------------------------------------------------
	public class CMain
	{
//------------------------------------------------------------------------
		public static string GetTypeNameWOArity(string Name)
		{
			int		Position;

			if ((Position=Name.LastIndexOf('`'))!=-1)
				return(Name.Remove(Position));
			else
				return(Name);
		}
//-----------------------------------------------------------------------------
		// Vrati meno triedy s generic parametrami, alebo iba do urovne 1.
		public static string GetTypeName(Type Type)
		{
			Type[]				GenericTypes=Type.GetGenericArguments();

			if (GenericTypes.Length==0)
				return(Type.Name);

			StringBuilder		SB=new StringBuilder();

			SB.Append(GetTypeNameWOArity(Type.Name));
			SB.Append("<");

			for (int i=0;i<GenericTypes.Length;i++)
			{
				if (i!=0)
					SB.Append(",");

				SB.Append(GenericTypes[i].Name);
			}

			SB.Append(">");

			return(SB.ToString());
		}
//------------------------------------------------------------------------
		private static void ShowMethodName()
		{
			StackFrame		SF=new StackFrame(1);

			Debug.WriteLine(string.Format("!!! {0}.{1}() CALLED !",GetTypeName(SF.GetMethod().DeclaringType),SF.GetMethod().Name));
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		static void App_Startup(object Sender, StartupEventArgs E)
		{
			Debug.WriteLine(string.Format("Input parameter COUNT: {0} !",E.Args.Length));

			for (int i=0;i<E.Args.Length;i++)
				Debug.WriteLine(string.Format("\tParameter[{0}]: {1} !",i+1,E.Args[i]));
	
			ShowMethodName();
		}
//------------------------------------------------------------------------
		private static void App_Activated(object Sender, EventArgs E)
		{
			ShowMethodName();
		}
//------------------------------------------------------------------------
		private static void App_Deactivated(object Sender, EventArgs E)
		{
			ShowMethodName();
		}
//------------------------------------------------------------------------
		private static void App_Exit(object Sender, ExitEventArgs E)
		{
			ShowMethodName();

			Debug.WriteLine(string.Format("!!! ApplicationExitCode: {0} !",E.ApplicationExitCode));
		}
//------------------------------------------------------------------------
		static void App_SessionEnding(object Sender, SessionEndingCancelEventArgs E)
		{
			ShowMethodName();

			Debug.WriteLine(string.Format("!!! ReasonSessionEnding: {0} !",E.ReasonSessionEnding));

			if (MessageBox.Show("Close Window ?","Exit",MessageBoxButton.YesNo)==MessageBoxResult.No)
				E.Cancel=true;
		}
//------------------------------------------------------------------------
		static void App_DispatcherUnhandledException(object Sender, DispatcherUnhandledExceptionEventArgs E)
		{
			ShowMethodName();

			// !!! Ak je to ApplicationException tak ju sparcujem a PROGRAM BUDE DALEJ BEZAT.
			if (E.Exception.GetType()==typeof(ApplicationException))
			{
				E.Handled=true;
				Debug.WriteLine("!!! Unhandled Exception HANDLED !!!");
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		[STAThread()]
		public static void Main(string[] Args)
		{
			Application			App=new Application();

			App.Startup+=new StartupEventHandler(App_Startup);
			App.Activated+=new EventHandler(App_Activated);
			App.Deactivated+=new EventHandler(App_Deactivated);
			App.Exit+=new ExitEventHandler(App_Exit);
			App.SessionEnding+=new SessionEndingCancelEventHandler(App_SessionEnding);
			App.DispatcherUnhandledException+=new DispatcherUnhandledExceptionEventHandler(App_DispatcherUnhandledException);

			App.MainWindow=new MainWindow();

			int					Ret=App.Run(App.MainWindow);

			Debug.WriteLine(string.Format("!!! Run() RETURNED: {0} !",Ret));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------