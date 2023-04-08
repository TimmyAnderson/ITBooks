using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace FreezableObjects
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void B_Changed(object Sender, EventArgs E)
		{
			SolidColorBrush	SCB=(SolidColorBrush) Sender;

			Console.WriteLine(string.Format("Event CHANGED - Brush color is: [{0}] !",SCB.Color));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test()
		{
			SolidColorBrush	B=new SolidColorBrush(Colors.Red);

			B.Changed+=new EventHandler(B_Changed);

			B.Color=Colors.Green;
			B.Color=Colors.Green;
			B.Color=Colors.Green;
			B.Color=Colors.Green;
			B.Color=Colors.Green;

			Console.WriteLine("Brush WILL be FROZEN !");

			B.Freeze();

			Console.WriteLine("Brush is FROZEN !");

			try
			{
				// Teraz uz nezmeni hodnotu.
				B.Color=Colors.Blue;
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			SolidColorBrush	NewBrush=B.Clone();

			NewBrush.Changed+=new EventHandler(B_Changed);

			// Klonovany objekt je UNFROZEN.
			NewBrush.Color=Colors.Blue;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		[STAThread]
		static void Main(string[] args)
		{
			try
			{
				Test();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadKey();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------