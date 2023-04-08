using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//-----------------------------------------------------------------------------------------------------------------
namespace XAML
{
//-----------------------------------------------------------------------------------------------------------------
	class Program
	{
//-----------------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			XamlReaderTest					Win=new XamlReaderTest();
			Application						App=new Application();

			App.Run(Win);
		}
//-----------------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			LoadXamlResource				Win=new LoadXamlResource();
			Application						App=new Application();

			App.Run(Win);
		}
//-----------------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			LoadXamlWindow.Start();
		}
//-----------------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			LoadXamlFile					Win=new LoadXamlFile();
			Application						App=new Application();

			App.Run(Win);
		}
//-----------------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			CompileXamlWindow				Win=new CompileXamlWindow();
			Application						App=new Application();

			App.Run(Win);
		}
//-----------------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			UseCustomClass					Win=new UseCustomClass();
			Application						App=new Application();

			App.Run(Win);
		}
//-----------------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			UseCustomXamlClass				Win=new UseCustomXamlClass();
			Application						App=new Application();

			App.Run(Win);
		}
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
		[STAThread]
		static void Main(string[] args)
		{
			try
			{
				//Test1();
				//Test2();
				//Test3();
				//Test4();
				//Test5();
				//Test6();
				Test7();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadKey();
		}
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------