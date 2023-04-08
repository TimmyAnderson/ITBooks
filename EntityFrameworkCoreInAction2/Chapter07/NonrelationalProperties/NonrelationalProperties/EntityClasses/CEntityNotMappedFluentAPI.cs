using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace NonrelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityNotMappedFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MValue;
		private string											MExcludedPropertyValue;
		private CEntityNotExcluded								MNotExcludedClassValue;
		private CEntityExcludedFluentAPI						MExcludedClassValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityNotMappedFluentAPI()
		{
			MID=default;
			MValue=default;
			MExcludedPropertyValue=default;
			MNotExcludedClassValue=default;
			MExcludedClassValue=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityNotMappedFluentAPI(string Value, string ExcludedPropertyValue, CEntityNotExcluded NotExcludedClassValue, CEntityExcludedFluentAPI ExcludedClassValue)
		{
			MID=default(int);
			MValue=Value;
			MExcludedPropertyValue=ExcludedPropertyValue;
			MNotExcludedClassValue=NotExcludedClassValue;
			MExcludedClassValue=ExcludedClassValue;
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
		// !!! PROPERTY NEBUDE MAPPED do DB nastavenim cez FLUENT API.
		public string											ExcludedPropertyValue
		{
			get
			{
				return(MExcludedPropertyValue);
			}
			set
			{
				MExcludedPropertyValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY BUDE MAPPED do DB.
		public CEntityNotExcluded								NotExcludedClassValue
		{
			get
			{
				return(MNotExcludedClassValue);
			}
			set
			{
				MNotExcludedClassValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityExcludedFluentAPI							ExcludedClassValue
		{
			get
			{
				return(MExcludedClassValue);
			}
			set
			{
				MExcludedClassValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityNotMappedFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityNotMappedFluentAPI						Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY NOT MAPPED FLUENT API [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY NOT MAPPED FLUENT API:");
			}

			SB.AppendLine($"\tID [{MID}] !");

			SB.AppendLine($"\tVALUE [{MValue}] !");
			SB.AppendLine($"\tEXCLUDED PROPERTY VALUE [{MExcludedPropertyValue}] !");
			SB.AppendLine($"\tNOT EXCLUDED CLASS VALUE -> ID [{MNotExcludedClassValue?.ID}] !");
			SB.AppendLine($"\tNOT EXCLUDED CLASS VALUE -> VALUE [{MNotExcludedClassValue?.Value}] !");
			SB.AppendLine($"\tEXCLUDED CLASS VALUE -> VALUE [{MExcludedClassValue?.Value}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------