using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace TipsAndTechniques
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityConstructorsDependent
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityDependentValue;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
		private CEntityConstructorsPrincipal					MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
		public CEntityConstructorsDependent()
		{
			CConsoleHelpers.WriteLine("CONSTRUCTOR [CEntityConstructorsDependent()] CALLED.",ConsoleColor.Cyan);

			MEntityDependentID=default(int);
			MEntityDependentValue=default(string);
			MEntityPrincipalID=default(int);
			MEntityPrincipal=default(CEntityConstructorsPrincipal);
		}
*/
//----------------------------------------------------------------------------------------------------------------------
/*
		public CEntityConstructorsDependent(string EntityDependentValue)
		{
			CConsoleHelpers.WriteLine("CONSTRUCTOR [CEntityConstructorsDependent(string EntityDependentValue)] CALLED.",ConsoleColor.Cyan);

			MEntityDependentID=default(int);
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID=default(int);
			MEntityPrincipal=default(CEntityConstructorsPrincipal);
		}
*/
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! CONSTRUCTOR sa zavola IBA ak NIE JE povoleny DEFAULT CONSTRCTOR, ani CUSTOM CONSTRUCTOR s MENSIM POCTOM PARAMETERS.
		public CEntityConstructorsDependent(string EntityDependentValue, int EntityPrincipalID)
		{
			CConsoleHelpers.WriteLine("CONSTRUCTOR [CEntityConstructorsDependent(string EntityDependentValue, int EntityPrincipalID)] CALLED.",ConsoleColor.Cyan);

			MEntityDependentID=default(int);
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipal=default(CEntityConstructorsPrincipal);
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
				CConsoleHelpers.WriteLine($"SETTER [CEntityConstructorsDependent.EntityDependentID] CALLED with VALUE [{value}].",ConsoleColor.Blue);

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
				CConsoleHelpers.WriteLine($"SETTER [CEntityConstructorsDependent.EntityDependentValue] CALLED with VALUE [{value}].",ConsoleColor.Blue);

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
				CConsoleHelpers.WriteLine($"SETTER [CEntityConstructorsDependent.EntityPrincipalID] CALLED with VALUE [{value}].",ConsoleColor.Blue);

				MEntityPrincipalID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityConstructorsPrincipal						EntityPrincipal
		{
			get
			{
				return(MEntityPrincipal);
			}
			set
			{
				CConsoleHelpers.WriteLine($"SETTER [CEntityConstructorsDependent.EntityPrincipal] CALLED with VALUE [{value}].",ConsoleColor.Blue);

				MEntityPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityConstructorsDependent[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityConstructorsDependent					Entity=Entities[Index];
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