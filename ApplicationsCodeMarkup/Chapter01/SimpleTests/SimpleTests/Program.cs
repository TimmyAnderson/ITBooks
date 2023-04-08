using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//------------------------------------------------------------------------------
namespace SimpleTests
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		[STAThread]
		static void Main(string[] args)
		{
			try
			{
				//CSayHallo.Do1();
				//CSayHallo.Do2();
				//CSayHallo.Do3();

				//CHandleAnEvent.Do();

				//CCurrentWindow.Do1();
				//CCurrentWindow.Do2();
				//CCurrentWindow.Do3();

				//CDialogWindowOwnsMessagePump.Do();

				//CKeyboardInput.Do();

				//CWindowStyle.Do1();
				//CWindowStyle.Do2();
				//CWindowStyle.Do3();
				//CWindowStyle.Do4();

				//CResizeMode.Do1();
				//CResizeMode.Do2();
				//CResizeMode.Do3();
				CResizeMode.Do4();
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