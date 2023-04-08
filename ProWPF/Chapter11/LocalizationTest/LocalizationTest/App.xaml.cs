using System;
using System.Windows;
using System.Data;
using System.Xml;
using System.Configuration;
using System.Threading;
using System.Globalization;
//------------------------------------------------------------------------
namespace LocalizationTest
{
//------------------------------------------------------------------------
	public partial class App:System.Windows.Application
	{
//------------------------------------------------------------------------
		public App()
		{
			// Zmenim jazykovu mutaciu.
			Thread.CurrentThread.CurrentUICulture=new CultureInfo("sk-SK");
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------