using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace TipsAndTechniques
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityIncludePrincipal
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityPrincipalValue;
//----------------------------------------------------------------------------------------------------------------------
		private ICollection<CEntityIncludeDependent1>			MEntitiesDependent1;
		private ICollection<CEntityIncludeDependent2>			MEntitiesDependent2;
		private ICollection<CEntityIncludeDependent3>			MEntitiesDependent3;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityIncludePrincipal()
		{
			MEntityPrincipalID=default(int);
			MEntityPrincipalValue=default(string);
			MEntitiesDependent1=default(ICollection<CEntityIncludeDependent1>);
			MEntitiesDependent2=default(ICollection<CEntityIncludeDependent2>);
			MEntitiesDependent3=default(ICollection<CEntityIncludeDependent3>);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityIncludePrincipal(string EntityPrincipalValue, ICollection<CEntityIncludeDependent1> EntitiesDependent1, ICollection<CEntityIncludeDependent2> EntitiesDependent2, ICollection<CEntityIncludeDependent3> EntitiesDependent3)
		{
			MEntityPrincipalID=default(int);
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntitiesDependent1=EntitiesDependent1;
			MEntitiesDependent2=EntitiesDependent2;
			MEntitiesDependent3=EntitiesDependent3;
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
		public ICollection<CEntityIncludeDependent1>			EntitiesDependent1
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
		public ICollection<CEntityIncludeDependent2>			EntitiesDependent2
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
		public ICollection<CEntityIncludeDependent3>			EntitiesDependent3
		{
			get
			{
				return(MEntitiesDependent3);
			}
			set
			{
				MEntitiesDependent3=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityIncludePrincipal[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityIncludePrincipal							Entity=Entities[Index];
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

			if (MEntitiesDependent1!=null)
			{
				SB.AppendLine($"\tENTITIES DEPENDENT 1:");

				int												EntityDependentIndex=1;

				foreach(CEntityIncludeDependent1 EntityDependent in MEntitiesDependent1)
				{
					SB.AppendLine($"\t\tENTITY DEPENDENT 1 [{EntityDependentIndex}]:");

					SB.AppendLine($"\t\t\tENTITY DEPENDENT ID [{EntityDependent.EntityDependentID}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT VALUE [{EntityDependent.EntityDependentValue}] !");

					EntityDependentIndex++;
				}
			}
			else
			{
				SB.AppendLine($"\t--- ENTITIES DEPENDENT 1 is NULL ! ---");
			}

			if (MEntitiesDependent2!=null)
			{
				SB.AppendLine($"\tENTITIES DEPENDENT 2:");

				int												EntityDependentIndex=1;

				foreach(CEntityIncludeDependent2 EntityDependent in MEntitiesDependent2)
				{
					SB.AppendLine($"\t\tENTITY DEPENDENT 2 [{EntityDependentIndex}]:");

					SB.AppendLine($"\t\t\tENTITY DEPENDENT ID [{EntityDependent.EntityDependentID}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT VALUE [{EntityDependent.EntityDependentValue}] !");

					EntityDependentIndex++;
				}
			}
			else
			{
				SB.AppendLine($"\t--- ENTITIES DEPENDENT 2 is NULL ! ---");
			}

			if (MEntitiesDependent3!=null)
			{
				SB.AppendLine($"\tENTITIES DEPENDENT 3:");

				int												EntityDependentIndex=1;

				foreach(CEntityIncludeDependent3 EntityDependent in MEntitiesDependent3)
				{
					SB.AppendLine($"\t\tENTITY DEPENDENT 3 [{EntityDependentIndex}]:");

					SB.AppendLine($"\t\t\tENTITY DEPENDENT ID [{EntityDependent.EntityDependentID}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT VALUE [{EntityDependent.EntityDependentValue}] !");

					EntityDependentIndex++;
				}
			}
			else
			{
				SB.AppendLine($"\t--- ENTITIES DEPENDENT 3 is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------