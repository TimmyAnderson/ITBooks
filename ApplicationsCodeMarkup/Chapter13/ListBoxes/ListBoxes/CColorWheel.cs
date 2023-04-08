using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
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
	public class CColorWheel : ListBox
	{
//------------------------------------------------------------------------------
        public CColorWheel()
        {
            // Definujem ItemsPanel TEMPLATE.
            FrameworkElementFactory		FactoryRadialPanel=new FrameworkElementFactory(typeof(CRadialPanel));

			// Nastavim ItemsPanel.
            ItemsPanel=new ItemsPanelTemplate(FactoryRadialPanel);

            // Definujem ItemTemplate TEMPLATE.
            DataTemplate				Template=new DataTemplate(typeof(Brush));

			// Nastavim ItemTemplate.
            ItemTemplate=Template;

            FrameworkElementFactory		ElRectangle=new FrameworkElementFactory(typeof(Rectangle));

            ElRectangle.SetValue(Rectangle.WidthProperty,4.0);
            ElRectangle.SetValue(Rectangle.HeightProperty,12.0);
            ElRectangle.SetValue(Rectangle.MarginProperty,new Thickness(1,8,1,8));
            ElRectangle.SetBinding(Rectangle.FillProperty, new Binding(""));

            Template.VisualTree=ElRectangle;

            PropertyInfo[]				Props=typeof(Brushes).GetProperties();

            foreach (PropertyInfo Prop in Props)
                Items.Add((Brush)Prop.GetValue(null, null));
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------