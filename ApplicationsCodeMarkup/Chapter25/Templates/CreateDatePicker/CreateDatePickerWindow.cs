using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace CreateDatePicker
{
//-------------------------------------------------------------------------------------------------------
	public partial class CreateDatePickerWindow : Window
	{
//-------------------------------------------------------------------------------------------------------
        public CreateDatePickerWindow()
        {
            InitializeComponent();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void DatePickerOnDateChanged(object Sender, RoutedPropertyChangedEventArgs<DateTime?> Args)
        {
            if (Args.NewValue != null)
            {
                DateTime		DT=(DateTime) Args.NewValue;

                MTxtblkDate.Text=DT.ToString("d");
            }
            else
                MTxtblkDate.Text="";
        }
//-------------------------------------------------------------------------------------------------------
	}
}
//-------------------------------------------------------------------------------------------------------