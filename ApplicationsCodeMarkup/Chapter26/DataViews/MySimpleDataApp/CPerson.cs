using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace MySimpleDataApp
{
//-------------------------------------------------------------------------------------------------------
	// Trieda bude poskytovat notifikaciu pre GUI.
	// Ak CollectionView pouzijem ako DataContxt a ZAROVEN cez BINDING MAPUJEM PROPERTIES ELEMENTOV, tak pri PRECHODE cez CollectionView, alebo PRIDANI ci UBRANI RECORDU do VIEW (presnejsie kolekcie, ktora VIEW OBALUJE) sa AUTOMATICKY POSUNIE INDEX AKTUALNEHO ZAZNAMU a ZMENIA VSETKY BINDINGS, ukazujuc na NOVY RECORD. Ak zarovne RECORD IMPLEMENTUJE INotifyPropertyChanged tak ZMENY v PROPERTIES daneho RECORDS su AUTOMATICKY PREMIETNUTE do PROPERTIES ELEMENTU.
	public class CPerson : INotifyPropertyChanged
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFirstName;
		private string											MLastName;
		private int												MAge;
//-------------------------------------------------------------------------------------------------------
		public event PropertyChangedEventHandler				PropertyChanged;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CPerson()
		{
			MFirstName=null;
			MLastName=null;
			MAge=0;
		}
//-------------------------------------------------------------------------------------------------------
		public CPerson(string FirstName, string LastName, int Age)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											FirstName
		{
			get
			{
				return(MFirstName);
			}
			set
			{
				MFirstName=value;
				FirePropertyChanged("FirstName");
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											LastName
		{
			get
			{
				return(MLastName);
			}
			set
			{
				MLastName=value;
				FirePropertyChanged("LastName");
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int												Age
		{
			get
			{
				return(MAge);
			}
			set
			{
				MAge=value;
				FirePropertyChanged("Age");
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void FirePropertyChanged(string PropertyName)
		{
			if (PropertyChanged!=null)
				PropertyChanged(this,new PropertyChangedEventArgs("PropertyName"));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------