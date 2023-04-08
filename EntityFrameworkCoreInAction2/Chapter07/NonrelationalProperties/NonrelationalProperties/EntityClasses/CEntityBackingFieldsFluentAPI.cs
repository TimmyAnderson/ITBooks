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
	public sealed class CEntityBackingFieldsFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		// !!! Toto NIE je BACKING FIELD, lebo nesplna CONVENTIONS a ani je je oznaceny ako BACKING FIELD pomocou DATA ANNOTATIONS ci FLUENT API.
		private string											MNoBackingField;
		private string											MBackingField1;
		private string											MBackingField2;
		// !!!!! K tomuto FIELD NIE JE C# PROPERTY a ENTITY PROPERTY je vytvorena pomocou FLUENT API s nastavenim BACKING FIELD na tento FIELD.
		private string											MBackingField3;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityBackingFieldsFluentAPI()
		{
			MID=default;
			MNoBackingField=default;
			MBackingField1=default;
			MBackingField2=default;
			MBackingField3=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityBackingFieldsFluentAPI(string NoBackingField, string BackingField1, string BackingField2, string BackingField3)
		{
			MID=default;
			MNoBackingField=NoBackingField;
			MBackingField1=BackingField1;
			MBackingField2=BackingField2;
			MBackingField3=BackingField3;
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
		public string											NoBackingField
		{
			get
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(NoBackingField)}] READ - VALUE [{MNoBackingField}].",ConsoleColor.White);

				return(MNoBackingField);
			}
			set
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(NoBackingField)}] WRITTEN - VALUE [{value}].",ConsoleColor.White);

				MNoBackingField=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Pre PROPERTY je definovany BACKING FIELD pomocou FLUENT API.
		public string											BackingField1
		{
			get
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingField1)}] READ - VALUE [{MBackingField1}].",ConsoleColor.White);

				return(MBackingField1);
			}
			set
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingField1)}] WRITTEN - VALUE [{value}].",ConsoleColor.White);

				MBackingField1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Pre PROPERTY je definovany BACKING FIELD pomocou FLUENT API.
		public string											BackingField2
		{
			get
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingField2)}] READ - VALUE [{MBackingField2}].",ConsoleColor.White);

				return(MBackingField2);
			}
			set
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingField2)}] WRITTEN - VALUE [{value}].",ConsoleColor.White);

				MBackingField2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityBackingFieldsFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityBackingFieldsFluentAPI					Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY BACKING FIELDS FLUENT API [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY BACKING FIELDS FLUENT API:");
			}

			SB.AppendLine($"\tID [{MID}] !");

			SB.AppendLine($"\tNO BACKING FIELD [{MNoBackingField}] !");
			SB.AppendLine($"\tBACKING FIELD 1 [{MBackingField1}] !");
			SB.AppendLine($"\tBACKING FIELD 2 [{MBackingField2}] !");
			SB.AppendLine($"\tBACKING FIELD 3 [{MBackingField3}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------