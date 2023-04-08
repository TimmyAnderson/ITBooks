using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Documents;
//------------------------------------------------------------------------------
namespace RoutedEvents
{
//------------------------------------------------------------------------------
	public class CMyCoustomREWindow : Window
	{
//------------------------------------------------------------------------------
		// Deklarujem RE.
		public static readonly RoutedEvent			PreviewMySuperREEvent;
		public static readonly RoutedEvent			MySuperREEvent;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static CMyCoustomREWindow()
		{
			// Zaregistrujem RE.
			PreviewMySuperREEvent=EventManager.RegisterRoutedEvent("PreviewMySuperRE",RoutingStrategy.Tunnel,typeof(RoutedEvent),typeof(CMyCoustomREWindow));
			MySuperREEvent=EventManager.RegisterRoutedEvent("MySuperRE",RoutingStrategy.Bubble,typeof(RoutedEvent),typeof(CMyCoustomREWindow));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CMyCoustomREWindow()
        {
            Title="My CUSTOM RE";

			Button			But=new Button();

			But.Content="Click on me !";
			But.Click+=new RoutedEventHandler(But_Click);

			Content=But;
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		// Definujem .NET EVENTS pre RE na ktore sa je mozne pripojit.
//------------------------------------------------------------------------------
		public event RoutedEventHandler				PreviewMySuperRE
		{
			add
			{
				AddHandler(PreviewMySuperREEvent,value);
			}
			remove
			{
				RemoveHandler(PreviewMySuperREEvent,value);
			}
		}
//------------------------------------------------------------------------------
		public event RoutedEventHandler				MySuperRE
		{
			add
			{
				AddHandler(MySuperREEvent,value);
			}
			remove
			{
				RemoveHandler(MySuperREEvent,value);
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void But_Click(object Sender, RoutedEventArgs E)
		{
			RoutedEventArgs		REA1=new RoutedEventArgs(PreviewMySuperREEvent,this);
			RoutedEventArgs		REA2=new RoutedEventArgs(MySuperREEvent,this);

			// Vyvolam RE.
			RaiseEvent(REA1);

			if (REA1.Handled==false)
				RaiseEvent(REA2);
			else
				Console.WriteLine("\tBecause PreviewMySuperRE was HANDLED MySuperRE will NOT be RAISED !");
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------