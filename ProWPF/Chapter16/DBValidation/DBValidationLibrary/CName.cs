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
namespace DBValidationLibrary
{
//------------------------------------------------------------------------
	public class CName : INotifyPropertyChanged, IDataErrorInfo
	{
//------------------------------------------------------------------------
		private string								MFirstName;
		private string								MLastName;
		private int									MAge;
		private string								MError=null;
		private bool								MErrorFirstName=false;
		private bool								MErrorLastName=false;
		private bool								MErrorAge=false;
//------------------------------------------------------------------------
		public event PropertyChangedEventHandler	PropertyChanged;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CName(string FirstName, string LastName, int Age)
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
				Debug.WriteLine(string.Format("CName.FirstName: {0} !",1));

				MFirstName=value;

				if (MFirstName.Length>10)
				{
					MErrorFirstName=true;
					MError="FirstName is too LONG !";
				}
				else
				{
					MErrorFirstName=false;
					MError=null;
				}

				if (PropertyChanged!=null)
				{
					// !!! Ak dam do PropertyChangedEventArgs prazdny string tak sa updateuje kazda property.
					PropertyChanged(this,new PropertyChangedEventArgs("FirstName"));
				}

				Debug.WriteLine(string.Format("CName.FirstName: {0} !",2));

				if (MErrorFirstName==true)
					throw(new Exception("SETTER Says: FirstName INVALID !"));					
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
				Debug.WriteLine(string.Format("CName.LastName: {0} !",1));

				MLastName=value;

				if (MLastName.Length>10)
				{
					MErrorLastName=true;
					MError="LastName is too LONG !";
				}
				else
				{
					MErrorLastName=false;
					MError=null;
				}

				if (PropertyChanged!=null)
				{
					// !!! Ak dam do PropertyChangedEventArgs prazdny string tak sa updateuje kazda property.
					PropertyChanged(this,new PropertyChangedEventArgs("LastName"));
				}

				Debug.WriteLine(string.Format("CName.LastName: {0} !",2));

				// !!! Tu nehodim EXCEPTION.
				/*
				if (MErrorLastName==true)
					throw(new Exception("SETTER Says: LastName is INVALID !"));					
				*/
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
				Debug.WriteLine(string.Format("CName.Age: {0} !",1));

				MAge=value;

				if (MAge>100)
				{
					MErrorAge=true;
					MError="Age is to BIG !";
				}
				else
				{
					MErrorAge=false;
					MError=null;
				}

				if (PropertyChanged!=null)
				{
					// !!! Ak dam do PropertyChangedEventArgs prazdny string tak sa updateuje kazda property.
					PropertyChanged(this,new PropertyChangedEventArgs("Age"));
				}

				Debug.WriteLine(string.Format("CName.Age: {0} !",2));

				if (MErrorAge==true)
					throw(new Exception("SETTER Says: Age is INVALID !"));					
			}
		}
//------------------------------------------------------------------------
		public string						Error
		{
			get
			{
				Debug.WriteLine("CName.Error CALLED !");

				return(MError);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public string						this[string PropertyName]
		{
			get
			{
				Debug.WriteLine(string.Format("CName.INDEXER CALLED for: {0} !",PropertyName));

				if (PropertyName=="FirstName")
				{
					if (MErrorFirstName==true)
						return("Invalid FirstName !");
					else
						return(null);
				}
				else if (PropertyName=="LastName")
				{
					if (MErrorLastName==true)
						return("Invalid LastName !");
					else
						return(null);
				}
				else if (PropertyName=="Age")
				{
					if (MErrorAge==true)
						return("Invalid Age !");
					else
						return(null);
				}
				else
					return(null);
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