using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS je PRINCIPAL ENTITY, pretoze NEOBSAHUJE FOREIGN KEY PROPERTY.
	public sealed class CEntityTableSplittingPrincipalFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityPrincipalValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY na DEPENDENT ENTITIES.
		private CEntityTableSplittingDependent1FluentAPI		MEntityDependent1;
		private CEntityTableSplittingDependent2FluentAPI		MEntityDependent2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityTableSplittingPrincipalFluentAPI()
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=default;
			MEntityDependent1=default;
			MEntityDependent2=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityTableSplittingPrincipalFluentAPI(string EntityPrincipalValue)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntityDependent1=default;
			MEntityDependent2=default;
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
		public CEntityTableSplittingDependent1FluentAPI			EntityDependent1
		{
			get
			{
				return(MEntityDependent1);
			}
			set
			{
				MEntityDependent1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityTableSplittingDependent2FluentAPI			EntityDependent2
		{
			get
			{
				return(MEntityDependent2);
			}
			set
			{
				MEntityDependent2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityTableSplittingPrincipalFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityTableSplittingPrincipalFluentAPI			Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY TABLE SPLITTING PRINCIPAL FLUENT API [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY TABLE SPLITTING PRINCIPAL FLUENT API:");
			}

			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL VALUE [{MEntityPrincipalValue}] !");

			if (MEntityDependent1!=null)
			{
				SB.AppendLine($"\tENTITY DEPENDENT 1:");

				SB.AppendLine($"\t\tENTITY DEPENDENT ID [{MEntityDependent1.EntityDependentID}] !");
				SB.AppendLine($"\t\tENTITY DEPENDENT VALUE 1 [{MEntityDependent1.EntityDependentValue1}] !");
				SB.AppendLine($"\t\tENTITY SHARED VALUE [{MEntityDependent1.EntitySharedValue}] !");
			}
			else
			{
				SB.AppendLine($"\t--- ENTITY DEPENDENT 1 is NULL ! ---");
			}

			if (MEntityDependent2!=null)
			{
				SB.AppendLine($"\tENTITY DEPENDENT 2:");

				SB.AppendLine($"\t\tENTITY DEPENDENT ID [{MEntityDependent2.EntityDependentID}] !");
				SB.AppendLine($"\t\tENTITY DEPENDENT VALUE 2 [{MEntityDependent2.EntityDependentValue2}] !");
				SB.AppendLine($"\t\tENTITY SHARED VALUE [{MEntityDependent2.EntitySharedValue}] !");
			}
			else
			{
				SB.AppendLine($"\t--- ENTITY DEPENDENT 2 is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------