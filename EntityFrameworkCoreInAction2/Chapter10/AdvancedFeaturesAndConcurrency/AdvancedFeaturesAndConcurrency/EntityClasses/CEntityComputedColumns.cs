using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedFeaturesAndConcurrency
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityComputedColumns
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MStringValue1;
		private string											MStringValue2;
		private int												MIntValue1;
		private int												MIntValue2;
		private int												MComputedValueDynamic;
		private string											MComputedValuePersistent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityComputedColumns()
		{
			MID=default;
			MStringValue1=default;
			MStringValue2=default;
			MIntValue1=default;
			MIntValue2=default;
			MComputedValueDynamic=default;
			MComputedValuePersistent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityComputedColumns(string StringValue1, string StringValue2, int IntValue1, int IntValue2)
		{
			MID=default;
			MStringValue1=StringValue1;
			MStringValue2=StringValue2;
			MIntValue1=IntValue1;
			MIntValue2=IntValue2;
			MComputedValueDynamic=default;
			MComputedValuePersistent=default;
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
		public string											StringValue1
		{
			get
			{
				return(MStringValue1);
			}
			set
			{
				MStringValue1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											StringValue2
		{
			get
			{
				return(MStringValue2);
			}
			set
			{
				MStringValue2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												IntValue1
		{
			get
			{
				return(MIntValue1);
			}
			set
			{
				MIntValue1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												IntValue2
		{
			get
			{
				return(MIntValue2);
			}
			set
			{
				MIntValue2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!! Kedze COMPUTED PROPERTIES su READ ONLY mali by mat SETTER nastaveny ako PRIVATE.
		public int												ComputedValueDynamic
		{
			get
			{
				return(MComputedValueDynamic);
			}
			private set
			{
				MComputedValueDynamic=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!! Kedze COMPUTED PROPERTIES su READ ONLY mali by mat SETTER nastaveny ako PRIVATE.
		public string											ComputedValuePersistent
		{
			get
			{
				return(MComputedValuePersistent);
			}
			private set
			{
				MComputedValuePersistent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityComputedColumns[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityComputedColumns							Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY COMPUTED COLUMNS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY COMPUTED COLUMNS:");
			}

			SB.AppendLine($"\tID [{MID}] !");
			SB.AppendLine($"\tSTRING VALUE 1 [{MStringValue1}] !");
			SB.AppendLine($"\tSTRING VALUE 2 [{MStringValue2}] !");
			SB.AppendLine($"\tINT VALUE 1 [{MIntValue1}] !");
			SB.AppendLine($"\tINT VALUE 2 [{MIntValue2}] !");
			SB.AppendLine($"\tCOMPUTED VALUE DYNAMIC [{MComputedValueDynamic}] !");
			SB.AppendLine($"\tCOMPUTED VALUE PERSISTENT [{MComputedValuePersistent}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------