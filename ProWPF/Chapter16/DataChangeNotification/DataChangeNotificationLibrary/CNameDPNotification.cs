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
namespace DataChangeNotificationLibrary
{
//------------------------------------------------------------------------
	public class CNameDPNotification : DependencyObject
	{
//------------------------------------------------------------------------
		public DependencyProperty				FirstNameProperty=DependencyProperty.Register("FirstName",typeof(string),typeof(CNameDPNotification));
		public DependencyProperty				LastNameProperty=DependencyProperty.Register("LastName",typeof(string),typeof(CNameDPNotification));
		public DependencyProperty				AgeProperty=DependencyProperty.Register("Age",typeof(int),typeof(CNameDPNotification));
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CNameDPNotification(string FirstName, string LastName, int Age)
		{
			this.FirstName=FirstName;
			this.LastName=LastName;
			this.Age=Age;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public string							FirstName
		{
			get
			{
				return((string) this.GetValue(FirstNameProperty));
			}
			set
			{
				this.SetValue(FirstNameProperty, value);
			}
		}
//------------------------------------------------------------------------
		public string							LastName
		{
			get
			{
				return((string) this.GetValue(LastNameProperty));
			}
			set
			{
				this.SetValue(LastNameProperty, value);
			}
		}
//------------------------------------------------------------------------
		public int								Age
		{
			get
			{
				return((int) this.GetValue(AgeProperty));
			}
			set
			{
				this.SetValue(AgeProperty, value);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("FN: {0}, LN: {1}, Age: {2} !",FirstName,LastName,Age));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------