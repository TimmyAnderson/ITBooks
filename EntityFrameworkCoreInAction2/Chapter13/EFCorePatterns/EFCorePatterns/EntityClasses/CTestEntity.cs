﻿using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace EFCorePatterns
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CTestEntity
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CTestEntity()
		{
			MID=default(int);
			MValue=default(string);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CTestEntity(string Value)
		{
			MID=default(int);
			MValue=Value;
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CTestEntity[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CTestEntity										Entity=Entities[Index];
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
				SB.AppendLine($"TEST ENTITY [{Index}]:");
			}
			else
			{
				SB.AppendLine($"TEST ENTITY:");
			}

			SB.AppendLine($"\tID [{MID}] !");
			SB.AppendLine($"\tVALUE [{MValue}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------