﻿using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS je PRINCIPAL ENTITY, pretoze NEOBSAHUJE FOREIGN KEY PROPERTY.
	public sealed class CEntityOneToOne2PrincipalFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityPrincipalValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY na DEPENDENT ENTITY.
		private CEntityOneToOne2DependentFluentAPI				MEntityDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToOne2PrincipalFluentAPI()
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=default;
			MEntityDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToOne2PrincipalFluentAPI(string EntityPrincipalValue)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntityDependent=default;
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
		public CEntityOneToOne2DependentFluentAPI				EntityDependent
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
		public static void PrintToConsole(CEntityOneToOne2PrincipalFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityOneToOne2PrincipalFluentAPI				Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY ONE TO ONE PRINCIPAL FLUENT API 2 [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY ONE TO ONE PRINCIPAL FLUENT API 2:");
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