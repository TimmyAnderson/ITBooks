﻿using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace GoingDeeperIntoDbContext
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS je PRINCIPAL ENTITY, pretoze NEOBSAHUJE FOREIGN KEY PROPERTY.
	public sealed class CEntityZeroToManyPrincipal
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalIntValue;
		private string											MEntityPrincipalStringValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY na DEPENDENT ENTITIES.
		private IList<CEntityZeroToManyDependent>				MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityZeroToManyPrincipal()
		{
			MEntityPrincipalID=default;
			MEntityPrincipalIntValue=default;
			MEntityPrincipalStringValue=default;
			MEntitiesDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityZeroToManyPrincipal(int EntityPrincipalIntValue, string EntityPrincipalStringValue)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalIntValue=EntityPrincipalIntValue;
			MEntityPrincipalStringValue=EntityPrincipalStringValue;
			MEntitiesDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityZeroToManyPrincipal(int EntityPrincipalIntValue, string EntityPrincipalStringValue, IList<CEntityZeroToManyDependent> EntitiesDependent)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalIntValue=EntityPrincipalIntValue;
			MEntityPrincipalStringValue=EntityPrincipalStringValue;
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
		public int												EntityPrincipalIntValue
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
		public string											EntityPrincipalStringValue
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
		public IList<CEntityZeroToManyDependent>				EntitiesDependent
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
		public static void PrintToConsole(CEntityZeroToManyPrincipal[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityZeroToManyPrincipal						Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY ZERO TO MANY PRINCIPAL [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY ZERO TO MANY PRINCIPAL:");
			}

			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL INT VALUE [{MEntityPrincipalIntValue}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL STRING VALUE [{MEntityPrincipalStringValue}] !");

			if (MEntitiesDependent!=null)
			{
				SB.AppendLine($"\tENTITIES DEPENDENT:");

				for(int EntityDependentIndex=0;EntityDependentIndex<MEntitiesDependent.Count;EntityDependentIndex++)
				{
					CEntityZeroToManyDependent					EntityDependent=MEntitiesDependent[EntityDependentIndex];

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