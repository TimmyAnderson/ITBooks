using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess2
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS je PRINCIPAL ENTITY, pretoze NEOBSAHUJE FOREIGN KEY PROPERTY.
	public sealed class CEntityOwnedOneToOnePrincipal
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityPrincipalValue;
//----------------------------------------------------------------------------------------------------------------------
		private CEntityOwnedOneToOneDependent					MEntityDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOwnedOneToOnePrincipal()
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=default;
			MEntityDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOwnedOneToOnePrincipal(string EntityPrincipalValue)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntityDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOwnedOneToOnePrincipal(int EntityPrincipalID, string EntityPrincipalValue)
		{
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntityDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOwnedOneToOnePrincipal(string EntityPrincipalValue, CEntityOwnedOneToOneDependent EntityDependent)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntityDependent=EntityDependent;
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
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityPrincipalValue
		{
			get
			{
				return(MEntityPrincipalValue);
			}
			set
			{
				MEntityPrincipalValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOwnedOneToOneDependent					EntityDependent
		{
			get
			{
				return(MEntityDependent);
			}
			set
			{
				MEntityDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityOwnedOneToOnePrincipal[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityOwnedOneToOnePrincipal					Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY OWNED ONE TO ONE PRINCIPAL [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY OWNED ONE TO ONE PRINCIPAL:");
			}

			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL VALUE [{MEntityPrincipalValue}] !");

			if (MEntityDependent!=null)
			{
				SB.AppendLine($"\tENTITY DEPENDENT:");

				SB.AppendLine($"\t\tENTITY DEPENDENT ID [{MEntityDependent.EntityDependentID}] !");
				SB.AppendLine($"\t\tENTITY DEPENDENT VALUE [{MEntityDependent.EntityDependentValue}] !");
			}
			else
			{
				SB.AppendLine($"\t--- ENTITY DEPENDENT is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------