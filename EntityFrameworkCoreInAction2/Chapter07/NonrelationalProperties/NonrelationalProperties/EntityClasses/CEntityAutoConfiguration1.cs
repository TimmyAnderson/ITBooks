using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;
using Microsoft.EntityFrameworkCore;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace NonrelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! ENTITY CLASS je AUTO CONFIGURED v DB CONTEXT pouzitim INTERFACE [IMutableModel].
	[CAutoConfigureEntity("EntitiesAutoConfiguration1")]
	public sealed class CEntityAutoConfiguration1
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		// !!! Pomocou AUTO CONFIGURATION bude DB COLUMN oznaceny za REQUIRED a bude mat MAX LENGTH.
		private string											MStringValue;
		// !!! Pomocou AUTO CONFIGURATION bude DB COLUMN oznaceny za REQUIRED.
		private int												MIntValue;
		// !!! Pomocou AUTO CONFIGURATION bude DB COLUMN oznaceny za a budu nan aplikovane CONSTRAINS na PRECISION a SCALE.
		private double											MDoubleValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityAutoConfiguration1()
		{
			MID=default;
			MStringValue=default;
			MIntValue=default;
			MDoubleValue=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityAutoConfiguration1(string StringValue, int IntValue, double DoubleValue)
		{
			MID=default;
			MStringValue=StringValue;
			MIntValue=IntValue;
			MDoubleValue=DoubleValue;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[CPrimaryKey]
		public int												ID
		{
			get
			{
				return(MID);
			}
			set
			{
				MID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[CRequired]
		[CMaxSize(100)]
		public string											StringValue
		{
			get
			{
				return(MStringValue);
			}
			set
			{
				MStringValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[CRequired]
		public int												IntValue
		{
			get
			{
				return(MIntValue);
			}
			set
			{
				MIntValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[CRequired]
		[CPrecision(9)]
		[CScale(2)]
		public double											DoubleValue
		{
			get
			{
				return(MDoubleValue);
			}
			set
			{
				MDoubleValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityAutoConfiguration1[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityAutoConfiguration1						Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY AUTO CONFIGURATION 1 [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY AUTO CONFIGURATION 1:");
			}

			SB.AppendLine($"\tID [{MID}] !");

			SB.AppendLine($"\tSTRING VALUE [{MStringValue}] !");
			SB.AppendLine($"\tINT VALUE [{MIntValue}] !");
			SB.AppendLine($"\tDOUBLE VALUE [{MDoubleValue}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------