using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace NonrelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityUsingValueConversions
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
		private string											MValue;
		private EEnumType										MEnumTypeNoConversion;
		private EEnumType										MEnumTypeWithConversion1;
		private EEnumType										MEnumTypeWithConversion2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityUsingValueConversions()
		{
			MID=default(int);
			MValue=default(string);
			MEnumTypeNoConversion=default(EEnumType);
			MEnumTypeWithConversion1=default(EEnumType);
			MEnumTypeWithConversion2=default(EEnumType);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityUsingValueConversions(string Value, EEnumType EnumTypeNoConversion, EEnumType EnumTypeWithConversion1, EEnumType EnumTypeWithConversion2)
		{
			MID=default(int);
			MValue=Value;
			MEnumTypeNoConversion=EnumTypeNoConversion;
			MEnumTypeWithConversion1=EnumTypeWithConversion1;
			MEnumTypeWithConversion2=EnumTypeWithConversion2;
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
			private set
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
			private set
			{
				MValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public EEnumType										EnumTypeNoConversion
		{
			get
			{
				return(MEnumTypeNoConversion);
			}
			private set
			{
				MEnumTypeNoConversion=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public EEnumType										EnumTypeWithConversion1
		{
			get
			{
				return(MEnumTypeWithConversion1);
			}
			private set
			{
				MEnumTypeWithConversion1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public EEnumType										EnumTypeWithConversion2
		{
			get
			{
				return(MEnumTypeWithConversion2);
			}
			private set
			{
				MEnumTypeWithConversion2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityUsingValueConversions[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityUsingValueConversions					Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY USING VALUE CONVERSIONS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY USING VALUE CONVERSIONS:");
			}

			SB.AppendLine($"\tID [{MID}] !");

			SB.AppendLine($"\tVALUE [{MValue}] !");
			SB.AppendLine($"\tENUM TYPE NO CONVERSION [{MEnumTypeNoConversion}] !");
			SB.AppendLine($"\tENUM TYPE WITH CONVERSION 1 [{MEnumTypeWithConversion1}] !");
			SB.AppendLine($"\tENUM TYPE WITH CONVERSION 2 [{MEnumTypeWithConversion2}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------