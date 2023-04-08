using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace CustomPanels
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void Test1()
		{
			CCustomUniformGridWindow		Win=new CCustomUniformGridWindow(1);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			CCustomUniformGridWindow		Win=new CCustomUniformGridWindow(2);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			CCustomUniformGridWindow		Win=new CCustomUniformGridWindow(3);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test4()
		{
			CCustomUniformGridWindow		Win=new CCustomUniformGridWindow(4);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test5()
		{
			CCustomUniformGridWindow		Win=new CCustomUniformGridWindow(5);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		[STAThread]
		static void Main(string[] args)
		{
			try
			{
				//Test1();
				//Test2();
				//Test3();
				//Test4();
				Test5();
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