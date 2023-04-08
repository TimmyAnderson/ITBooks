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
using System.Windows.Navigation;
using System.Windows.Shapes;
//------------------------------------------------------------------------
namespace PageHistoryTestClient
{
//------------------------------------------------------------------------
	public partial class JournalDPPage:System.Windows.Controls.Page
	{
//------------------------------------------------------------------------
		private static DependencyProperty	MyValueProperty;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		static JournalDPPage()
		{
			FrameworkPropertyMetadata		Metadata=new FrameworkPropertyMetadata();

			// !!! Hodnota sa bude zapisovat do Journal.
			Metadata.Journal=true;

			MyValueProperty=DependencyProperty.Register("MyValue", typeof(string), typeof(JournalDPPage), Metadata, null);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public JournalDPPage()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public string						MyValue
		{
			get
			{
				return((string)GetValue(MyValueProperty));
			}
			set
			{ 
				SetValue(MyValueProperty, value);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnLoadClick(object Sender, RoutedEventArgs E)
		{
			MResult.Content=MyValue;
		}
//------------------------------------------------------------------------
		private void OnSaveClick(object Sender, RoutedEventArgs E)
		{
			MyValue=MTextBox.Text;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------