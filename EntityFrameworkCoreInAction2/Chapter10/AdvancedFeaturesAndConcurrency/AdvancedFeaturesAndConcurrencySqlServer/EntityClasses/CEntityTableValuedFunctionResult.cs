using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedFeaturesAndConcurrencySqlServer
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! ENTITY sluzi ako RESULT TABLE VALUED FUNCTION.
	// !!!!! ENTITY NEMA KEY.
	public sealed class CEntityTableValuedFunctionResult
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MStringValue;
		private int												MIntValue;
		private double											MDoubleValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityTableValuedFunctionResult()
		{
			MStringValue=default;
			MIntValue=default;
			MDoubleValue=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityTableValuedFunctionResult(string StringValue, int IntValue, double DoubleValue)
		{
			MStringValue=StringValue;
			MIntValue=IntValue;
			MDoubleValue=DoubleValue;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
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
		public double											DoubleValue
		{
			get
			{
				return(MDoubleValue);
			}
			set
			{
				MDoubleValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityTableValuedFunctionResult[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityTableValuedFunctionResult				Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY TABLE VALUED FUNCTION RESULT [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY TABLE VALUED FUNCTION RESULT:");
			}

			SB.AppendLine($"\tSTRING VALUE [{MStringValue}] !");
			SB.AppendLine($"\tINT VALUE [{MIntValue}] !");
			SB.AppendLine($"\tDOUBLE VALUE [{MDoubleValue}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------