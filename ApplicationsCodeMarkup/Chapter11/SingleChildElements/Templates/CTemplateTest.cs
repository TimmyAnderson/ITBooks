using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Threading;
//------------------------------------------------------------------------------
namespace Templates
{
//------------------------------------------------------------------------------
	public class CTemplateTest : Window
	{
//------------------------------------------------------------------------------
        public CTemplateTest()
        {
            Title="Build Button Factory";

			ControlTemplate		MyTemplate=CreateTemplate();

            // Na tento BUTTON APLIKUJEM TEMPLATE.
            Button				Btn=new Button();

            // Aplikujem CUSTOM TEMPLATE.
            Btn.Template=MyTemplate;

            Btn.Content="Button with Custom Template";
            Btn.Padding=new Thickness(20);
            Btn.FontSize=48;
            Btn.HorizontalAlignment=HorizontalAlignment.Center;
            Btn.VerticalAlignment=VerticalAlignment.Center;
            Btn.Click+=ButtonOnClick;

            Content=Btn;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private ControlTemplate CreateTemplate()
		{
            // Vytvorim ControlTemplate pre element typu BUTTON.
			// Takato Template moze byt aplikovana IBA NA BUTTONS.
            ControlTemplate				Template=new ControlTemplate(typeof(Button));

            // Vytvorim PROXY TRIEDU FrameworkElementFactory reprezentujucu BORDER BUTTON.
            FrameworkElementFactory		FactoryBorder=new FrameworkElementFactory(typeof(Border));

            FactoryBorder.Name="MBUTBorder";
            //FactoryBorder.Name="border";

            // Nastavim niektore DP na FrameworkElementFactory reprezentujucu BORDER.
            FactoryBorder.SetValue(Border.BorderBrushProperty, Brushes.Red);
            FactoryBorder.SetValue(Border.BorderThicknessProperty, new Thickness(3));
            FactoryBorder.SetValue(Border.BackgroundProperty, SystemColors.ControlLightBrush);

            // Vytvorim PROXY TRIEDU FrameworkElementFactory reprezentujucu ContentPresenter, ktory WRAPPUJE obsah BUTTON.
            FrameworkElementFactory		FactoryContent=new FrameworkElementFactory(typeof(ContentPresenter));

            FactoryContent.Name="MCNPContent";
            //FactoryContent.Name="content";

            // !!! Bindujem BUTTON DP 'ContentProperty' na DP 'ContentProperty' ContentPresenter.
			// !!!!! Tymto dosiahnem, ze ContentProperty.ContentProperty==Button.ContentProperty a teda, ze TO CO DEFINUJEM v property Content pre BUTTON sa stane Content v ContentPresenter a teda bude vytvarat obsah Button.
            FactoryContent.SetValue(ContentPresenter.ContentProperty, new TemplateBindingExtension(Button.ContentProperty));

            // Bindujem BUTTON DP 'PaddingProperty' na DP 'MarginProperty' ContentPresenter.
            FactoryContent.SetValue(ContentPresenter.MarginProperty, new TemplateBindingExtension(Button.PaddingProperty));

            // !!! Pridam FACTORY pre ContentPresenter do FACTORY pre BUTTON.
            FactoryBorder.AppendChild(FactoryContent);

            // !!! Urobim z BORDER ROOT pre TEMPLATE.
            Template.VisualTree=FactoryBorder;

			/*
            Trigger						Trig1=new Trigger();

            // Definujem TRIGGER na DP IsMouseOver==true.
            Trig1.Property=UIElement.IsMouseOverProperty;
            Trig1.Value=true;

            Setter						Set1=new Setter();

            // Do TRIGGER pridam SETTER, ktory zmeni hodnou DP CornerRadiusProperty elementu BORDER.
            Set1.Property=Border.CornerRadiusProperty;
            Set1.Value=new CornerRadius(24);
			// !!! Ako TagetName nastavim MENO BORDER.
            Set1.TargetName="MBUTBorder";

            // Pridam SETTER do TRIGGER.
            Trig1.Setters.Add(Set1);

            Setter						Set2=new Setter();

            // Do TRIGGER PRIDAM DALSI SETTER, ktory zmeni font na ITALICS.
            Set2.Property=Control.FontStyleProperty;
            Set2.Value=FontStyles.Italic;

            // Pridam SETTER do TRIGGER.
            Trig1.Setters.Add(Set2);

            // Pridam TRIGGER do kolekcie TRIGGERS.
            Template.Triggers.Add(Trig1);

            Trigger						Trig2=new Trigger();

            // Definujem TRIGGER na DP IsPressedProperty==true.
            Trig2.Property=Button.IsPressedProperty;
            Trig2.Value=true;

            Setter						Set3=new Setter();

            // Do TRIGGER pridam SETTER, ktory zmeni hodnou DP BackgroundProperty elementu BORDER.
            Set3.Property=Border.BackgroundProperty;
            Set3.Value=SystemColors.ControlDarkBrush;
			// !!! Ako TagetName nastavim MENO BORDER.
            Set3.TargetName="MBUTBorder";

            // Pridam SETTER do TRIGGER.
            Trig2.Setters.Add(Set3);

            // Pridam TRIGGER do kolekcie TRIGGERS.
            Template.Triggers.Add(Trig2);
			*/

			return(Template);
		}
//------------------------------------------------------------------------------
        private void ButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            MessageBox.Show("You clicked the button !", Title);
        } 
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------