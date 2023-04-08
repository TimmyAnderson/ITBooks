using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
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
namespace ListViewTestLibrary
{
//------------------------------------------------------------------------
	public class CNameWithPhoto : INotifyPropertyChanged
	{
//------------------------------------------------------------------------
		private string								MFirstName;
		private string								MLastName;
		private int									MAge;
		private string								MPhoto;
//------------------------------------------------------------------------
		public event PropertyChangedEventHandler	PropertyChanged;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CNameWithPhoto(string FirstName, string LastName, int Age, string Photo)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
			MPhoto=Photo;
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

				if (PropertyChanged!=null)
				{
					// !!! Ak dam do PropertyChangedEventArgs prazdny string tak sa updateuje kazda property.
					PropertyChanged(this,new PropertyChangedEventArgs("FirstName"));
				}
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

				if (PropertyChanged!=null)
				{
					// !!! Ak dam do PropertyChangedEventArgs prazdny string tak sa updateuje kazda property.
					PropertyChanged(this,new PropertyChangedEventArgs("LastName"));
				}
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

				if (PropertyChanged!=null)
				{
					// !!! Ak dam do PropertyChangedEventArgs prazdny string tak sa updateuje kazda property.
					PropertyChanged(this,new PropertyChangedEventArgs("Age"));
				}
			}
		}
//------------------------------------------------------------------------
		public string								Photo
		{
			get
			{
				return(MPhoto);
			}
			set
			{
				MPhoto=value;

				if (PropertyChanged!=null)
				{
					// !!! Ak dam do PropertyChangedEventArgs prazdny string tak sa updateuje kazda property.
					PropertyChanged(this,new PropertyChangedEventArgs("Photo"));
				}
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