using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityHasPrincipalKeyCompositeDependentFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityDependentValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! FIELD definuje COMPOSITE FOREIGN KEY na PRINCIPAL KEY PRINCIPAL ENTITY. FOREIGN KEY DEPENDENT ENTITY sa teda nereferuje na PRIMARY KEY PRINCIPAL ENTITY, ale na PRINCIPAL KEY PRINCIPAL ENTITY.
		private string											MMyPrincipalKeyInEntityDependent1;
		private string											MMyPrincipalKeyInEntityDependent2;
//----------------------------------------------------------------------------------------------------------------------
		private CEntityHasPrincipalKeyCompositePrincipalFluentAPI	MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityHasPrincipalKeyCompositeDependentFluentAPI()
		{
			MEntityDependentID=default;
			MEntityDependentValue=default;
			MMyPrincipalKeyInEntityDependent1=default;
			MMyPrincipalKeyInEntityDependent2=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityHasPrincipalKeyCompositeDependentFluentAPI(string EntityDependentValue, string MyPrincipalKeyInEntityDependent1, string MyPrincipalKeyInEntityDependent2)
		{
			MEntityDependentID=default;
			MEntityDependentValue=EntityDependentValue;
			MMyPrincipalKeyInEntityDependent1=MyPrincipalKeyInEntityDependent1;
			MMyPrincipalKeyInEntityDependent2=MyPrincipalKeyInEntityDependent2;
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
		public string											MyPrincipalKeyInEntityDependent1
		{
			get
			{
				return(MMyPrincipalKeyInEntityDependent1);
			}
			set
			{
				MMyPrincipalKeyInEntityDependent1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											MyPrincipalKeyInEntityDependent2
		{
			get
			{
				return(MMyPrincipalKeyInEntityDependent2);
			}
			set
			{
				MMyPrincipalKeyInEntityDependent2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityHasPrincipalKeyCompositePrincipalFluentAPI	EntityPrincipal
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
		public static void PrintToConsole(CEntityHasPrincipalKeyCompositeDependentFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityHasPrincipalKeyCompositeDependentFluentAPI	EntityN=Entities[Index];
				string											EntityNText=EntityN.Print(Index+1);
							
				if (Index>0)
				{
					CConsoleHelpers.WriteLineSeparator();
				}

				CConsoleHelpers.Write(EntityNText,ConsoleColor.Green);
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
				SB.AppendLine($"ENTITY HAS PRINCIPAL KEY COMPOSITE DEPENDENT FLUENT API [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY HAS PRINCIPAL KEY COMPOSITE DEPENDENT FLUENT API:");
			}

			SB.AppendLine($"\tDEPENDENT ENTITY ID [{MEntityDependentID}] !");
			SB.AppendLine($"\tDEPENDENT ENTITY VALUE [{MEntityDependentValue}] !");
			SB.AppendLine($"\tDEPENDENT ENTITY MY PRINCIPAL KEY IN DEPENDENT ENTITY 1 [{MMyPrincipalKeyInEntityDependent1}] !");
			SB.AppendLine($"\tDEPENDENT ENTITY MY PRINCIPAL KEY IN DEPENDENT ENTITY 2 [{MMyPrincipalKeyInEntityDependent2}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------