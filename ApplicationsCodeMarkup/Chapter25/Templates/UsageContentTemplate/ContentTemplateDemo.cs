using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace UsageContentTemplate
{
//-------------------------------------------------------------------------------------------------------
	public partial class ContentTemplateDemo : Window
	{
//-------------------------------------------------------------------------------------------------------
        public ContentTemplateDemo()
        {
            InitializeComponent();
            
            EmployeeButton		Btn=new EmployeeButton();

            Btn.Content=new Employee("Jim", "Images\\Jim.png", new DateTime(1975, 6, 15), false);
            MStack.Children.Add(Btn);
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void EmployeeButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            Button				Btn=Args.Source as Button;
            Employee			Emp=Btn.Content as Employee;

            MessageBox.Show(string.Format("{0} button clicked !",Emp.Name), Title);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------