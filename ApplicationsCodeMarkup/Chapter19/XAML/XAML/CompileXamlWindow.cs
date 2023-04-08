using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
//-----------------------------------------------------------------------------------------------------------------
namespace XAML
{
//-----------------------------------------------------------------------------------------------------------------
	public partial class CompileXamlWindow : Window
	{
//-----------------------------------------------------------------------------------------------------------------
        public CompileXamlWindow()
        {
			// Tato metoda je AUTOMATICKY GENEROVANA v subore na pozadi.
            InitializeComponent();

            foreach (PropertyInfo Prop in typeof(Brushes).GetProperties())
                MListBox.Items.Add(Prop.Name);
        }
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        private void ButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            Button			Btn=Sender as Button;

            MessageBox.Show(string.Format("The button labeled '{0}' has been clicked !",(Args.Source as Button).Content));
        }
//-----------------------------------------------------------------------------------------------------------------
        private void ListBoxOnSelection(object Sender, SelectionChangedEventArgs Args)
        {
            ListBox				LstBox=Sender as ListBox;
            string				StrItem=LstBox.SelectedItem as string;
            PropertyInfo		Prop=typeof(Brushes).GetProperty(StrItem);

            MEllipse.Fill = (Brush)Prop.GetValue(null, null);
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------