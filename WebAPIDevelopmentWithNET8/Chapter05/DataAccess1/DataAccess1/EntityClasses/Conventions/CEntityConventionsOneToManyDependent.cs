using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess1
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS je DEPENDENT ENTITY, pretoze OBSAHUJE FOREIGN KEY PROPERTY.
	public sealed class CEntityConventionsOneToManyDependent
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityDependentValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! FOREIGN KEY v RELATIONSHIP 1:N, lebo FOREIGN KEY je NON-NULLABLE.
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY na PRINCIPAL CLASS.
		private CEntityConventionsOneToManyPrincipal			MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityConventionsOneToManyDependent()
		{
			MEntityDependentID=default;
			MEntityDependentValue=default;
			MEntityPrincipalID=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityConventionsOneToManyDependent(string EntityDependentValue)
		{
			MEntityDependentID=default;
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityConventionsOneToManyDependent(string EntityDependentValue, CEntityConventionsOneToManyPrincipal EntityPrincipal)
		{
			MEntityDependentID=default;
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID=default;
			MEntityPrincipal=EntityPrincipal;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												CEntityConventionsOneToManyDependentId
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
		public string											EntityDependentValue
		{
			get
			{
				return(MEntityDependentValue);
			}
			set
			{
				MEntityDependentValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! FOREIGN KEY PROPERTY NAME MUSI SPLNAT niektoru z CONVENTIONS, aby ho ENTITY FRAMEWORK CORE povazoval za FOREIGN KEY PROPERTY.
		// !!! FOREIGN KEY PROPERTY NAME je zhodny s NAME PRIMARY KEY v PRINCIPAL ENTITY.
		public int												CEntityConventionsOneToManyPrincipalId
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
		public CEntityConventionsOneToManyPrincipal				EntityPrincipal
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
		public static void PrintToConsole(CEntityConventionsOneToManyDependent[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityConventionsOneToManyDependent			Entity=Entities[Index];
				string											EntityText=Entity.Print(Index+1);
							
				if (Index>0)
				{
					Console.WriteLine(new string('-',80));
				}

				Console.Write(EntityText);
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
				SB.AppendLine($"ENTITY CONVENTIONS ONE TO MANY DEPENDENT [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY CONVENTIONS ONE TO MANY DEPENDENT:");
			}

			SB.AppendLine($"\tENTITY DEPENDENT ID [{MEntityDependentID}] !");
			SB.AppendLine($"\tENTITY DEPENDENT VALUE [{MEntityDependentValue}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");

			if (MEntityPrincipal!=null)
			{
				SB.AppendLine($"\tENTITY PRINCIPAL:");

				SB.AppendLine($"\t\tENTITY PRINCIPAL ID [{MEntityPrincipal.CEntityConventionsOneToManyPrincipalId}] !");
				SB.AppendLine($"\t\tENTITY PRINCIPAL VALUE [{MEntityPrincipal.EntityPrincipalValue}] !");
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