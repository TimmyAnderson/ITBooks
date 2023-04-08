using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace NoSQLDatabases
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! V COSMOS DB su DEPENDENT ENTITIES ukladane ako OWNED TYPES co znamena, ze sa ulozia do RECORD PRINCIPAL ENTITY. RECORDS sa v COSMOS DB ukladaju v JSON FORMAT.
	// !!!!! Kedze v COSMOS DB DEPENDENT ENTITIES su OWNED TYPES, NEPOTREBUJU ID.
	public sealed class CEntityDependent
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentIntValue;
		private string											MEntityDependentStringValue;
		private double											MEntityDependentDoubleValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDependent()
		{
			MEntityDependentIntValue=default;
			MEntityDependentStringValue=default;
			MEntityDependentDoubleValue=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDependent(int EntityDependentIntValue, string EntityDependentStringValue, double EntityDependentDoubleValue)
		{
			MEntityDependentIntValue=EntityDependentIntValue;
			MEntityDependentStringValue=EntityDependentStringValue;
			MEntityDependentDoubleValue=EntityDependentDoubleValue;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityDependentIntValue
		{
			get
			{
				return(MEntityDependentIntValue);
			}
			set
			{
				MEntityDependentIntValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityDependentStringValue
		{
			get
			{
				return(MEntityDependentStringValue);
			}
			set
			{
				MEntityDependentStringValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public double											EntityDependentDoubleValue
		{
			get
			{
				return(MEntityDependentDoubleValue);
			}
			set
			{
				MEntityDependentDoubleValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityDependent[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityDependent								Entity=Entities[Index];
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

			SB.AppendLine($"\tENTITY DEPENDENT INT VALUE [{MEntityDependentIntValue}] !");
			SB.AppendLine($"\tENTITY DEPENDENT STRING VALUE [{MEntityDependentStringValue}] !");
			SB.AppendLine($"\tENTITY DEPENDENT DOUBLE VALUE [{MEntityDependentStringValue}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------