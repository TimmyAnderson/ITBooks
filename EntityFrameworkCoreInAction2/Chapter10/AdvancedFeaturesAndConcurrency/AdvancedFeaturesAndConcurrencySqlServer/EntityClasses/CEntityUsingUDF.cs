﻿using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedFeaturesAndConcurrencySqlServer
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityUsingUDF
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MStringValue;
		private int												MIntValue;
		private double											MDoubleValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityUsingUDF()
		{
			MID=default;
			MStringValue=default;
			MIntValue=default;
			MDoubleValue=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityUsingUDF(string StringValue, int IntValue, double DoubleValue)
		{
			MID=default;
			MStringValue=StringValue;
			MIntValue=IntValue;
			MDoubleValue=DoubleValue;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityUsingUDF(int ID, string StringValue, int IntValue, double DoubleValue)
		{
			MID=ID;
			MStringValue=StringValue;
			MIntValue=IntValue;
			MDoubleValue=DoubleValue;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
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
		public static void PrintToConsole(CEntityUsingUDF[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityUsingUDF									Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY USING UDF [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY USING UDF:");
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