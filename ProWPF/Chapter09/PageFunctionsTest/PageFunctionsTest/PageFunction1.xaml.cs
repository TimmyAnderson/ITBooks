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
namespace PageFunctionsTest
{
//------------------------------------------------------------------------
	public partial class PageFunction1:System.Windows.Navigation.PageFunction<int>
	{
//------------------------------------------------------------------------
		public PageFunction1()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnOKClick(object Sender, RoutedEventArgs E)
		{
			int				Value1;
			int				Value2;

			if (int.TryParse(MValue1.Text, out Value1)==false || int.TryParse(MValue2.Text, out Value2)==false)
			{
				MessageBox.Show("Invalid Value !");
				return;
			}

			int				Result=Value1+Value2;

			OnReturn(new ReturnEventArgs<int>(Result));
		}
//------------------------------------------------------------------------
		private void OnCancelClick(object Sender, RoutedEventArgs E)
		{
			// !!! FP sa skonci, ale bez navratovej hodnoty.
			OnReturn(null);
		}
//------------------------------------------------------------------------
		private void OnPF2Click(object Sender, RoutedEventArgs E)
		{
			PageFunction2		PF=new PageFunction2();

			// Zaregistrujem Return Handler.
			PF.Return+=new ReturnEventHandler<string>(PF_Return2);
			// Navigujem sa na Page predanim vytvoreneho objektu.
			this.NavigationService.Navigate(PF);
		}
//------------------------------------------------------------------------
		// Return Handler z PF2.
		private void PF_Return2(object Sender, ReturnEventArgs<string> E)
		{
			if (E!=null)
				MResult.Content=string.Format("String Result: {0} !",E.Result);
			else
				MResult.Content=string.Format("String Result: {0} !","CANCEL PRESSED");
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------