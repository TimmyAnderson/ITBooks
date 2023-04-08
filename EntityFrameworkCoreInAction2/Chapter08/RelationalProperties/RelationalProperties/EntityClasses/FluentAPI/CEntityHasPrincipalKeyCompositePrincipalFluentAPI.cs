using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityHasPrincipalKeyCompositePrincipalFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityPrincipalValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! FIELD definuje COMPOSITE PRINCIPAL KEY, ktory vytvori RELATIONSHIP, tak ze DEPENDENT ENTITIES sa budu referovat na tento PRINCIPAL KEY, a nie na PRIMARY KEY.
		// !!! FIELD ma zaroven nastaveny na UNIQUE CONSTRAINT.
		private string											MMyPrincipalKeyInEntityPrincipal1;
		private string											MMyPrincipalKeyInEntityPrincipal2;
//----------------------------------------------------------------------------------------------------------------------
		private IList<CEntityHasPrincipalKeyCompositeDependentFluentAPI>	MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityHasPrincipalKeyCompositePrincipalFluentAPI()
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=default;
			MMyPrincipalKeyInEntityPrincipal1=default;
			MMyPrincipalKeyInEntityPrincipal2=default;
			MEntitiesDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityHasPrincipalKeyCompositePrincipalFluentAPI(string EntityPrincipalValue, string MyPrincipalKeyInEntityPrincipal1, string MyPrincipalKeyInEntityPrincipal2)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=EntityPrincipalValue;
			MMyPrincipalKeyInEntityPrincipal1=MyPrincipalKeyInEntityPrincipal1;
			MMyPrincipalKeyInEntityPrincipal2=MyPrincipalKeyInEntityPrincipal2;
			MEntitiesDependent=default;
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
		public string											MyPrincipalKeyInEntityPrincipal1
		{
			get
			{
				return(MMyPrincipalKeyInEntityPrincipal1);
			}
			set
			{
				MMyPrincipalKeyInEntityPrincipal1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											MyPrincipalKeyInEntityPrincipal2
		{
			get
			{
				return(MMyPrincipalKeyInEntityPrincipal2);
			}
			set
			{
				MMyPrincipalKeyInEntityPrincipal2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IList<CEntityHasPrincipalKeyCompositeDependentFluentAPI>	EntitiesDependent
		{
			get
			{
				return(MEntitiesDependent);
			}
			set
			{
				MEntitiesDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityHasPrincipalKeyCompositePrincipalFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityHasPrincipalKeyCompositePrincipalFluentAPI	EntityN=Entities[Index];
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
				SB.AppendLine($"ENTITY HAS PRINCIPAL KEY COMPOSITE PRINCIPAL FLUENT API [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY HAS PRINCIPAL KEY COMPOSITE PRINCIPAL FLUENT API:");
			}

			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL VALUE [{MEntityPrincipalValue}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL MY ALTERNATE KEY IN PRINCIPAL ENTITY 1 [{MMyPrincipalKeyInEntityPrincipal1}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL MY ALTERNATE KEY IN PRINCIPAL ENTITY 2 [{MMyPrincipalKeyInEntityPrincipal2}] !");

			if (MEntitiesDependent!=null)
			{
				SB.AppendLine($"\tENTITIES DEPENDENT:");

				for(int EntityDependentIndex=0;EntityDependentIndex<MEntitiesDependent.Count;EntityDependentIndex++)
				{
					CEntityHasPrincipalKeyCompositeDependentFluentAPI	EntityDependent=MEntitiesDependent[EntityDependentIndex];

					SB.AppendLine($"\t\tENTITY DEPENDENT [{(EntityDependentIndex+1)}]:");

					SB.AppendLine($"\t\t\tENTITY DEPENDENT ID [{EntityDependent.EntityDependentID}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT VALUE [{EntityDependent.EntityDependentValue}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT MY ALTERNATE KEY DEPENDENT ENTITY 1 [{EntityDependent.MyPrincipalKeyInEntityDependent1}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT MY ALTERNATE KEY DEPENDENT ENTITY 2 [{EntityDependent.MyPrincipalKeyInEntityDependent2}] !");
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