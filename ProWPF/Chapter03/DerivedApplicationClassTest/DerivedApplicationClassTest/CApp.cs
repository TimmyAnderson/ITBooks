using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
namespace DerivedApplicationClassTest
{
//------------------------------------------------------------------------
	public class CApp : Application
	{
//------------------------------------------------------------------------
		private string					MMySharedData;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CApp()
		{
			MMySharedData="Hello World !";
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public string					MySharedData
		{
			get
			{
				return(MMySharedData);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		[STAThread()]
		public static void Main(string[] Args)
		{
			CApp				App=new CApp();

			App.StartupUri=new Uri("MainWindow.xaml", UriKind.Relative);
			App.Run();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		protected override void OnActivated(EventArgs E)
		{
			base.OnActivated(E);

			Debug.WriteLine("!!! OnActivated() CALLED !");
		}
//------------------------------------------------------------------------
		protected override void OnDeactivated(EventArgs E)
		{
			base.OnDeactivated(E);

			Debug.WriteLine("!!! OnDeactivated() CALLED !");
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------