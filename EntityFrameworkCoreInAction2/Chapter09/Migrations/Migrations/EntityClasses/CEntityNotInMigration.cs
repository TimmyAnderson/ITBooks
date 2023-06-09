﻿using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace Migrations
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! ENTITY NIE JE SUCASTOU MIGRATIONS.
	public sealed class CEntityNotInMigration
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		private int												MIntValue;
		private string											MStringValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityNotInMigration()
		{
			MID=default;
			MIntValue=default;
			MStringValue=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityNotInMigration(int IntValue, string StringValue)
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
		public static void PrintToConsole(CEntityNotInMigration[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityNotInMigration							Entity=Entities[Index];
				string											Text=Entity.Print(Index+1);
							
				if (Index>0)
				{
					CConsoleHelpers.WriteLineSeparator();
				}

				CConsoleHelpers.Write(Text,ConsoleColor.Green);
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
				SB.AppendLine($"ENTITY NOT IN MIGRATION [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY NOT IN MIGRATION:");
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