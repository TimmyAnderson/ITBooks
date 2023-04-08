﻿using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS je PRINCIPAL ENTITY, pretoze NEOBSAHUJE FOREIGN KEY PROPERTY.
	public sealed class CEntityOnDeleteNoActionNotNullPrincipalFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityPrincipalValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY na DEPENDENT ENTITIES.
		private IList<CEntityOnDeleteNoActionNotNullDependentFluentAPI>	MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOnDeleteNoActionNotNullPrincipalFluentAPI()
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=default;
			MEntitiesDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOnDeleteNoActionNotNullPrincipalFluentAPI(string EntityPrincipalValue)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntitiesDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOnDeleteNoActionNotNullPrincipalFluentAPI(string EntityPrincipalValue, IList<CEntityOnDeleteNoActionNotNullDependentFluentAPI> EntitiesDependent)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntitiesDependent=EntitiesDependent;
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
		public IList<CEntityOnDeleteNoActionNotNullDependentFluentAPI>	EntitiesDependent
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
		public static void PrintToConsole(CEntityOnDeleteNoActionNotNullPrincipalFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityOnDeleteNoActionNotNullPrincipalFluentAPI	Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY ON DELETE NO ACTION NOT NULL PRINCIPAL FLUENT API [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY ON DELETE NO ACTION NOT NULL PRINCIPAL FLUENT API:");
			}

			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL VALUE [{MEntityPrincipalValue}] !");

			if (MEntitiesDependent!=null)
			{
				SB.AppendLine($"\tENTITIES DEPENDENT:");

				for(int EntityDependentIndex=0;EntityDependentIndex<MEntitiesDependent.Count;EntityDependentIndex++)
				{
					CEntityOnDeleteNoActionNotNullDependentFluentAPI	EntityDependent=MEntitiesDependent[EntityDependentIndex];

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