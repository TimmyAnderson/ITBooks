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
	public sealed class CEntityNotMappedDataAnnotations
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MValue;
		private string											MExcludedPropertyValue;
		private CEntityNotExcluded								MNotExcludedClassValue;
		private CEntityExcludedDataAnnotations					MExcludedClassValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityNotMappedDataAnnotations()
		{
			MID=default(int);
			MValue=default(string);
			MExcludedPropertyValue=default(string);
			MNotExcludedClassValue=default;
			MExcludedClassValue=default(CEntityExcludedDataAnnotations);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityNotMappedDataAnnotations(string Value, string ExcludedPropertyValue, CEntityNotExcluded NotExcludedClassValue, CEntityExcludedDataAnnotations ExcludedClassValue)
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
		// !!! PROPERTY NEBUDE MAPPED do DB.
		[NotMapped]
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
		// !!! PROPERTY NEBUDE MAPPED do DB.
		public CEntityExcludedDataAnnotations					ExcludedClassValue
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
		public static void PrintToConsole(CEntityNotMappedDataAnnotations[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityNotMappedDataAnnotations					Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY NOT MAPPED DATA ANNOTATIONS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY NOT MAPPED DATA ANNOTATIONS:");
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