using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace NoSQLDatabases
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityPrincipal
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalIntValue;
		private string											MEntityPrincipalStringValue;
		private double											MEntityPrincipalDoubleValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Toto NIE JE NAVIGATION PROPERTY, ale COLLECTION OWNED TYPES, ktore su v COSMOS DB ulozene ako JSON ARRAY PRINCIPAL ENTITY.
		private List<CEntityDependent>							MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityPrincipal()
		{
			MEntityPrincipalID=default;
			MEntityPrincipalIntValue=default;
			MEntityPrincipalStringValue=default;
			MEntityPrincipalDoubleValue=default;
			MEntitiesDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! PRIMARY KEY MUSI byt EXPLICITNE NASTAVENY, pretoze COSMOS DB ho NEGENERUJE AUTOMATICKY.
		public CEntityPrincipal(int EntityPrincipalID, int EntityPrincipalIntValue, string EntityPrincipalStringValue, double EntityPrincipalDoubleValue, List<CEntityDependent> EntitiesDependent)
		{
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipalIntValue=EntityPrincipalIntValue;
			MEntityPrincipalStringValue=EntityPrincipalStringValue;
			MEntityPrincipalDoubleValue=EntityPrincipalDoubleValue;
			MEntitiesDependent=EntitiesDependent;
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
		public int												EntityPrincipalIntValue
		{
			get
			{
				return(MEntityPrincipalIntValue);
			}
			set
			{
				MEntityPrincipalIntValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityPrincipalStringValue
		{
			get
			{
				return(MEntityPrincipalStringValue);
			}
			set
			{
				MEntityPrincipalStringValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public double											EntityPrincipalDoubleValue
		{
			get
			{
				return(MEntityPrincipalDoubleValue);
			}
			set
			{
				MEntityPrincipalDoubleValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public List<CEntityDependent>					EntitiesDependent
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
		public static void PrintToConsole(CEntityPrincipal[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityPrincipal								Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY ONE TO MANY PRINCIPAL [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY ONE TO MANY PRINCIPAL:");
			}

			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL INT VALUE [{MEntityPrincipalIntValue}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL STRING VALUE [{MEntityPrincipalStringValue}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL DOUBLE VALUE [{MEntityPrincipalDoubleValue}] !");

			if (MEntitiesDependent!=null)
			{
				SB.AppendLine($"\tENTITIES DEPENDENT:");

				for(int EntityDependentIndex=0;EntityDependentIndex<MEntitiesDependent.Count;EntityDependentIndex++)
				{
					CEntityDependent							EntityDependent=MEntitiesDependent[EntityDependentIndex];

					SB.AppendLine($"\t\tENTITY DEPENDENT [{(EntityDependentIndex+1)}]:");

					SB.AppendLine($"\t\t\tENTITY DEPENDENT INT VALUE [{EntityDependent.EntityDependentIntValue}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT STRING VALUE [{EntityDependent.EntityDependentStringValue}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT DOUBLE VALUE [{EntityDependent.EntityDependentDoubleValue}] !");
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