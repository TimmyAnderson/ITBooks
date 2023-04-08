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
	public partial class SubPage:System.Windows.Controls.Page
	{
//------------------------------------------------------------------------
		public SubPage()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnPF1Click(object Sender, RoutedEventArgs E)
		{
			PageFunction1		PF=new PageFunction1();

			// Zaregistrujem Return Handler.
			PF.Return+=new ReturnEventHandler<int>(PF_Return1);
			// Navigujem sa na Page predanim vytvoreneho objektu.
			this.NavigationService.Navigate(PF);
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
		// Return Handler z PF1.
		private void PF_Return1(object Sender, ReturnEventArgs<int> E)
		{
			if (E!=null)
				MResult.Content=string.Format("Int Result: {0} !",E.Result);
			else
				MResult.Content=string.Format("Int Result: {0} !","CANCEL PRESSED");
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