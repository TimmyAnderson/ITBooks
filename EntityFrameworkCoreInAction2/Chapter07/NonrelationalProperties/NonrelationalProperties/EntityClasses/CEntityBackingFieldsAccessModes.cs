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
	public sealed class CEntityBackingFieldsAccessModes
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MBackingFieldField;
		private string											MBackingFieldFieldDuringConstruction;
		private string											MBackingFieldProperty;
		private string											MBackingFieldPreferField;
		private string											MBackingFieldPreferFieldDuringConstruction;
		private string											MBackingFieldPreferProperty;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityBackingFieldsAccessModes()
		{
			MID=default;
			MBackingFieldField=default;
			MBackingFieldFieldDuringConstruction=default;
			MBackingFieldProperty=default;
			MBackingFieldPreferField=default;
			MBackingFieldPreferFieldDuringConstruction=default;
			MBackingFieldPreferProperty=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityBackingFieldsAccessModes(string BackingFieldField, string BackingFieldFieldDuringConstruction, string BackingFieldProperty, string BackingFieldPreferField, string BackingFieldPreferFieldDuringConstruction, string BackingFieldPreferProperty)
		{
			MID=default;
			MBackingFieldField=BackingFieldField;
			MBackingFieldFieldDuringConstruction=BackingFieldFieldDuringConstruction;
			MBackingFieldProperty=BackingFieldProperty;
			MBackingFieldPreferField=BackingFieldPreferField;
			MBackingFieldPreferFieldDuringConstruction=BackingFieldPreferFieldDuringConstruction;
			MBackingFieldPreferProperty=BackingFieldPreferProperty;
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
		public string											BackingFieldField
		{
			get
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingFieldField)}] READ - VALUE [{MBackingFieldField}].",ConsoleColor.White);

				return(MBackingFieldField);
			}
			set
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingFieldField)}] WRITTEN - VALUE [{value}].",ConsoleColor.White);

				MBackingFieldField=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											BackingFieldFieldDuringConstruction
		{
			get
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingFieldFieldDuringConstruction)}] READ - VALUE [{MBackingFieldFieldDuringConstruction}].",ConsoleColor.White);

				return(MBackingFieldFieldDuringConstruction);
			}
			set
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingFieldFieldDuringConstruction)}] WRITTEN - VALUE [{value}].",ConsoleColor.White);

				MBackingFieldFieldDuringConstruction=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											BackingFieldProperty
		{
			get
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingFieldProperty)}] READ - VALUE [{MBackingFieldProperty}].",ConsoleColor.White);

				return(MBackingFieldProperty);
			}
			set
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingFieldProperty)}] WRITTEN - VALUE [{value}].",ConsoleColor.White);

				MBackingFieldProperty=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											BackingFieldPreferField
		{
			get
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingFieldPreferField)}] READ - VALUE [{MBackingFieldPreferField}].",ConsoleColor.White);

				return(MBackingFieldPreferField);
			}
			set
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingFieldPreferField)}] WRITTEN - VALUE [{value}].",ConsoleColor.White);

				MBackingFieldPreferField=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											BackingFieldPreferFieldDuringConstruction
		{
			get
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingFieldPreferFieldDuringConstruction)}] READ - VALUE [{MBackingFieldPreferFieldDuringConstruction}].",ConsoleColor.White);

				return(MBackingFieldPreferFieldDuringConstruction);
			}
			set
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingFieldPreferFieldDuringConstruction)}] WRITTEN - VALUE [{value}].",ConsoleColor.White);

				MBackingFieldPreferFieldDuringConstruction=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											BackingFieldPreferProperty
		{
			get
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingFieldPreferProperty)}] READ - VALUE [{MBackingFieldPreferProperty}].",ConsoleColor.White);

				return(MBackingFieldPreferProperty);
			}
			set
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingFieldPreferProperty)}] WRITTEN - VALUE [{value}].",ConsoleColor.White);

				MBackingFieldPreferProperty=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityBackingFieldsAccessModes[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityBackingFieldsAccessModes					Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY BACKING FIELDS ACCESS MODES [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY BACKING FIELDS ACCESS MODES:");
			}

			SB.AppendLine($"\tID [{MID}] !");

			SB.AppendLine($"\tBACKING FIELD FIELD [{MBackingFieldField}] !");
			SB.AppendLine($"\tBACKING FIELD FIELD DURING CONSTRUCTION [{MBackingFieldFieldDuringConstruction}] !");
			SB.AppendLine($"\tBACKING FIELD PROPERTY [{MBackingFieldProperty}] !");
			SB.AppendLine($"\tBACKING FIELD PREFER FIELD [{MBackingFieldPreferField}] !");
			SB.AppendLine($"\tBACKING FIELD PREFER FIELD DURING CONSTRUCTION [{MBackingFieldPreferFieldDuringConstruction}] !");
			SB.AppendLine($"\tBACKING FIELD PREFER PROPERTY [{MBackingFieldPreferProperty}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------