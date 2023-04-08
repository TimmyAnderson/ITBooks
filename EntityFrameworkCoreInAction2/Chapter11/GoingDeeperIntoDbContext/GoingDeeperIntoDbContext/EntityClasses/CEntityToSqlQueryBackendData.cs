using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace GoingDeeperIntoDbContext
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! ENTITY sluzi na vytvorenie TABLE na ktoru sa pripoji ENTITY 'CEntityToSqlQuery', ktora je vytvarana pomocou METHOD [EntityTypeBuilder<TEntity> EntityTypeBuilder<TEntity>.ToSqlQuery<TEntity>(string Query)].
	public sealed class CEntityToSqlQueryBackendData
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
		public CEntityToSqlQueryBackendData()
		{
			MEntityID=default;
			MEntityIntValue=default;
			MEntityStringValue=default;
			MEntityDoubleValue=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityToSqlQueryBackendData(int EntityIntValue, string EntityStringValue, double EntityDoubleValue)
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
		public static void PrintToConsole(CEntityToSqlQueryBackendData[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityToSqlQueryBackendData					Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY TO SQL QUERY BACKEND DATA [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY TO SQL QUERY BACKEND DATA:");
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