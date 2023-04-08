﻿using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace GoingDeeperIntoDbContext
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS je DEPENDENT ENTITY, pretoze OBSAHUJE FOREIGN KEY PROPERTY.
	public sealed class CEntityZeroToManyDependent
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentIntValue;
		private string											MEntityDependentStringValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! FOREIGN KEY v RELATIONSHIP 0:N, lebo FOREIGN KEY je NULLABLE.
		private int?											MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY na PRINCIPAL CLASS.
		private CEntityZeroToManyPrincipal						MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityZeroToManyDependent()
		{
			MEntityDependentID=default;
			MEntityDependentIntValue=default;
			MEntityDependentStringValue=default;
			MEntityPrincipalID=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityZeroToManyDependent(int EntityDependentIntValue, string EntityDependentStringValue)
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
		public int												EntityDependentIntValue
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
		public string											EntityDependentStringValue
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
		public int?												EntityPrincipalID
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
		public CEntityZeroToManyPrincipal						EntityPrincipal
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
		public static void PrintToConsole(CEntityZeroToManyDependent[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityZeroToManyDependent						Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY ZERO TO MANY DEPENDENT [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY ZERO TO MANY DEPENDENT:");
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