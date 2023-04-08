using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
//------------------------------------------------------------------------------
namespace SimpleTests
{
//------------------------------------------------------------------------------
	public class CDialogWindowOwnsMessagePump
	{
//------------------------------------------------------------------------------
		public static void Do()
		{
			// !!! Application NEMUSIM VOBEC VYTVARAT, kedze DIALOG WINDOW ma VLASTNU MESSAGE PUMP.
			/*
            Application		App=new Application();

            App.Run();
			*/

			Console.WriteLine(string.Format("1. Application.Current [{0}] !",Application.Current));

            Window			Win=new Window();

            Win.Title="DIALOG Window";

			Console.WriteLine(string.Format("2. Application.Current [{0}] !",Application.Current));

			// Spustam DIALOG WINDOW MESSAGE PUMP.
            Win.ShowDialog();

			Console.WriteLine(string.Format("3. Application.Current [{0}] !",Application.Current));
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------