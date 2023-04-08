using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace GoingDeeperIntoDbContext
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! ENTITY pouziva TRACKING CHANGES MODE [ChangedNotifications].
	// !!!!! CLASS implementuje INTERFACE [INotifyPropertyChanged], ktorym ENTITY OBJECT zasiela informaciu DB CONTEXT o CHANGES, ktore boli vykonane nad VALUES jednotlivych PROPERTIES.
	public sealed class CEntityOneToManyTrackingChangesChangedNotificationsPrincipal : INotifyPropertyChanged
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalIntValue;
		private string											MEntityPrincipalStringValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Pri TRACKING CHANGES MODE [ChangedNotifications] MUSIA byt NAVIGATION PROPERTIES typu COLLECTION OBSERVABLE, aby pri ich zmene doslo k notifikacii CLASS [ChangeTracker].
		private ObservableCollection<CEntityOneToManyTrackingChangesChangedNotificationsDependent>	MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
		public event PropertyChangedEventHandler				PropertyChanged;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyTrackingChangesChangedNotificationsPrincipal()
		{
			MEntityPrincipalID=default;
			MEntityPrincipalIntValue=default;
			MEntityPrincipalStringValue=default;
			MEntitiesDependent=new ObservableCollection<CEntityOneToManyTrackingChangesChangedNotificationsDependent>();
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyTrackingChangesChangedNotificationsPrincipal(int EntityPrincipalIntValue, string EntityPrincipalStringValue, ObservableCollection<CEntityOneToManyTrackingChangesChangedNotificationsDependent> EntitiesDependent)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalIntValue=EntityPrincipalIntValue;
			MEntityPrincipalStringValue=EntityPrincipalStringValue;
			MEntitiesDependent=EntitiesDependent;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityPrincipalID
		{
			get
			{
				return(MEntityPrincipalID);
			}
			set
			{
				MEntityPrincipalID=value;

				// !!!!! NON-COLLECTION PROPERTY musi o svojich zmenach vykonat NOTIFICATION, aby CLASS [ChangeTracker] mal informaciu o zmene PROPERTY.
				if (PropertyChanged!=null)
				{
					PropertyChanged(this,new PropertyChangedEventArgs(nameof(EntityPrincipalID)));
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityPrincipalIntValue
		{
			get
			{
				return(MEntityPrincipalIntValue);
			}
			set
			{
				MEntityPrincipalIntValue=value;

				// !!!!! NON-COLLECTION PROPERTY musi o svojich zmenach vykonat NOTIFICATION, aby CLASS [ChangeTracker] mal informaciu o zmene PROPERTY.
				if (PropertyChanged!=null)
				{
					PropertyChanged(this,new PropertyChangedEventArgs(nameof(EntityPrincipalIntValue)));
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityPrincipalStringValue
		{
			get
			{
				return(MEntityPrincipalStringValue);
			}
			set
			{
				MEntityPrincipalStringValue=value;

				// !!!!! NON-COLLECTION PROPERTY musi o svojich zmenach vykonat NOTIFICATION, aby CLASS [ChangeTracker] mal informaciu o zmene PROPERTY.
				if (PropertyChanged!=null)
				{
					PropertyChanged(this,new PropertyChangedEventArgs(nameof(EntityPrincipalStringValue)));
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Pri TRACKING CHANGES MODE [ChangedNotifications] MUSIA byt NAVIGATION PROPERTIES typu COLLECTION OBSERVABLE, aby pri ich zmene doslo k notifikacii CLASS [ChangeTracker].
		public ObservableCollection<CEntityOneToManyTrackingChangesChangedNotificationsDependent>	EntitiesDependent
		{
			get
			{
				return(MEntitiesDependent);
			}
			set
			{
				MEntitiesDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityOneToManyTrackingChangesChangedNotificationsPrincipal[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityOneToManyTrackingChangesChangedNotificationsPrincipal	Entity=Entities[Index];
				string											EntityText=Entity.Print(Index+1);
							
				if (Index>0)
				{
					CConsoleHelpers.WriteLineSeparator();
				}

				CConsoleHelpers.Write(EntityText,ConsoleColor.Green);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string Print(int? Index)
		{
			StringBuilder										SB=new StringBuilder();

			if (Index!=null)
			{
				SB.AppendLine($"ENTITY ONE TO MANY TRACKING CHANGES CHANGED NOTIFICATIONS PRINCIPAL [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY ONE TO MANY TRACKING CHANGES CHANGED NOTIFICATIONS PRINCIPAL:");
			}

			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL INT VALUE [{MEntityPrincipalIntValue}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL STRING VALUE [{MEntityPrincipalStringValue}] !");

			if (MEntitiesDependent!=null)
			{
				SB.AppendLine($"\tENTITIES DEPENDENT:");

				for(int EntityDependentIndex=0;EntityDependentIndex<MEntitiesDependent.Count;EntityDependentIndex++)
				{
					CEntityOneToManyTrackingChangesChangedNotificationsDependent	EntityDependent=MEntitiesDependent[EntityDependentIndex];

					SB.AppendLine($"\t\tENTITY DEPENDENT [{(EntityDependentIndex+1)}]:");

					SB.AppendLine($"\t\t\tENTITY DEPENDENT ID [{EntityDependent.EntityDependentID}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT INT VALUE [{EntityDependent.EntityDependentIntValue}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT STRING VALUE [{EntityDependent.EntityDependentStringValue}] !");
				}
			}
			else
			{
				SB.AppendLine($"\t--- ENTITIES DEPENDENT is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------