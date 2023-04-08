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
namespace TransformationsTests
{
//------------------------------------------------------------------------
	public partial class DynamicTransformation:System.Windows.Window
	{
//------------------------------------------------------------------------
		private double						MAngle=30;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public DynamicTransformation()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnClick(object Sender, RoutedEventArgs E)
		{
			MAngle+=5;

			// Aplikovanim transformacie sa ta hned prejavi v GUI.
			RotateTransform		NewTransform=new RotateTransform(MAngle);

			MButton.LayoutTransform=NewTransform;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------