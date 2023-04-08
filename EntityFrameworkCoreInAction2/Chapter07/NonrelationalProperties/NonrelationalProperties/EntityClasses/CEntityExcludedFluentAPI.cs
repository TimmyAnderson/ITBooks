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
	// !!! CLASS NEBUDE MAPPED do DB nastavenim cez FLUENT API.
	public sealed class CEntityExcludedFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityExcludedFluentAPI()
		{
			MValue=default(string);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityExcludedFluentAPI(string Value)
		{
			MValue=Value;
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
		public static void PrintToConsole(CEntityExcludedFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityExcludedFluentAPI						Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY EXCLUDED FLUENT API [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY EXCLUDED FLUENT API:");
			}

			SB.AppendLine($"\tVALUE [{MValue}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------