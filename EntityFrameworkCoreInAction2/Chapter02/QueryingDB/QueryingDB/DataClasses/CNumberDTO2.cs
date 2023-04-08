using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace QueryingDB
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CNumberDTO2
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MNumberID;
		private int												MNumber;
		private string											MNumberAsText;
		private int												MNumberSquared;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CNumberDTO2()
		{
			MNumberID=default(int);
			MNumber=default(int);
			MNumberAsText=default(string);
			MNumberSquared=default(int);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CNumberDTO2(int Number, string NumberAsText, int NumberSquared)
		{
			MNumberID=default(int);
			MNumber=Number;
			MNumberAsText=NumberAsText;
			MNumberSquared=NumberSquared;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CNumberDTO2(int NumberID, int Number, string NumberAsText, int NumberSquared)
		{
			MNumberID=NumberID;
			MNumber=Number;
			MNumberAsText=NumberAsText;
			MNumberSquared=NumberSquared;
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
		public int												NumberSquared
		{
			get
			{
				return(MNumberSquared);
			}
			set
			{
				MNumberSquared=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CNumberDTO2[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CNumberDTO2										EntityM=Entities[Index];
				string											EntityMText=EntityM.Print(Index+1);
							
				if (Index>0)
				{
					CConsoleHelpers.WriteLineSeparator();
				}

				CConsoleHelpers.Write(EntityMText,ConsoleColor.Green);
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
				SB.AppendLine($"NUMBER DTO 2 [{Index}]:");
			}
			else
			{
				SB.AppendLine($"NUMBER DTO 2:");
			}

			SB.AppendLine($"\tNUMBER ID [{MNumberID}] !");
			SB.AppendLine($"\tNUMBER [{MNumber}] !");
			SB.AppendLine($"\tNUMBER AS TEXT [{MNumberAsText}] !");
			SB.AppendLine($"\tNUMBER SQUARED [{MNumberSquared}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------