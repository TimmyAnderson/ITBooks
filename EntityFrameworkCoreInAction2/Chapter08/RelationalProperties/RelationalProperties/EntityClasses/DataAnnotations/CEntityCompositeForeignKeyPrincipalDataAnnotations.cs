using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS je PRINCIPAL ENTITY, pretoze NEOBSAHUJE FOREIGN KEY PROPERTY.
	public sealed class CEntityCompositeForeignKeyPrincipalDataAnnotations
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! COMPOSITE PRIMARY KEY.
		private int												MEntityPrincipalID1;
		private int												MEntityPrincipalID2;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityPrincipalValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY na DEPENDENT ENTITIES.
		private IList<CEntityCompositeForeignKeyDependentDataAnnotations>	MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityCompositeForeignKeyPrincipalDataAnnotations()
		{
			MEntityPrincipalID1=default;
			MEntityPrincipalID2=default;
			MEntityPrincipalValue=default;
			MEntitiesDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityCompositeForeignKeyPrincipalDataAnnotations(int EntityPrincipalID1, int EntityPrincipalID2, string EntityPrincipalValue)
		{
			MEntityPrincipalID1=EntityPrincipalID1;
			MEntityPrincipalID2=EntityPrincipalID2;
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntitiesDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityCompositeForeignKeyPrincipalDataAnnotations(int EntityPrincipalID1, int EntityPrincipalID2, string EntityPrincipalValue, IList<CEntityCompositeForeignKeyDependentDataAnnotations> EntitiesDependent)
		{
			MEntityPrincipalID1=EntityPrincipalID1;
			MEntityPrincipalID2=EntityPrincipalID2;
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntitiesDependent=EntitiesDependent;
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
		public IList<CEntityCompositeForeignKeyDependentDataAnnotations>	EntitiesDependent
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
		public static void PrintToConsole(CEntityCompositeForeignKeyPrincipalDataAnnotations[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityCompositeForeignKeyPrincipalDataAnnotations	Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY COMPOSITE FOREIGN KEY PRINCIPAL DATA ANNOTATIONS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY COMPOSITE FOREIGN KEY PRINCIPAL DATA ANNOTATIONS:");
			}

			SB.AppendLine($"\tENTITY PRINCIPAL ID 1 [{MEntityPrincipalID1}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL ID 2 [{MEntityPrincipalID2}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL VALUE [{MEntityPrincipalValue}] !");

			if (MEntitiesDependent!=null)
			{
				SB.AppendLine($"\tENTITIES DEPENDENT:");

				for(int EntityDependentIndex=0;EntityDependentIndex<MEntitiesDependent.Count;EntityDependentIndex++)
				{
					CEntityCompositeForeignKeyDependentDataAnnotations	EntityDependent=MEntitiesDependent[EntityDependentIndex];

					SB.AppendLine($"\t\tENTITY DEPENDENT [{(EntityDependentIndex+1)}]:");

					SB.AppendLine($"\t\t\tENTITY DEPENDENT ID [{EntityDependent.EntityDependentID}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT VALUE [{EntityDependent.EntityDependentValue}] !");
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