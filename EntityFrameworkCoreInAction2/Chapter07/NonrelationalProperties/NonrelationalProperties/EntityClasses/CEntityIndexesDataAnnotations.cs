using System;
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
	// !!! DEFINUJU sa INDEXES.
	[Index(nameof(SingleColumnIndex),IsUnique=false,Name="My_SingleColumnIndex_DataAnnotations")]
	[Index(nameof(MultiColumnIndex1),nameof(MultiColumnIndex2),IsUnique=true,Name="My_MultiColumnIndex_DataAnnotations")]
	[Index(nameof(SingleColumnUniqueIndex),IsUnique=true,Name="My_SingleColumnUniqueIndex_DataAnnotations")]
	public sealed class CEntityIndexesDataAnnotations
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MSingleColumnIndex;
		private string											MMultiColumnIndex1;
		private string											MMultiColumnIndex2;
		private string											MSingleColumnUniqueIndex;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityIndexesDataAnnotations()
		{
			MID=default;
			MSingleColumnIndex=default;
			MMultiColumnIndex1=default;
			MMultiColumnIndex2=default;
			MSingleColumnUniqueIndex=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityIndexesDataAnnotations(string SingleColumnIndex, string MultiColumnIndex1, string MultiColumnIndex2, string SingleColumnUniqueIndex)
		{
			MID=default;
			MSingleColumnIndex=SingleColumnIndex;
			MMultiColumnIndex1=MultiColumnIndex1;
			MMultiColumnIndex2=MultiColumnIndex2;
			MSingleColumnUniqueIndex=SingleColumnUniqueIndex;
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
		public string											SingleColumnIndex
		{
			get
			{
				return(MSingleColumnIndex);
			}
			set
			{
				MSingleColumnIndex=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											MultiColumnIndex1
		{
			get
			{
				return(MMultiColumnIndex1);
			}
			set
			{
				MMultiColumnIndex1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											MultiColumnIndex2
		{
			get
			{
				return(MMultiColumnIndex2);
			}
			set
			{
				MMultiColumnIndex2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											SingleColumnUniqueIndex
		{
			get
			{
				return(MSingleColumnUniqueIndex);
			}
			set
			{
				MSingleColumnUniqueIndex=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityIndexesDataAnnotations[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityIndexesDataAnnotations					Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY INDEXES DATA ANNOTATIONS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY INDEXES DATA ANNOTATIONS:");
			}

			SB.AppendLine($"\tID [{MID}] !");

			SB.AppendLine($"\tMULTI COLUMN INDEX [{MSingleColumnIndex}] !");
			SB.AppendLine($"\tMULTI COLUMN INDEX 1 [{MMultiColumnIndex1}] !");
			SB.AppendLine($"\tMULTI COLUMN INDEX 2 [{MMultiColumnIndex2}] !");
			SB.AppendLine($"\tSINGLE COLUMN UNIQUE INDEX [{MSingleColumnUniqueIndex}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------