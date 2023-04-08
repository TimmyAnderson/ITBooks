using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace UseTrackingChangesProxies
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! ENTITY CLASS NESMIE BYT SEALED.
	public class CEntityOneToManyTrackingChangesProxiesPrincipal
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalIntValue;
		private string											MEntityPrincipalStringValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Pri TRACKING CHANGES PROXIES MUSIA byt NAVIGATION PROPERTIES typu COLLECTION OBSERVABLE, aby pri ich zmene doslo k notifikacii CLASS [ChangeTracker].
		private ObservableCollection<CEntityOneToManyTrackingChangesProxiesDependent>	MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyTrackingChangesProxiesPrincipal()
		{
			MEntityPrincipalID=default;
			MEntityPrincipalIntValue=default;
			MEntityPrincipalStringValue=default;
			MEntitiesDependent=new ObservableCollection<CEntityOneToManyTrackingChangesProxiesDependent>();
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyTrackingChangesProxiesPrincipal(int EntityPrincipalIntValue, string EntityPrincipalStringValue, ObservableCollection<CEntityOneToManyTrackingChangesProxiesDependent> EntitiesDependent)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalIntValue=EntityPrincipalIntValue;
			MEntityPrincipalStringValue=EntityPrincipalStringValue;
			MEntitiesDependent=EntitiesDependent;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! PROPERTIES MUSIA byt VIRTUAL.
		public virtual int										EntityPrincipalID
		{
			get
			{
				return(MEntityPrincipalID);
			}
			set
			{
				MEntityPrincipalID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! PROPERTIES MUSIA byt VIRTUAL.
		public virtual int										EntityPrincipalIntValue
		{
			get
			{
				return(MEntityPrincipalIntValue);
			}
			set
			{
				MEntityPrincipalIntValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! PROPERTIES MUSIA byt VIRTUAL.
		public virtual string									EntityPrincipalStringValue
		{
			get
			{
				return(MEntityPrincipalStringValue);
			}
			set
			{
				MEntityPrincipalStringValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! PROPERTIES MUSIA byt VIRTUAL.
		public virtual ObservableCollection<CEntityOneToManyTrackingChangesProxiesDependent>	EntitiesDependent
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
		public static void PrintToConsole(CEntityOneToManyTrackingChangesProxiesPrincipal[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityOneToManyTrackingChangesProxiesPrincipal	Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY ONE TO MANY TRACKING CHANGES PROXIES PRINCIPAL [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY ONE TO MANY TRACKING CHANGES PROXIES PRINCIPAL:");
			}

			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL INT VALUE [{MEntityPrincipalIntValue}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL STRING VALUE [{MEntityPrincipalStringValue}] !");

			if (MEntitiesDependent!=null)
			{
				SB.AppendLine($"\tENTITIES DEPENDENT:");

				for(int EntityDependentIndex=0;EntityDependentIndex<MEntitiesDependent.Count;EntityDependentIndex++)
				{
					CEntityOneToManyTrackingChangesProxiesDependent	EntityDependent=MEntitiesDependent[EntityDependentIndex];

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