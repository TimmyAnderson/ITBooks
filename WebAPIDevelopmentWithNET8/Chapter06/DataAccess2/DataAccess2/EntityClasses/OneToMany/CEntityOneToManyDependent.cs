﻿using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess2
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS je DEPENDENT ENTITY, pretoze OBSAHUJE FOREIGN KEY PROPERTY.
	public sealed class CEntityOneToManyDependent
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
		private CEntityOneToManyPrincipal						MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyDependent()
		{
			MEntityDependentID=default;
			MEntityDependentValue=default;
			MEntityPrincipalID=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyDependent(string EntityDependentValue)
		{
			MEntityDependentID=default;
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyDependent(string EntityDependentValue, int EntityPrincipalID)
		{
			MEntityDependentID=default;
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyDependent(int EntityDependentID, string EntityDependentValue, int EntityPrincipalID)
		{
			MEntityDependentID=EntityDependentID;
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyDependent(string EntityDependentValue, CEntityOneToManyPrincipal EntityPrincipal)
		{
			MEntityDependentID=default;
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID=default;
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
		public CEntityOneToManyPrincipal						EntityPrincipal
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
		public static void PrintToConsole(CEntityOneToManyDependent[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityOneToManyDependent						Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY ONE TO MANY DEPENDENT [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY ONE TO MANY DEPENDENT:");
			}

			SB.AppendLine($"\tENTITY DEPENDENT ID [{MEntityDependentID}] !");
			SB.AppendLine($"\tENTITY DEPENDENT VALUE [{MEntityDependentValue}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");

			if (MEntityPrincipal!=null)
			{
				SB.AppendLine($"\tENTITY PRINCIPAL:");

				SB.AppendLine($"\t\tENTITY PRINCIPAL ID [{MEntityPrincipal.EntityPrincipalID}] !");
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