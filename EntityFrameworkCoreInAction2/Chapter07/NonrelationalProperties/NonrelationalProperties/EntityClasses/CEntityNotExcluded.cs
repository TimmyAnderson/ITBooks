﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace NonrelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityNotExcluded
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityNotExcluded()
		{
			MID=default(int);
			MValue=default(string);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityNotExcluded(string Value)
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
		public static void PrintToConsole(CEntityNotExcluded[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityNotExcluded								Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY NOT EXCLUDED [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY NOT EXCLUDED:");
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