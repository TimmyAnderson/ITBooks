﻿using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedFeaturesAndConcurrency
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityDefaultValueColumns
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MValue;
		private DateTime										MDefaultValue1;
		private double											MDefaultValue2;
		private int												MDefaultValue3;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDefaultValueColumns()
		{
			MID=default;
			MValue=default;
			MDefaultValue1=default;
			MDefaultValue2=default;
			MDefaultValue3=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDefaultValueColumns(string Value, DateTime DefaultValue1, double DefaultValue2, int DefaultValue3)
		{
			MID=default;
			MValue=Value;
			MDefaultValue1=DefaultValue1;
			MDefaultValue2=DefaultValue2;
			MDefaultValue3=DefaultValue3;
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
		public string											Value
		{
			get
			{
				return(MValue);
			}
			set
			{
				MValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DateTime											DefaultValue1
		{
			get
			{
				return(MDefaultValue1);
			}
			set
			{
				MDefaultValue1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public double											DefaultValue2
		{
			get
			{
				return(MDefaultValue2);
			}
			set
			{
				MDefaultValue2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												DefaultValue3
		{
			get
			{
				return(MDefaultValue3);
			}
			set
			{
				MDefaultValue3=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityDefaultValueColumns[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityDefaultValueColumns						Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY DEFAULT VALUE COLUMNS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY DEFAULT VALUE COLUMNS:");
			}

			SB.AppendLine($"\tID [{MID}] !");
			SB.AppendLine($"\tVALUE [{MValue}] !");
			SB.AppendLine($"\tDEFAULT VALUE 1 [{MDefaultValue1}] !");
			SB.AppendLine($"\tDEFAULT VALUE 2 [{MDefaultValue2}] !");
			SB.AppendLine($"\tDEFAULT VALUE 3 [{MDefaultValue3}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------