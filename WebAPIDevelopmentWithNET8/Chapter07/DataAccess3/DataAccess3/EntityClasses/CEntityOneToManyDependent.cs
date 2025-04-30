using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess3
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje DEPENDENT ENTITY v RELATIONSHIP 1:N.
	public sealed class CEntityOneToManyDependent
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityDependentValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! FOREIGN KEY na PRINCIPAL ENTITY.
		private int												MEntityPrincipalID;
		// !!! NAVIGATION PROPERTY na PRINCIPAL ENTITY.
		private CEntityOneToManyPrincipal						MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyDependent()
		{
			MEntityDependentID=default(int);
			MEntityDependentValue=default(string);
			MEntityPrincipalID=default(int);
			MEntityPrincipal=default(CEntityOneToManyPrincipal);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyDependent(string EntityDependentValue)
		{
			MEntityDependentID=default(int);
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID=default(int);
			MEntityPrincipal=default(CEntityOneToManyPrincipal);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyDependent(int EntityDependentID, string EntityDependentValue, int EntityPrincipalID)
		{
			MEntityDependentID=EntityDependentID;
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipal=default(CEntityOneToManyPrincipal);
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
				SB.AppendLine($"ENTITY DEPENDENT [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY DEPENDENT:");
			}

			SB.AppendLine($"\tENTITY DEPENDENT ID [{MEntityDependentID}] !");
			SB.AppendLine($"\tENTITY DEPENDENT VALUE [{MEntityDependentValue}] !");

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