using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace GoingDeeperIntoDbContext
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! ENTITY pouziva TRACKING CHANGES MODE [ChangingAndChangedNotificationsWithOriginalValues].
	// !!!!! CLASS implementuje INTERFACE [INotifyPropertyChanging], ktorym ENTITY OBJECT zasiela DB CONTEXT informaciu o planovanej zmene PROPERTY VALUES. DB CONTEXT si tak moze ulozit ORIGINAL VALUES PROPERTIES, ktore su potrebne napriklad pre vykonanie detekcie CONCURRENCY CONFLICTS.
	// !!!!! CLASS implementuje INTERFACE [INotifyPropertyChanged], ktorym ENTITY OBJECT zasiela informaciu DB CONTEXT o CHANGES, ktore boli vykonane nad VALUES jednotlivych PROPERTIES.
	public sealed class CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent : INotifyPropertyChanging, INotifyPropertyChanged
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentIntValue;
		private string											MEntityDependentStringValue;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal	MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
		public event PropertyChangingEventHandler				PropertyChanging;
		public event PropertyChangedEventHandler				PropertyChanged;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent()
		{
			MEntityDependentID=default;
			MEntityDependentIntValue=default;
			MEntityDependentStringValue=default;
			MEntityPrincipalID=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent(int EntityDependentIntValue, string EntityDependentStringValue)
		{
			MEntityDependentID=default;
			MEntityDependentIntValue=EntityDependentIntValue;
			MEntityDependentStringValue=EntityDependentStringValue;
			MEntityPrincipalID=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityDependentID
		{
			get
			{
				return(MEntityDependentID);
			}
			set
			{
				const string									PROPERTY_NAME=nameof(EntityDependentID);

				// !!!!! NON-COLLECTION PROPERTY musi o tom, ze dojde k vykonaniu zmeny VALUE danej PROPERTY zaslat NOTIFICATION do CLASS [ChangeTracker], aby si ten mohol ulozit ORIGINAL VALUES niektorych klucovych PROPERTIES, ako tie, ktore sa pouzivaju napriklad na riesenie CONCURRENCY CONFLICTS.
				if (PropertyChanging!=null)
				{
					PropertyChangingEventArgs					Parameter=new PropertyChangingEventArgs(PROPERTY_NAME);

					PropertyChanging.Invoke(this,Parameter);
				}

				MEntityDependentID=value;

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
		public int												EntityDependentIntValue
		{
			get
			{
				return(MEntityDependentIntValue);
			}
			set
			{
				const string									PROPERTY_NAME=nameof(EntityDependentIntValue);

				// !!!!! NON-COLLECTION PROPERTY musi o tom, ze dojde k vykonaniu zmeny VALUE danej PROPERTY zaslat NOTIFICATION do CLASS [ChangeTracker], aby si ten mohol ulozit ORIGINAL VALUES niektorych klucovych PROPERTIES, ako tie, ktore sa pouzivaju napriklad na riesenie CONCURRENCY CONFLICTS.
				if (PropertyChanging!=null)
				{
					PropertyChangingEventArgs					Parameter=new PropertyChangingEventArgs(PROPERTY_NAME);

					PropertyChanging.Invoke(this,Parameter);
				}

				MEntityDependentIntValue=value;

				// !!!!! NON-COLLECTION PROPERTY musi o svojich zmenach vykonat NOTIFICATION, aby CLASS [ChangeTracker] mal informaciu o zmene PROPERTY.
				if (PropertyChanged!=null)
				{
					PropertyChangedEventArgs					Parameter=new PropertyChangedEventArgs(PROPERTY_NAME);

					PropertyChanged.Invoke(this,Parameter);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityDependentStringValue
		{
			get
			{
				return(MEntityDependentStringValue);
			}
			set
			{
				const string									PROPERTY_NAME=nameof(EntityDependentStringValue);

				// !!!!! NON-COLLECTION PROPERTY musi o tom, ze dojde k vykonaniu zmeny VALUE danej PROPERTY zaslat NOTIFICATION do CLASS [ChangeTracker], aby si ten mohol ulozit ORIGINAL VALUES niektorych klucovych PROPERTIES, ako tie, ktore sa pouzivaju napriklad na riesenie CONCURRENCY CONFLICTS.
				if (PropertyChanging!=null)
				{
					PropertyChangingEventArgs					Parameter=new PropertyChangingEventArgs(PROPERTY_NAME);

					PropertyChanging.Invoke(this,Parameter);
				}

				MEntityDependentStringValue=value;

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
		public CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal	EntityPrincipal
		{
			get
			{
				return(MEntityPrincipal);
			}
			set
			{
				const string									PROPERTY_NAME=nameof(EntityPrincipal);

				// !!!!! NON-COLLECTION PROPERTY musi o tom, ze dojde k vykonaniu zmeny VALUE danej PROPERTY zaslat NOTIFICATION do CLASS [ChangeTracker], aby si ten mohol ulozit ORIGINAL VALUES niektorych klucovych PROPERTIES, ako tie, ktore sa pouzivaju napriklad na riesenie CONCURRENCY CONFLICTS.
				if (PropertyChanging!=null)
				{
					PropertyChangingEventArgs					Parameter=new PropertyChangingEventArgs(PROPERTY_NAME);

					PropertyChanging.Invoke(this,Parameter);
				}

				MEntityPrincipal=value;

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
		public static void PrintToConsole(CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent	Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY ONE TO MANY TRACKING CHANGES CHANGING AND CHANGED NOTIFICATIONS WITH ORIGINAL VALUES DEPENDENT [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY ONE TO MANY TRACKING CHANGES CHANGING AND CHANGED NOTIFICATIONS WITH ORIGINAL VALUES DEPENDENT:");
			}

			SB.AppendLine($"\tENTITY DEPENDENT ID [{MEntityDependentID}] !");
			SB.AppendLine($"\tENTITY DEPENDENT INT VALUE [{MEntityDependentIntValue}] !");
			SB.AppendLine($"\tENTITY DEPENDENT STRING VALUE [{MEntityDependentStringValue}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");

			if (MEntityPrincipal!=null)
			{
				SB.AppendLine($"\tENTITY PRINCIPAL:");

				SB.AppendLine($"\t\tENTITY PRINCIPAL ID [{MEntityPrincipal.EntityPrincipalID}] !");
				SB.AppendLine($"\t\tENTITY PRINCIPAL INT VALUE [{MEntityPrincipal.EntityPrincipalIntValue}] !");
				SB.AppendLine($"\t\tENTITY PRINCIPAL STRING VALUE [{MEntityPrincipal.EntityPrincipalStringValue}] !");
			}
			else
			{
				SB.AppendLine($"\t--- ENTITY PRINCIPAL is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------