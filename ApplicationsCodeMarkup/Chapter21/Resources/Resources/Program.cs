using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//-----------------------------------------------------------------------------------------------------------------
namespace DPInheritanceInXAML
{
//-----------------------------------------------------------------------------------------------------------------
	class Program
	{
//-----------------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CFontSizeResources				Win=new CFontSizeResources();

			// !!! Musim zavolat metodu InitializeComponent(), aby sa nacital XAML.
			Win.InitializeComponent();

			Application						App=new Application();

			App.Run(Win);
		}
//-----------------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CResourceLookupDemo				Win=new CResourceLookupDemo();

			// !!! Musim zavolat metodu InitializeComponent(), aby sa nacital XAML.
			Win.InitializeComponent();

			Application						App=new Application();

			App.Run(Win);
		}
//-----------------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			CDisplayCurrentDateTime			Win=new CDisplayCurrentDateTime();

			// !!! Musim zavolat metodu InitializeComponent(), aby sa nacital XAML.
			Win.InitializeComponent();

			Application						App=new Application();

			App.Run(Win);
		}
//-----------------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			CResourceKeyTest				Win=new CResourceKeyTest();

			// !!! Musim zavolat metodu InitializeComponent(), aby sa nacital XAML.
			Win.InitializeComponent();

			Application						App=new Application();

			App.Run(Win);
		}
//-----------------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			CDynamicResourceDemo			Win=new CDynamicResourceDemo();

			// !!! Musim zavolat metodu InitializeComponent(), aby sa nacital XAML.
			Win.InitializeComponent();

			Application						App=new Application();

			App.Run(Win);
		}
//-----------------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			CAnotherResourceLookupDemo		Win=new CAnotherResourceLookupDemo();

			// !!! Musim zavolat metodu InitializeComponent(), aby sa nacital XAML.
			Win.InitializeComponent();

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
				Test6();
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