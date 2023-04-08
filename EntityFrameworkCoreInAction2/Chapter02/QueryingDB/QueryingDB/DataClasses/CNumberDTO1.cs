using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace QueryingDB
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CNumberDTO1
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MNumberID;
		private int												MNumber;
		private string											MNumberAsText;
		private int												MNumberSquared;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CNumberDTO1()
		{
			MNumberID=default(int);
			MNumber=default(int);
			MNumberAsText=default(string);
			MNumberSquared=default(int);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CNumberDTO1(int Number, string NumberAsText, int NumberSquared)
		{
			MNumberID=default(int);
			MNumber=Number;
			MNumberAsText=NumberAsText;
			MNumberSquared=NumberSquared;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CNumberDTO1(int NumberID, int Number, string NumberAsText, int NumberSquared)
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
		public static void PrintToConsole(CNumberDTO1[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CNumberDTO1										EntityM=Entities[Index];
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
				SB.AppendLine($"NUMBER DTO 1 [{Index}]:");
			}
			else
			{
				SB.AppendLine($"NUMBER DTO 1:");
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