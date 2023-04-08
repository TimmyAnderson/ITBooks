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
	// !!! ENTITY pouziva TRACKING CHANGES MODE [ChangingAndChangedNotifications].
	// !!!!! CLASS implementuje INTERFACE [INotifyPropertyChanging], ktorym ENTITY OBJECT zasiela DB CONTEXT informaciu o planovanej zmene PROPERTY VALUES. DB CONTEXT si tak moze ulozit ORIGINAL VALUES PROPERTIES, ktore su potrebne napriklad pre vykonanie detekcie CONCURRENCY CONFLICTS.
	// !!!!! CLASS implementuje INTERFACE [INotifyPropertyChanged], ktorym ENTITY OBJECT zasiela informaciu DB CONTEXT o CHANGES, ktore boli vykonane nad VALUES jednotlivych PROPERTIES.
	public sealed class CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal : INotifyPropertyChanging, INotifyPropertyChanged
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalIntValue;
		private string											MEntityPrincipalStringValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Pri TRACKING CHANGES MODE [ChangingAndChangedNotifications] MUSIA byt NAVIGATION PROPERTIES typu COLLECTION OBSERVABLE, aby pri ich zmene doslo k notifikacii CLASS [ChangeTracker].
		private ObservableCollection<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent>	MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
		public event PropertyChangingEventHandler				PropertyChanging;
		public event PropertyChangedEventHandler				PropertyChanged;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal()
		{
			MEntityPrincipalID=default;
			MEntityPrincipalIntValue=default;
			MEntityPrincipalStringValue=default;
			MEntitiesDependent=new ObservableCollection<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent>();
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal(int EntityPrincipalIntValue, string EntityPrincipalStringValue, ObservableCollection<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent> EntitiesDependent)
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
				const string									PROPERTY_NAME=nameof(EntityPrincipalID);

				// !!!!! NON-COLLECTION PROPERTY musi o tom, ze dojde k vykonaniu zmeny VALUE danej PROPERTY zaslat NOTIFICATION do CLASS [ChangeTracker], aby si ten mohol ulozit ORIGINAL VALUES niektorych klucovych PROPERTIES, ako tie, ktore sa pouzivaju napriklad na riesenie CONCURRENCY CONFLICTS.
				if (PropertyChanging!=null)
				{
					PropertyChangingEventArgs					Parameter=new PropertyChangingEventArgs(PROPERTY_NAME);

					PropertyChanging.Invoke(this,Parameter);
				}

				MEntityPrincipalID=value;

				// !!!!! NON-COLLECTION PROPERTY musi o svojich zmenach vykonat NOTIFICATION, aby CLASS [ChangeTracker] mal informaciu o zmene PROPERTY.
				if (PropertyChanged!=null)
				{
					PropertyChangedEventArgs					Parameter=new PropertyChangedEventArgs(PROPERTY_NAME);

					PropertyChanged.Invoke(this,Parameter);
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
				const string									PROPERTY_NAME=nameof(EntityPrincipalIntValue);

				// !!!!! NON-COLLECTION PROPERTY musi o tom, ze dojde k vykonaniu zmeny VALUE danej PROPERTY zaslat NOTIFICATION do CLASS [ChangeTracker], aby si ten mohol ulozit ORIGINAL VALUES niektorych klucovych PROPERTIES, ako tie, ktore sa pouzivaju napriklad na riesenie CONCURRENCY CONFLICTS.
				if (PropertyChanging!=null)
				{
					PropertyChangingEventArgs					Parameter=new PropertyChangingEventArgs(PROPERTY_NAME);

					PropertyChanging.Invoke(this,Parameter);
				}

				MEntityPrincipalIntValue=value;

				// !!!!! NON-COLLECTION PROPERTY musi o svojich zmenach vykonat NOTIFICATION, aby CLASS [ChangeTracker] mal informaciu o zmene PROPERTY.
				if (PropertyChanged!=null)
				{
					PropertyChangedEventArgs					Parameter=new PropertyChangedEventArgs(PROPERTY_NAME);

					PropertyChanged.Invoke(this,Parameter);
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
				const string									PROPERTY_NAME=nameof(EntityPrincipalStringValue);

				// !!!!! NON-COLLECTION PROPERTY musi o tom, ze dojde k vykonaniu zmeny VALUE danej PROPERTY zaslat NOTIFICATION do CLASS [ChangeTracker], aby si ten mohol ulozit ORIGINAL VALUES niektorych klucovych PROPERTIES, ako tie, ktore sa pouzivaju napriklad na riesenie CONCURRENCY CONFLICTS.
				if (PropertyChanging!=null)
				{
					PropertyChangingEventArgs					Parameter=new PropertyChangingEventArgs(PROPERTY_NAME);

					PropertyChanging.Invoke(this,Parameter);
				}

				MEntityPrincipalStringValue=value;

				// !!!!! NON-COLLECTION PROPERTY musi o svojich zmenach vykonat NOTIFICATION, aby CLASS [ChangeTracker] mal informaciu o zmene PROPERTY.
				if (PropertyChanged!=null)
				{
					PropertyChangedEventArgs					Parameter=new PropertyChangedEventArgs(PROPERTY_NAME);

					PropertyChanged.Invoke(this,Parameter);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Pri TRACKING CHANGES MODE [ChangingAndChangedNotifications] MUSIA byt NAVIGATION PROPERTIES typu COLLECTION OBSERVABLE, aby pri ich zmene doslo k notifikacii CLASS [ChangeTracker].
		public ObservableCollection<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent>	EntitiesDependent
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
		public static void PrintToConsole(CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal	Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY ONE TO MANY TRACKING CHANGING AND CHANGES CHANGED NOTIFICATIONS PRINCIPAL [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY ONE TO MANY TRACKING CHANGING AND CHANGES CHANGED NOTIFICATIONS PRINCIPAL:");
			}

			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL INT VALUE [{MEntityPrincipalIntValue}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL STRING VALUE [{MEntityPrincipalStringValue}] !");

			if (MEntitiesDependent!=null)
			{
				SB.AppendLine($"\tENTITIES DEPENDENT:");

				for(int EntityDependentIndex=0;EntityDependentIndex<MEntitiesDependent.Count;EntityDependentIndex++)
				{
					CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent	EntityDependent=MEntitiesDependent[EntityDependentIndex];

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