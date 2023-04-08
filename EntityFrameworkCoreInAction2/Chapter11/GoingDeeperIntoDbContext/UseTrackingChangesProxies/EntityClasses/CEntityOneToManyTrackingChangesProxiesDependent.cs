using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace UseTrackingChangesProxies
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! ENTITY CLASS NESMIE BYT SEALED.
	public class CEntityOneToManyTrackingChangesProxiesDependent
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentIntValue;
		private string											MEntityDependentStringValue;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private CEntityOneToManyTrackingChangesProxiesPrincipal	MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyTrackingChangesProxiesDependent()
		{
			MEntityDependentID=default;
			MEntityDependentIntValue=default;
			MEntityDependentStringValue=default;
			MEntityPrincipalID=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyTrackingChangesProxiesDependent(int EntityDependentIntValue, string EntityDependentStringValue)
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
		// !!!!! PROPERTIES MUSIA byt VIRTUAL.
		public virtual int										EntityDependentID
		{
			get
			{
				return(MEntityDependentID);
			}
			set
			{
				MEntityDependentID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! PROPERTIES MUSIA byt VIRTUAL.
		public virtual int										EntityDependentIntValue
		{
			get
			{
				return(MEntityDependentIntValue);
			}
			set
			{
				MEntityDependentIntValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! PROPERTIES MUSIA byt VIRTUAL.
		public virtual string									EntityDependentStringValue
		{
			get
			{
				return(MEntityDependentStringValue);
			}
			set
			{
				MEntityDependentStringValue=value;
			}
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
		public virtual CEntityOneToManyTrackingChangesProxiesPrincipal	EntityPrincipal
		{
			get
			{
				return(MEntityPrincipal);
			}
			set
			{
				MEntityPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityOneToManyTrackingChangesProxiesDependent[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityOneToManyTrackingChangesProxiesDependent	Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY ONE TO MANY TRACKING CHANGES PROXIES DEPENDENT [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY ONE TO MANY TRACKING CHANGES PROXIES DEPENDENT:");
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