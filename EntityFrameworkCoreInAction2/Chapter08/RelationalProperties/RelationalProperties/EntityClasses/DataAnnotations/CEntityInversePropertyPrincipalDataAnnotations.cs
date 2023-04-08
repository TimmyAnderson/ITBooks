using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS je PRINCIPAL ENTITY, pretoze NEOBSAHUJE FOREIGN KEY PROPERTY.
	// !!!!! PRINCIPAL ENTITY obsahuje VIACERO RELATIONSHIP na TU ISTU DEPENDENT ENTITY.
	public sealed class CEntityInversePropertyPrincipalDataAnnotations
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityPrincipalValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY na DEPENDENT ENTITIES.
		private IList<CEntityInversePropertyDependentDataAnnotations>	MEntitiesDependent1;
		// !!! NAVIGATION PROPERTY na DEPENDENT ENTITIES.
		private IList<CEntityInversePropertyDependentDataAnnotations>	MEntitiesDependent2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityInversePropertyPrincipalDataAnnotations()
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=default;
			MEntitiesDependent1=default;
			MEntitiesDependent2=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityInversePropertyPrincipalDataAnnotations(string EntityPrincipalValue)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntitiesDependent1=default;
			MEntitiesDependent2=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityInversePropertyPrincipalDataAnnotations(string EntityPrincipalValue, IList<CEntityInversePropertyDependentDataAnnotations> EntitiesDependent1, IList<CEntityInversePropertyDependentDataAnnotations> EntitiesDependent2)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntitiesDependent1=EntitiesDependent1;
			MEntitiesDependent2=EntitiesDependent2;
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
		// !!!!! Kedze PRINCIPAL ENTITY ma 2 RELATIONSHIPS do TEJ ISTE DEPENDENT ENTIITY, ATTRIBUTE umoznuje urcit ku ktorej RELATIONSHIP dana NAVIGATION PROPERTY patri.
		[InverseProperty(nameof(CEntityInversePropertyDependentDataAnnotations.EntityPrincipal1))]
		public IList<CEntityInversePropertyDependentDataAnnotations>	EntitiesDependent1
		{
			get
			{
				return(MEntitiesDependent1);
			}
			set
			{
				MEntitiesDependent1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Kedze PRINCIPAL ENTITY ma 2 RELATIONSHIPS do TEJ ISTE DEPENDENT ENTIITY, ATTRIBUTE umoznuje urcit ku ktorej RELATIONSHIP dana NAVIGATION PROPERTY patri.
		[InverseProperty(nameof(CEntityInversePropertyDependentDataAnnotations.EntityPrincipal2))]
		public IList<CEntityInversePropertyDependentDataAnnotations>	EntitiesDependent2
		{
			get
			{
				return(MEntitiesDependent2);
			}
			set
			{
				MEntitiesDependent2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityInversePropertyPrincipalDataAnnotations[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityInversePropertyPrincipalDataAnnotations	Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY INVERSE PROPERTY PRINCIPAL DATA ANNOTATIONS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY INVERSE PROPERTY PRINCIPAL DATA ANNOTATIONS:");
			}

			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL VALUE [{MEntityPrincipalValue}] !");

			if (MEntitiesDependent1!=null)
			{
				SB.AppendLine($"\tENTITIES DEPENDENT 1:");

				for(int EntityDependentIndex=0;EntityDependentIndex<MEntitiesDependent1.Count;EntityDependentIndex++)
				{
					CEntityInversePropertyDependentDataAnnotations	EntityDependent=MEntitiesDependent1[EntityDependentIndex];

					SB.AppendLine($"\t\tENTITY DEPENDENT [{(EntityDependentIndex+1)}]:");

					SB.AppendLine($"\t\t\tENTITY DEPENDENT ID [{EntityDependent.EntityDependentID}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT VALUE [{EntityDependent.EntityDependentValue}] !");
				}
			}
			else
			{
				SB.AppendLine($"\t--- ENTITIES DEPENDENT 1 is NULL ! ---");
			}

			if (MEntitiesDependent2!=null)
			{
				SB.AppendLine($"\tENTITIES DEPENDENT 2:");

				for(int EntityDependentIndex=0;EntityDependentIndex<MEntitiesDependent2.Count;EntityDependentIndex++)
				{
					CEntityInversePropertyDependentDataAnnotations	EntityDependent=MEntitiesDependent2[EntityDependentIndex];

					SB.AppendLine($"\t\tENTITY DEPENDENT [{(EntityDependentIndex+1)}]:");

					SB.AppendLine($"\t\t\tENTITY DEPENDENT ID [{EntityDependent.EntityDependentID}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT VALUE [{EntityDependent.EntityDependentValue}] !");
				}
			}
			else
			{
				SB.AppendLine($"\t--- ENTITIES DEPENDENT 2 is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------