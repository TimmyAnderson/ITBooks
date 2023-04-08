using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS je DEPENDENT ENTITY, pretoze OBSAHUJE FOREIGN KEY PROPERTY.
	public sealed class CEntityCompositeForeignKeyDependentDataAnnotations
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityDependentValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! COMPOSITE FOREIGN KEY v RELATIONSHIP 1:N, lebo FOREIGN KEY je NON-NULLABLE.
		private int												MEntityPrincipalID1;
		private int												MEntityPrincipalID2;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY na PRINCIPAL CLASS.
		private CEntityCompositeForeignKeyPrincipalDataAnnotations	MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityCompositeForeignKeyDependentDataAnnotations()
		{
			MEntityDependentID=default;
			MEntityDependentValue=default;
			MEntityPrincipalID1=default;
			MEntityPrincipalID2=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityCompositeForeignKeyDependentDataAnnotations(string EntityDependentValue)
		{
			MEntityDependentID=default;
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID1=default;
			MEntityPrincipalID2=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityCompositeForeignKeyDependentDataAnnotations(string EntityDependentValue, CEntityCompositeForeignKeyPrincipalDataAnnotations EntityPrincipal)
		{
			MEntityDependentID=default;
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID1=default;
			MEntityPrincipalID2=default;
			MEntityPrincipal=EntityPrincipal;
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
		public int												EntityPrincipalID1
		{
			get
			{
				return(MEntityPrincipalID1);
			}
			set
			{
				MEntityPrincipalID1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityPrincipalID2
		{
			get
			{
				return(MEntityPrincipalID2);
			}
			set
			{
				MEntityPrincipalID2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! APLIKUJE sa FOREIGN KEY. FOREIGN KEY je COMPOSITE KEY kde su KEY oddelene CHAR ','.
		[ForeignKey(nameof(EntityPrincipalID1)+","+nameof(EntityPrincipalID2))]
		public CEntityCompositeForeignKeyPrincipalDataAnnotations	EntityPrincipal
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
		public static void PrintToConsole(CEntityCompositeForeignKeyDependentDataAnnotations[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityCompositeForeignKeyDependentDataAnnotations	Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY COMPOSITE FOREIGN KEY DEPENDENT DATA ANNOTATIONS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY COMPOSITE FOREIGN KEY DEPENDENT DATA ANNOTATIONS:");
			}

			SB.AppendLine($"\tENTITY DEPENDENT ID [{MEntityDependentID}] !");
			SB.AppendLine($"\tENTITY DEPENDENT VALUE [{MEntityDependentValue}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL ID 1 [{MEntityPrincipalID1}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL ID 2 [{MEntityPrincipalID2}] !");

			if (MEntityPrincipal!=null)
			{
				SB.AppendLine($"\tENTITY PRINCIPAL:");

				SB.AppendLine($"\t\tENTITY PRINCIPAL ID 1 [{MEntityPrincipal.EntityPrincipalID1}] !");
				SB.AppendLine($"\t\tENTITY PRINCIPAL ID 2 [{MEntityPrincipal.EntityPrincipalID2}] !");
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