using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace TipsAndTechniques
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityGroupByFunction
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MNumberID;
		private int												MNumber;
		private string											MNumberAsText;
		private int												MNumericValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityGroupByFunction()
		{
			MNumberID=default(int);
			MNumber=default(int);
			MNumberAsText=default(string);
			MNumericValue=default(int);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityGroupByFunction(int Number, string NumberAsText, int NumericValue)
		{
			MNumberID=default(int);
			MNumber=Number;
			MNumberAsText=NumberAsText;
			MNumericValue=NumericValue;
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
		public int												NumericValue
		{
			get
			{
				return(MNumericValue);
			}
			set
			{
				MNumericValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityGroupByFunction[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityGroupByFunction							Entity=Entities[Index];
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
				SB.AppendLine($"GROUP BY FUNCTION [{Index}]:");
			}
			else
			{
				SB.AppendLine($"GROUP BY FUNCTION:");
			}

			SB.AppendLine($"\tNUMBER ID [{MNumberID}] !");
			SB.AppendLine($"\tNUMBER [{MNumber}] !");
			SB.AppendLine($"\tNUMBER AS TEXT [{MNumberAsText}] !");
			SB.AppendLine($"\tNUMERIC VALUE [{MNumericValue}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------