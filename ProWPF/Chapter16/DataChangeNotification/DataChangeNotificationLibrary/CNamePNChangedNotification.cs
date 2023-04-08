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
using System.ComponentModel;
//------------------------------------------------------------------------
namespace DataChangeNotificationLibrary
{
//------------------------------------------------------------------------
	public class CNamePNChangedNotification
	{
//------------------------------------------------------------------------
		private string								MFirstName;
		private string								MLastName;
		private int									MAge;
//------------------------------------------------------------------------
		// !!! MUSI BYT TYPU EventHandler.
		public event EventHandler					FirstNameChanged;
		public event EventHandler					LastNameChanged;
		public event EventHandler					AgeChanged;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CNamePNChangedNotification(string FirstName, string LastName, int Age)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public string								FirstName
		{
			get
			{
				return(MFirstName);
			}
			set
			{
				MFirstName=value;

				if (FirstNameChanged!=null)
					FirstNameChanged(this,null);
			}
		}
//------------------------------------------------------------------------
		public string								LastName
		{
			get
			{
				return(MLastName);
			}
			set
			{
				MLastName=value;

				if (LastNameChanged!=null)
					LastNameChanged(this,null);
			}
		}
//------------------------------------------------------------------------
		public int									Age
		{
			get
			{
				return(MAge);
			}
			set
			{
				MAge=value;

				if (AgeChanged!=null)
					AgeChanged(this,null);
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