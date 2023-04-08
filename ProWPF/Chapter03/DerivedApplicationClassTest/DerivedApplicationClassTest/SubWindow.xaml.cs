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
//------------------------------------------------------------------------
namespace DerivedApplicationClassTest
{
//------------------------------------------------------------------------
	public partial class SubWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		public SubWindow(int Counter)
		{
			InitializeComponent();

			MLabel1.Content=Counter;
			this.Title=Counter.ToString();

			// !!! Nacitam data z Application Class.
			CApp				App=(CApp) Application.Current;

			MLabel2.Content=App.MySharedData;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------