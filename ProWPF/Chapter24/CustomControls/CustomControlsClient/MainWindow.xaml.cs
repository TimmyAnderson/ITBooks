using System;
using System.Collections.Generic;
using System.Linq;
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
// 1. Program demonstruje vytvorenie Custom Controls.
// 2. CC sa vytvaraju menej casto ako vo WinForms, kedze standardne Elements sa daju dobre customizovat pomocou CT ci DT.
// !!!!! 3. Cielom UC na rozdiel od CC je POSKYTNUT DesignSurface do ktoreho vkladam Child Elements a tym vytvaram novy Custom Element. Avsak takyto UC sa neda velmi dobre skinovat a poddhadzovat mu CUSTOM Styles ci Themes LEBO JE ZAVISLY NA NATVRDO DEFINOVANOM XAML KODE UC. lepsim riesenim je zadefinovat tzv. Lookless Control.
//------------------------------------------------------------------------
namespace CustomControlsClient
{
//------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void Button_Click1(object Sender, RoutedEventArgs E)
		{
			CColorPicker1Window				Win=new CColorPicker1Window();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click2(object Sender, RoutedEventArgs E)
		{
			CColorPicker2Window				Win=new CColorPicker2Window();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------