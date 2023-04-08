using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace GoingDeeperIntoDbContext
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! ENTITY pouziva TRACKING CHANGES MODE [ChangedNotifications].
	// !!!!! CLASS implementuje INTERFACE [INotifyPropertyChanged], ktorym ENTITY OBJECT zasiela informaciu DB CONTEXT o CHANGES, ktore boli vykonane nad VALUES jednotlivych PROPERTIES.
	public sealed class CEntityOneToManyTrackingChangesChangedNotificationsDependent : INotifyPropertyChanged
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentIntValue;
		private string											MEntityDependentStringValue;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private CEntityOneToManyTrackingChangesChangedNotificationsPrincipal	MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
		public event PropertyChangedEventHandler				PropertyChanged;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyTrackingChangesChangedNotificationsDependent()
		{
			MEntityDependentID=default;
			MEntityDependentIntValue=default;
			MEntityDependentStringValue=default;
			MEntityPrincipalID=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyTrackingChangesChangedNotificationsDependent(int EntityDependentIntValue, string EntityDependentStringValue)
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
				MEntityDependentID=value;

				// !!!!! NON-COLLECTION PROPERTY musi o svojich zmenach vykonat NOTIFICATION, aby CLASS [ChangeTracker] mal informaciu o zmene PROPERTY.
				if (PropertyChanged!=null)
				{
					PropertyChanged(this,new PropertyChangedEventArgs(nameof(EntityDependentID)));
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
				MEntityDependentIntValue=value;

				// !!!!! NON-COLLECTION PROPERTY musi o svojich zmenach vykonat NOTIFICATION, aby CLASS [ChangeTracker] mal informaciu o zmene PROPERTY.
				if (PropertyChanged!=null)
				{
					PropertyChanged(this,new PropertyChangedEventArgs(nameof(EntityDependentIntValue)));
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
				MEntityDependentStringValue=value;

				// !!!!! NON-COLLECTION PROPERTY musi o svojich zmenach vykonat NOTIFICATION, aby CLASS [ChangeTracker] mal informaciu o zmene PROPERTY.
				if (PropertyChanged!=null)
				{
					PropertyChanged(this,new PropertyChangedEventArgs(nameof(EntityDependentStringValue)));
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
		public CEntityOneToManyTrackingChangesChangedNotificationsPrincipal	EntityPrincipal
		{
			get
			{
				return(MEntityPrincipal);
			}
			set
			{
				MEntityPrincipal=value;

				// !!!!! NON-COLLECTION PROPERTY musi o svojich zmenach vykonat NOTIFICATION, aby CLASS [ChangeTracker] mal informaciu o zmene PROPERTY.
				if (PropertyChanged!=null)
				{
					PropertyChanged(this,new PropertyChangedEventArgs(nameof(EntityPrincipal)));
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityOneToManyTrackingChangesChangedNotificationsDependent[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityOneToManyTrackingChangesChangedNotificationsDependent	Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY ONE TO MANY TRACKING CHANGES CHANGED NOTIFICATIONS DEPENDENT [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY ONE TO MANY TRACKING CHANGES CHANGED NOTIFICATIONS DEPENDENT:");
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