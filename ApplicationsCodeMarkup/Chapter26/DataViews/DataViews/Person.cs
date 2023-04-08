using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Xml.Serialization;
using System.Collections.ObjectModel;
//-------------------------------------------------------------------------------------------------------
namespace DataViews
{
//-------------------------------------------------------------------------------------------------------
	// INotifyPropertyChanged umoznuje notifikovat WPF o zmenach hoednot properties.
	public class Person : INotifyPropertyChanged
	{
//-------------------------------------------------------------------------------------------------------
        private string											MStrFirstName="<first name>";
        private string											MStrMiddleName="" ;
        private string											MStrLastName="<last name>";
        private DateTime?										MDtBirthDate=new DateTime(1800, 1, 1);
        private DateTime?										MDtDeathDate=new DateTime(1900, 12, 31);
//-------------------------------------------------------------------------------------------------------
        public event PropertyChangedEventHandler				PropertyChanged;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public string											FirstName
        {
            get
			{
				return(MStrFirstName);
			}
            set 
            { 
                MStrFirstName=value; 
                OnPropertyChanged("FirstName");
            }
        }
//-------------------------------------------------------------------------------------------------------
        public string											MiddleName
        {
            get
			{
				return(MStrMiddleName);
			}
            set 
            { 
                MStrMiddleName=value; 
                OnPropertyChanged("MiddleName");
            }
        }
//-------------------------------------------------------------------------------------------------------
        public string											LastName
        {
            get
			{
				return(MStrLastName);
			}
            set 
            { 
                MStrLastName=value; 
                OnPropertyChanged("LastName");
            }
        }
//-------------------------------------------------------------------------------------------------------
        [XmlElement(DataType="date")]
        public DateTime?										BirthDate
        {
            get
			{
				return(MDtBirthDate);
			}
            set 
            { 
                MDtBirthDate=value; 
                OnPropertyChanged("BirthDate");
            }
        }
//-------------------------------------------------------------------------------------------------------
        [XmlElement(DataType="date")]
        public DateTime?										DeathDate
        {
            get
			{
				return(MDtDeathDate);
			}
            set 
            { 
                MDtDeathDate=value; 
                OnPropertyChanged("DeathDate");
            }
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        protected virtual void OnPropertyChanged(string StrPropertyName)
        {
            if (PropertyChanged!=null)
                PropertyChanged(this, new PropertyChangedEventArgs(StrPropertyName));
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------