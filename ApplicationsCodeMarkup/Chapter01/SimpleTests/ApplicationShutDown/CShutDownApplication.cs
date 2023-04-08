using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
//------------------------------------------------------------------------------
namespace ApplicationShutDown
{
//------------------------------------------------------------------------------
	public class CShutDownApplication : Application
	{
//------------------------------------------------------------------------------
        protected override void OnStartup(StartupEventArgs Args)
        {
            base.OnStartup(Args);

			// !!! Main Window vytvorim v OnStartup().
            Window				Win=new Window();

            Win.Title="Inherit the App";
            Win.Show();
        }
//------------------------------------------------------------------------------
		// Je volana, ak chcem spravit SHUTDOWN, alebo LOGOFF.
        protected override void OnSessionEnding(SessionEndingCancelEventArgs Args)
        {
            base.OnSessionEnding(Args);

            MessageBoxResult	Result=MessageBox.Show(string.Format("Do you want to save your data ? Reason [{0}] !",Args.ReasonSessionEnding),MainWindow.Title,MessageBoxButton.YesNoCancel,MessageBoxImage.Question,MessageBoxResult.Yes);

            Args.Cancel=(Result==MessageBoxResult.Cancel);
        }
//------------------------------------------------------------------------------
		protected override void OnExit(ExitEventArgs E)
		{
			base.OnExit(E);

			// Mozem nastavit ExitCode aplikacie.
			MessageBox.Show(string.Format("Exit Code: [{0}] !",E.ApplicationExitCode));
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------