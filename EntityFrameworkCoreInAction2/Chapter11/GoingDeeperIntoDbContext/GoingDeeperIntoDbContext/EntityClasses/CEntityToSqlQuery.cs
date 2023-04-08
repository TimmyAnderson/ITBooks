using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace GoingDeeperIntoDbContext
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! ENTITY vyuziva TABLE vytvorenu pomocou ENTITY 'CEntityToSqlQueryBackendData'.
	public sealed class CEntityToSqlQuery
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityID;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityIntValue;
		private string											MEntityStringValue;
		private double											MEntityDoubleValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityToSqlQuery()
		{
			MEntityID=default;
			MEntityIntValue=default;
			MEntityStringValue=default;
			MEntityDoubleValue=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityToSqlQuery(int EntityIntValue, string EntityStringValue, double EntityDoubleValue)
		{
			MEntityID=default;
			MEntityIntValue=EntityIntValue;
			MEntityStringValue=EntityStringValue;
			MEntityDoubleValue=EntityDoubleValue;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityID
		{
			get
			{
				return(MEntityID);
			}
			set
			{
				MEntityID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityIntValue
		{
			get
			{
				return(MEntityIntValue);
			}
			set
			{
				MEntityIntValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityStringValue
		{
			get
			{
				return(MEntityStringValue);
			}
			set
			{
				MEntityStringValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public double											EntityDoubleValue
		{
			get
			{
				return(MEntityDoubleValue);
			}
			set
			{
				MEntityDoubleValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityToSqlQuery[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityToSqlQuery								Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY TO SQL QUERY [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY TO SQL QUERY:");
			}

			SB.AppendLine($"\tENTITY ID [{MEntityID}] !");
			SB.AppendLine($"\tENTITY INT VALUE [{MEntityIntValue}] !");
			SB.AppendLine($"\tENTITY STRING VALUE [{MEntityStringValue}] !");
			SB.AppendLine($"\tENTITY DOUBLE VALUE [{MEntityDoubleValue}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------