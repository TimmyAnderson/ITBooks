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
namespace DataBindingTest
{
//------------------------------------------------------------------------
	public partial class SimpleTwoElementsDB:System.Windows.Window
	{
//------------------------------------------------------------------------
		public SimpleTwoElementsDB()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnSetSmallSlider(object Sender, RoutedEventArgs E)
		{
			MSliderFontSize.Value=8;
		}
//------------------------------------------------------------------------
		private void OnSetNormalSlider(object Sender, RoutedEventArgs E)
		{
			MSliderFontSize.Value=16;
		}
//------------------------------------------------------------------------
		private void OnSetLargeSlider(object Sender, RoutedEventArgs E)
		{
			MSliderFontSize.Value=32;
		}
//------------------------------------------------------------------------
		private void OnSliderClearValue(object Sender, RoutedEventArgs E)
		{
			MSliderFontSize.ClearValue(Slider.ValueProperty);
		}
//------------------------------------------------------------------------
		private void OnSetSmallLabel(object Sender, RoutedEventArgs E)
		{
			// Nastavenie Label ZRUSI BINDING.
			MLBLSampleText.FontSize=8;
		}
//------------------------------------------------------------------------
		private void OnSetNormalLabel(object Sender, RoutedEventArgs E)
		{
			// Nastavenie Label ZRUSI BINDING.
			MLBLSampleText.FontSize=16;
		}
//------------------------------------------------------------------------
		private void OnSetLargeLabel(object Sender, RoutedEventArgs E)
		{
			// Nastavenie Label ZRUSI BINDING.
			MLBLSampleText.FontSize=32;
		}
//------------------------------------------------------------------------
		private void OnLabelClearValue(object Sender, RoutedEventArgs E)
		{
			// Ani ClearValue() NEOBNOVI zruseny BINDING.
			MLBLSampleText.ClearValue(TextBlock.FontSizeProperty);
		}
//------------------------------------------------------------------------
		private void OnCreateBinding(object Sender, RoutedEventArgs E)
		{
			Binding				Binding=new Binding();

			Binding.Source=MCodeSliderFontSize;
			// Alternativny sposob mapovania.
			//Binding.ElementName="MCodeSliderFontSize";

			Binding.Path=new PropertyPath("Value");
			// Pouzijem TwoWay binding.
			Binding.Mode=BindingMode.TwoWay;
			MLBLCodeSampleText.SetBinding(TextBlock.TextProperty, Binding);
		}
//------------------------------------------------------------------------
		private void OnDeleteBinding(object Sender, RoutedEventArgs E)
		{
			BindingOperations.ClearAllBindings(MLBLCodeSampleText);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------