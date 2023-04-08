using System;
using System.ComponentModel;
using System.Collections.ObjectModel;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace MySimpleDataApp
{
//-------------------------------------------------------------------------------------------------------
	// Trieda kedze je zdedena z CPersonCollection bude poskytovat notifikaciu pre GUI.
	// Ak CollectionView pouzijem ako DataContxt a ZAROVEN cez BINDING MAPUJEM PROPERTIES ELEMENTOV, tak pri PRECHODE cez CollectionView, alebo PRIDANI ci UBRANI RECORDU do VIEW (presnejsie kolekcie, ktora VIEW OBALUJE) sa AUTOMATICKY POSUNIE INDEX AKTUALNEHO ZAZNAMU a ZMENIA VSETKY BINDINGS, ukazujuc na NOVY RECORD. Ak zarovne RECORD IMPLEMENTUJE INotifyPropertyChanged tak ZMENY v PROPERTIES daneho RECORDS su AUTOMATICKY PREMIETNUTE do PROPERTIES ELEMENTU.
	public class CPersonCollection : ObservableCollection<CPerson>
	{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------