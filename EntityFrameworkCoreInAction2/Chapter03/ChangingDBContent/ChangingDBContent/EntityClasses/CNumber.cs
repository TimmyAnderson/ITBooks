﻿using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace ChangingDBContent
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CNumber
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MNumberID;
		private int												MNumber;
		private string											MNumberAsText;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CNumber()
		{
			MNumberID=default(int);
			MNumber=default(int);
			MNumberAsText=default(string);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CNumber(int Number, string NumberAsText)
		{
			MNumberID=default(int);
			MNumber=Number;
			MNumberAsText=NumberAsText;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												NumberID
		{
			get
			{
				return(MNumberID);
			}
			set
			{
				MNumberID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												Number
		{
			get
			{
				return(MNumber);
			}
			set
			{
				MNumber=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											NumberAsText
		{
			get
			{
				return(MNumberAsText);
			}
			set
			{
				MNumberAsText=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CNumber[] Numbers)
		{
			for(int Index=0;Index<Numbers.Length;Index++)
			{
				CNumber											Number=Numbers[Index];
				string											NumberText=Number.Print(Index+1);
							
				if (Index>0)
				{
					CConsoleHelpers.WriteLineSeparator();
				}

				CConsoleHelpers.Write(NumberText,ConsoleColor.Green);
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
				SB.AppendLine($"NUMBER [{Index}]:");
			}
			else
			{
				SB.AppendLine($"NUMBER:");
			}

			SB.AppendLine($"\tNUMBER ID [{MNumberID}] !");
			SB.AppendLine($"\tNUMBER [{MNumber}] !");
			SB.AppendLine($"\tNUMBER AS TEXT [{MNumberAsText}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------