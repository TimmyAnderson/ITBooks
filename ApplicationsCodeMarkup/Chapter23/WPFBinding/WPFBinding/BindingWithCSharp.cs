using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Data;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
//-------------------------------------------------------------------------------------------------------
namespace WPFBinding
{
//-------------------------------------------------------------------------------------------------------
	public partial class BindingWithCSharp : Window
	{
//-------------------------------------------------------------------------------------------------------
		public BindingWithCSharp()
		{
			InitializeComponent();

			// Vytvorim Binding objekt.
			Binding			Bind=new Binding();

			// Nastavim jeho SOURCE na 'MScroll'.
			Bind.ElementName="MScroll";
			// Ako SOURCE PROPERTY je ScrollBar.ValueProperty.
			Bind.Path=new PropertyPath(ScrollBar.ValueProperty);

			// Aplikujem Binding na TARGER - MLabel.
			// !!! SetBinding() je definovany vo FrameworkElement.
			MLabel.SetBinding(Label.ContentProperty,Bind);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------