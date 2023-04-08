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
	// !!!!! DEPENDENT ENTITY obsahuje VIACERO RELATIONSHIP na TU ISTU PRINCIPAL ENTITY.
	public sealed class CEntityInversePropertyDependentDataAnnotations
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityDependentValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! FOREIGN KEY v RELATIONSHIP 0/1:N, lebo FOREIGN KEY je NON-NULLABLE.
		private int?											MEntityPrincipalID1;
		// !!! FOREIGN KEY v RELATIONSHIP 0/1:N, lebo FOREIGN KEY je NON-NULLABLE.
		private int?											MEntityPrincipalID2;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY na PRINCIPAL CLASS.
		private CEntityInversePropertyPrincipalDataAnnotations	MEntityPrincipal1;
		// !!! NAVIGATION PROPERTY na PRINCIPAL CLASS.
		private CEntityInversePropertyPrincipalDataAnnotations	MEntityPrincipal2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityInversePropertyDependentDataAnnotations()
		{
			MEntityDependentID=default;
			MEntityDependentValue=default;
			MEntityPrincipalID1=default;
			MEntityPrincipalID2=default;
			MEntityPrincipal1=default;
			MEntityPrincipal2=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityInversePropertyDependentDataAnnotations(string EntityDependentValue)
		{
			MEntityDependentID=default;
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID1=default;
			MEntityPrincipalID2=default;
			MEntityPrincipal1=default;
			MEntityPrincipal2=default;
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
		// !!! FOREIGN KEY na NAME, ktory NEZODPOVEDA CONVENTIONS.
		// !!! FOREIGN KEY MUSI byt NULLABLE, lebo v TEST DATA DEPENDENT ENTITY referuje na PRINCIPAL ENTITY naraz iba z jednej FOREIGN KEY PROPERTY.
		// !!! FOREIGN KEY by NEMUSEL byt NULLABLE, ak by VZDY DEPENDENT ENTITY mala naplnene OBA FOREIGN KEYS na PRINCIPAL ENTITIES.
		public int?												EntityPrincipalID1
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
		// !!! FOREIGN KEY na NAME, ktory NEZODPOVEDA CONVENTIONS.
		// !!! FOREIGN KEY MUSI byt NULLABLE, lebo v TEST DATA DEPENDENT ENTITY referuje na PRINCIPAL ENTITY naraz iba z jednej FOREIGN KEY PROPERTY.
		// !!! FOREIGN KEY by NEMUSEL byt NULLABLE, ak by VZDY DEPENDENT ENTITY mala naplnene OBA FOREIGN KEYS na PRINCIPAL ENTITIES.
		public int?												EntityPrincipalID2
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
		// !!! APLIKUJE sa FOREIGN KEY.
		[ForeignKey(nameof(EntityPrincipalID1))]
		public CEntityInversePropertyPrincipalDataAnnotations	EntityPrincipal1
		{
			get
			{
				return(MEntityPrincipal1);
			}
			set
			{
				MEntityPrincipal1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! APLIKUJE sa FOREIGN KEY.
		[ForeignKey(nameof(EntityPrincipalID2))]
		public CEntityInversePropertyPrincipalDataAnnotations	EntityPrincipal2
		{
			get
			{
				return(MEntityPrincipal2);
			}
			set
			{
				MEntityPrincipal2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityInversePropertyDependentDataAnnotations[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityInversePropertyDependentDataAnnotations	Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY INVERSE PROPERTY DEPENDENT DATA ANNOTATIONS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY INVERSE PROPERTY DEPENDENT DATA ANNOTATIONS:");
			}

			SB.AppendLine($"\tENTITY DEPENDENT ID [{MEntityDependentID}] !");
			SB.AppendLine($"\tENTITY DEPENDENT VALUE [{MEntityDependentValue}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID1}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID2}] !");

			if (MEntityPrincipal1!=null)
			{
				SB.AppendLine($"\tENTITY PRINCIPAL 1:");

				SB.AppendLine($"\t\tENTITY PRINCIPAL ID [{MEntityPrincipal1.EntityPrincipalID}] !");
				SB.AppendLine($"\t\tENTITY PRINCIPAL VALUE [{MEntityPrincipal1.EntityPrincipalValue}] !");
			}
			else
			{
				SB.AppendLine($"\t--- ENTITY PRINCIPAL 1 is NULL ! ---");
			}

			if (MEntityPrincipal2!=null)
			{
				SB.AppendLine($"\tENTITY PRINCIPAL 2:");

				SB.AppendLine($"\t\tENTITY PRINCIPAL ID [{MEntityPrincipal2.EntityPrincipalID}] !");
				SB.AppendLine($"\t\tENTITY PRINCIPAL VALUE [{MEntityPrincipal2.EntityPrincipalValue}] !");
			}
			else
			{
				SB.AppendLine($"\t--- ENTITY PRINCIPAL 2 is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------