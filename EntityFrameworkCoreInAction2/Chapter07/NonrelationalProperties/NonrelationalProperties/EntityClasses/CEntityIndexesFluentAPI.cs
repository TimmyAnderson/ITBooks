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
	public sealed class CEntityIndexesFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MSingleColumnIndex;
		private string											MMultiColumnIndex1;
		private string											MMultiColumnIndex2;
		private string											MSingleColumnUniqueIndex;
		private int												MSingleColumnFilteredIndex;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityIndexesFluentAPI()
		{
			MID=default;
			MSingleColumnIndex=default;
			MMultiColumnIndex1=default;
			MMultiColumnIndex2=default;
			MSingleColumnUniqueIndex=default;
			MSingleColumnFilteredIndex=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityIndexesFluentAPI(string SingleColumnIndex, string MultiColumnIndex1, string MultiColumnIndex2, string SingleColumnUniqueIndex, int SingleColumnFilteredIndex)
		{
			MID=default;
			MSingleColumnIndex=SingleColumnIndex;
			MMultiColumnIndex1=MultiColumnIndex1;
			MMultiColumnIndex2=MultiColumnIndex2;
			MSingleColumnUniqueIndex=SingleColumnUniqueIndex;
			MSingleColumnFilteredIndex=SingleColumnFilteredIndex;
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
		public int											SingleColumnFilteredIndex
		{
			get
			{
				return(MSingleColumnFilteredIndex);
			}
			set
			{
				MSingleColumnFilteredIndex=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityIndexesFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityIndexesFluentAPI							Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY INDEXES FLUENT API [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY INDEXES FLUENT API:");
			}

			SB.AppendLine($"\tID [{MID}] !");

			SB.AppendLine($"\tMULTI COLUMN INDEX [{MSingleColumnIndex}] !");
			SB.AppendLine($"\tMULTI COLUMN INDEX 1 [{MMultiColumnIndex1}] !");
			SB.AppendLine($"\tMULTI COLUMN INDEX 2 [{MMultiColumnIndex2}] !");
			SB.AppendLine($"\tSINGLE COLUMN UNIQUE INDEX [{MSingleColumnUniqueIndex}] !");
			SB.AppendLine($"\tSINGLE COLUMN FILTERED INDEX [{MSingleColumnFilteredIndex}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------