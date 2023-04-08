using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Data;
//-------------------------------------------------------------------------------------------------------
namespace WPFBinding
{
//-------------------------------------------------------------------------------------------------------
	public partial class UpdateSourceTriggerTest : Window
	{
//-------------------------------------------------------------------------------------------------------
		public UpdateSourceTriggerTest()
		{
			InitializeComponent();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void UpdateSourceClick(object Sender, RoutedEventArgs E)
		{
			// Ziskam BindingExpression.
			BindingExpression			BE1=MMyTxb1.GetBindingExpression(TextBox.TextProperty);
			BindingExpression			BE2=MMyTxb2.GetBindingExpression(TextBox.TextProperty);
			BindingExpression			BE3=MMyTxb3.GetBindingExpression(TextBox.TextProperty);

			BE1.UpdateSource();
			BE2.UpdateSource();
			BE3.UpdateSource();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------