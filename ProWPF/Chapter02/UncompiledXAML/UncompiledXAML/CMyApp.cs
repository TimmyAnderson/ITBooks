using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.IO;
using System.Windows.Markup;
//------------------------------------------------------------------------
namespace UncompiledXAML
{
//------------------------------------------------------------------------
	public class CMyApp
	{
//------------------------------------------------------------------------
		[STAThread()]
		public static void Main(string[] Args)
		{
			Application			App=new Application();

			App.MainWindow=new CMainWindow();
			App.MainWindow.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------