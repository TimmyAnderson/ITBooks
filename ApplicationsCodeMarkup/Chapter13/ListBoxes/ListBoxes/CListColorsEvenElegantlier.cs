using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
//------------------------------------------------------------------------------
namespace ListBoxes
{
//------------------------------------------------------------------------------
	public class CListColorsEvenElegantlier : Window
	{
//------------------------------------------------------------------------------
        public CListColorsEvenElegantlier()
        {
            Title="List Colors Even Elegantlier";

            // Vytvorim ItemTemplate, ktory obsahuje ITEMS typu CNamedBrush.
            DataTemplate				Template=new DataTemplate(typeof(CNamedBrush));

            // Vytvorim StackPanel, ktory bude obsahovat ELEMETNS pre ITEM.
            FrameworkElementFactory		FactoryStack=new FrameworkElementFactory(typeof(StackPanel));

            FactoryStack.SetValue(StackPanel.OrientationProperty, Orientation.Horizontal);

            // Vytvorim zo StackPanel VISUAL TREE ROOT.
            Template.VisualTree=FactoryStack;

            // Vytvorim FrameworkElementFactory pre Rectangle.
            FrameworkElementFactory		FactoryRectangle=new FrameworkElementFactory(typeof(Rectangle));

            FactoryRectangle.SetValue(Rectangle.WidthProperty,16.0);
            FactoryRectangle.SetValue(Rectangle.HeightProperty,16.0);
            FactoryRectangle.SetValue(Rectangle.MarginProperty,new Thickness(2));
            FactoryRectangle.SetValue(Rectangle.StrokeProperty,SystemColors.WindowTextBrush);

			// Nastavim BINDING, aby Fill DP bola mapovany na property Brush.
            FactoryRectangle.SetBinding(Rectangle.FillProperty,new Binding("Brush"));

            // Prihodm Rectangle ako CHILD StackPanel.
            FactoryStack.AppendChild(FactoryRectangle);

            // Vytvorim FrameworkElementFactory pre TextBlock.
            FrameworkElementFactory		FactoryTextBlock=new FrameworkElementFactory(typeof(TextBlock));

            FactoryTextBlock.SetValue(TextBlock.VerticalAlignmentProperty,VerticalAlignment.Center);
            FactoryTextBlock.SetBinding(TextBlock.TextProperty, new Binding("Name"));

            // Pridam TextBlock do StackPanel.
            FactoryStack.AppendChild(FactoryTextBlock);

            ListBox						LstBox=new ListBox();

            LstBox.Width=150;
            LstBox.Height=150;
            Content=LstBox;

            LstBox.ItemTemplate=Template;
            LstBox.ItemsSource=CNamedBrush.All;
            LstBox.SelectedValuePath="Brush";

            LstBox.SetBinding(ListBox.SelectedValueProperty, "Background");
            LstBox.DataContext=this;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------