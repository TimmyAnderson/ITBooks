using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace TipsAndTechniques
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityIncludeDependent2
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityDependentValue;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
		private CEntityIncludePrincipal							MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityIncludeDependent2()
		{
			MEntityDependentID=default(int);
			MEntityDependentValue=default(string);
			MEntityPrincipalID=default(int);
			MEntityPrincipal=default(CEntityIncludePrincipal);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityIncludeDependent2(string EntityDependentValue)
		{
			MEntityDependentID=default(int);
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID=default(int);
			MEntityPrincipal=default(CEntityIncludePrincipal);
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
		public CEntityIncludePrincipal							EntityPrincipal
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
		public static void PrintToConsole(CEntityIncludeDependent2[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityIncludeDependent2						Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY DEPENDENT 2 [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY DEPENDENT 2:");
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