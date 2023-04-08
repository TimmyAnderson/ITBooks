using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityHasPrincipalKeyDependentFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityDependentValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! FIELD definuje FOREIGN KEY na PRINCIPAL KEY PRINCIPAL ENTITY. FOREIGN KEY DEPENDENT ENTITY sa teda nereferuje na PRIMARY KEY PRINCIPAL ENTITY, ale na PRINCIPAL KEY PRINCIPAL ENTITY.
		private string											MMyPrincipalKeyInEntityDependent;
//----------------------------------------------------------------------------------------------------------------------
		private CEntityHasPrincipalKeyPrincipalFluentAPI		MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityHasPrincipalKeyDependentFluentAPI()
		{
			MEntityDependentID=default;
			MEntityDependentValue=default;
			MMyPrincipalKeyInEntityDependent=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityHasPrincipalKeyDependentFluentAPI(string EntityDependentValue, string MyPrincipalKeyInEntityDependent)
		{
			MEntityDependentID=default;
			MEntityDependentValue=EntityDependentValue;
			MMyPrincipalKeyInEntityDependent=MyPrincipalKeyInEntityDependent;
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
		public string											MyPrincipalKeyInEntityDependent
		{
			get
			{
				return(MMyPrincipalKeyInEntityDependent);
			}
			set
			{
				MMyPrincipalKeyInEntityDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityHasPrincipalKeyPrincipalFluentAPI			EntityPrincipal
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
		public static void PrintToConsole(CEntityHasPrincipalKeyDependentFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityHasPrincipalKeyDependentFluentAPI		EntityN=Entities[Index];
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
				SB.AppendLine($"ENTITY HAS PRINCIPAL KEY DEPENDENT FLUENT API [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY HAS PRINCIPAL KEY DEPENDENT FLUENT API:");
			}

			SB.AppendLine($"\tDEPENDENT ENTITY ID [{MEntityDependentID}] !");
			SB.AppendLine($"\tDEPENDENT ENTITY VALUE [{MEntityDependentValue}] !");
			SB.AppendLine($"\tDEPENDENT ENTITY MY PRINCIPAL KEY IN DEPENDENT ENTITY [{MMyPrincipalKeyInEntityDependent}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------