using System;
using System.Collections.Generic;
using System.Linq;
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
namespace CustomControlsClient
{
//------------------------------------------------------------------------
	public partial class CColorPicker2Window:Window
	{
//------------------------------------------------------------------------
		public CColorPicker2Window()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		/*
		private void ColorPicker_ColorChanged1(object Sender, RoutedPropertyChangedEventArgs<Color> E)
		{
			if (MLBLColor1!=null)
				MLBLColor1.Content=string.Format("The new color is: {0} !",E.NewValue.ToString());
		}
//------------------------------------------------------------------------
		private void Button_Click1(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("Color: {0} !",MColorPicker1.Color));
			Debug.WriteLine(string.Format("Red: {0} !",MColorPicker1.Red));
			Debug.WriteLine(string.Format("Green: {0} !",MColorPicker1.Green));
			Debug.WriteLine(string.Format("Blue: {0} !",MColorPicker1.Blue));
		}
//------------------------------------------------------------------------
		private void ColorPicker_ColorChanged2(object Sender, RoutedPropertyChangedEventArgs<Color> E)
		{
			if (MLBLColor2!=null)
				MLBLColor2.Content=string.Format("The new color is: {0} !",E.NewValue.ToString());
		}
//------------------------------------------------------------------------
		private void Button_Click2(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("Color: {0} !",MColorPicker2.Color));
			Debug.WriteLine(string.Format("Red: {0} !",MColorPicker2.Red));
			Debug.WriteLine(string.Format("Green: {0} !",MColorPicker2.Green));
			Debug.WriteLine(string.Format("Blue: {0} !",MColorPicker2.Blue));
		}*/
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------