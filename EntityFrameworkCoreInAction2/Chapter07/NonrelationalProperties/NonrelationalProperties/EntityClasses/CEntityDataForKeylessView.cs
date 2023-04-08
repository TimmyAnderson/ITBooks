﻿using System;
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
	// !!!!! ENTITY CLASS vytvara DATA pre VIEW pouzivany v CLASS 'CEntityKeylessDataAnnotations' a CLASS 'CEntityKeylessFluentAPI'.
	public sealed class CEntityDataForKeylessView
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		private int												MIntValue;
		private string											MStringValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataForKeylessView()
		{
			MID=default;
			MIntValue=default;
			MStringValue=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataForKeylessView(int IntValue, string StringValue)
		{
			MID=default;
			MIntValue=IntValue;
			MStringValue=StringValue;
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityDataForKeylessView[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityDataForKeylessView						Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY DATA FOR KEYLESS VIEW [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY DATA FOR KEYLESS VIEW:");
			}

			SB.AppendLine($"\tID [{MID}] !");

			SB.AppendLine($"\tINT VALUE [{MIntValue}] !");
			SB.AppendLine($"\tSTRING VALUE [{MStringValue}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------