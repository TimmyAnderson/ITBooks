using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
//-----------------------------------------------------------------------------------------------------------------
namespace XAML
{
//-----------------------------------------------------------------------------------------------------------------
	public partial class UseCustomXamlClass : Window
	{
//-----------------------------------------------------------------------------------------------------------------
        public UseCustomXamlClass()
        {
            InitializeComponent();

            for (int i=0;i<5;i++)
            {
                CenteredButton		Btn=new CenteredButton();

                Btn.Content="Button No. "+(i + 1);
                MStack.Children.Add(Btn);
            }
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------