using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace TipsAndTechniques
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityConstructorsPrincipal
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityPrincipalValue;
//----------------------------------------------------------------------------------------------------------------------
		private ICollection<CEntityConstructorsDependent>		MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
		public CEntityConstructorsPrincipal()
		{
			CConsoleHelpers.WriteLine("CONSTRUCTOR [CEntityConstructorsPrincipal()] CALLED.",ConsoleColor.Cyan);

			MEntityPrincipalID=default(int);
			MEntityPrincipalValue=default(string);
			MEntitiesDependent=default(ICollection<CEntityConstructorsDependent>);
		}
*/
//----------------------------------------------------------------------------------------------------------------------
		public CEntityConstructorsPrincipal(string EntityPrincipalValue)
		{
			CConsoleHelpers.WriteLine("CONSTRUCTOR [CEntityConstructorsPrincipal(string EntityPrincipalValue)] CALLED.",ConsoleColor.Cyan);

			MEntityPrincipalID=default(int);
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntitiesDependent=default(ICollection<CEntityConstructorsDependent>);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! CONSTRUCTOR sa NEZAVOLA, pretoze existuje CUSTOM CONSTUCTOR s NIZSIM POCTOM PARAMETERS, ktory sa zavola.
		public CEntityConstructorsPrincipal(int EntityPrincipalID, string EntityPrincipalValue)
		{
			CConsoleHelpers.WriteLine("CONSTRUCTOR [CEntityConstructorsPrincipal(int EntityPrincipalID, string EntityPrincipalValue)] CALLED.",ConsoleColor.Cyan);

			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntitiesDependent=default(ICollection<CEntityConstructorsDependent>);
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
				CConsoleHelpers.WriteLine($"SETTER [CEntityConstructorsPrincipal.EntityPrincipalID] CALLED with VALUE [{value}].",ConsoleColor.Blue);

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
				CConsoleHelpers.WriteLine($"SETTER [CEntityConstructorsPrincipal.EntityPrincipalValue] CALLED with VALUE [{value}].",ConsoleColor.Blue);

				MEntityPrincipalValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ICollection<CEntityConstructorsDependent>		EntitiesDependent
		{
			get
			{
				return(MEntitiesDependent);
			}
			set
			{
				CConsoleHelpers.WriteLine($"SETTER [CEntityConstructorsPrincipal.EntitiesDependent] CALLED with VALUE [{value}].",ConsoleColor.Blue);

				MEntitiesDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityConstructorsPrincipal[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityConstructorsPrincipal					Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY PRINCIPAL [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY PRINCIPAL:");
			}

			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL VALUE [{MEntityPrincipalValue}] !");

			if (MEntitiesDependent!=null)
			{
				SB.AppendLine($"\tENTITIES DEPENDENT:");

				int												EntityDependentIndex=1;

				foreach(CEntityConstructorsDependent EntityDependent in MEntitiesDependent)
				{
					SB.AppendLine($"\t\tENTITY DEPENDENT [{EntityDependentIndex}]:");

					SB.AppendLine($"\t\t\tENTITY DEPENDENT ID [{EntityDependent.EntityDependentID}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT VALUE [{EntityDependent.EntityDependentValue}] !");

					EntityDependentIndex++;
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