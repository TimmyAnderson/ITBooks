using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! HELPER CLASS na pracu s PROPERTY BAG ENTITY.
	public sealed class CMyPropertyBag
	{
//----------------------------------------------------------------------------------------------------------------------
		public const string										PROPERTY_BAG_PRINCIPAL_TABLE_NAME="My_PROPERTY_BAG_PRINCIPAL";
//----------------------------------------------------------------------------------------------------------------------
		public const string										PROPERTY_BAG_PRINCIPAL_COLUMN_ID="ID";
		public const string										PROPERTY_BAG_PRINCIPAL_COLUMN_VALUE_INT="ValueInt";
		public const string										PROPERTY_BAG_PRINCIPAL_COLUMN_VALUE_STRING="ValueString";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private readonly int									MEntityPrincipalID;
		private readonly int									MEntityPrincipalValueInt;
		private readonly string									MEntityPrincipalValueString;
//----------------------------------------------------------------------------------------------------------------------
		private readonly CEntityPropertyBagDependentFluentAPI[]	MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private CMyPropertyBag(int EntityPrincipalID, int EntityPrincipalValueInt, string EntityPrincipalValueString, CEntityPropertyBagDependentFluentAPI[] EntitiesDependent)
		{
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipalValueInt=EntityPrincipalValueInt;
			MEntityPrincipalValueString=EntityPrincipalValueString;
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
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityPrincipalValueInt
		{
			get
			{
				return(MEntityPrincipalValueInt);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityPrincipalValueString
		{
			get
			{
				return(MEntityPrincipalValueString);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityPropertyBagDependentFluentAPI[]			EntitiesDependent
		{
			get
			{
				return(MEntitiesDependent);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static CMyPropertyBag FromPropertyBag(Dictionary<string,object> PropertyBag, CEntityPropertyBagDependentFluentAPI[] EntitiesDependent)
		{
			int													EntityPrincipalID;
			int													EntityPrincipalValueInt;
			string												EntityPrincipalValueString;

			EntityPrincipalID=(int) PropertyBag[PROPERTY_BAG_PRINCIPAL_COLUMN_ID];
			EntityPrincipalValueInt=(int) PropertyBag[PROPERTY_BAG_PRINCIPAL_COLUMN_VALUE_INT];
			EntityPrincipalValueString=(string) PropertyBag[PROPERTY_BAG_PRINCIPAL_COLUMN_VALUE_STRING];

			CMyPropertyBag										MyPropertyBag=new CMyPropertyBag(EntityPrincipalID,EntityPrincipalValueInt,EntityPrincipalValueString,EntitiesDependent);

			return(MyPropertyBag);
		}
//----------------------------------------------------------------------------------------------------------------------
		public static Dictionary<string,object> ToPropertyBag(int EntityPrincipalID, int EntityPrincipalValueInt, string EntityPrincipalValueString)
		{
			Dictionary<string,object>							PropertyBag=new Dictionary<string,object>();

			PropertyBag.Add(PROPERTY_BAG_PRINCIPAL_COLUMN_ID,EntityPrincipalID);
			PropertyBag.Add(PROPERTY_BAG_PRINCIPAL_COLUMN_VALUE_INT,EntityPrincipalValueInt);
			PropertyBag.Add(PROPERTY_BAG_PRINCIPAL_COLUMN_VALUE_STRING,EntityPrincipalValueString);

			return(PropertyBag);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CMyPropertyBag[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CMyPropertyBag									Entity=Entities[Index];
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
				SB.AppendLine($"MY PROPERTY BAG [{Index}]:");
			}
			else
			{
				SB.AppendLine($"MY PROPERTY BAG:");
			}

			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL VALUE INT [{MEntityPrincipalValueInt}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL VALUE STRING [{MEntityPrincipalValueString}] !");

			if (MEntitiesDependent!=null)
			{
				SB.AppendLine($"\tENTITIES DEPENDENT:");

				for(int EntityDependentIndex=0;EntityDependentIndex<MEntitiesDependent.Length;EntityDependentIndex++)
				{
					CEntityPropertyBagDependentFluentAPI		EntityDependent=MEntitiesDependent[EntityDependentIndex];

					SB.AppendLine($"\t\tENTITY DEPENDENT [{(EntityDependentIndex+1)}]:");

					SB.AppendLine($"\t\t\tENTITY DEPENDENT ID [{EntityDependent.EntityDependentID}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT VALUE [{EntityDependent.EntityDependentValue}] !");
					SB.AppendLine($"\t\t\tENTITY PRINCIPAL ID [{EntityDependent.EntityPrincipalID}] !");
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