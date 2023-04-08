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
	public sealed class CEntityBackingFieldsConventions
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		// !!! Toto NIE je BACKING FIELD, lebo nesplna CONVENTIONS.
		private string											MNoBackingField;
		// !!! NAZVY FIELDS musia splnat CONVENTIONS voci nazvom PROPERTIES.
		private string											m_BackingField1;
		private string											_BackingField2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityBackingFieldsConventions()
		{
			MID=default;
			MNoBackingField=default;
			m_BackingField1=default;
			_BackingField2=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityBackingFieldsConventions(string NoBackingField, string BackingField1, string BackingField2)
		{
			MID=default;
			MNoBackingField=NoBackingField;
			m_BackingField1=BackingField1;
			_BackingField2=BackingField2;
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
		public string											BackingField1
		{
			get
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingField1)}] READ - VALUE [{m_BackingField1}].",ConsoleColor.White);

				return(m_BackingField1);
			}
			set
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingField1)}] WRITTEN - VALUE [{value}].",ConsoleColor.White);

				m_BackingField1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											BackingField2
		{
			get
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingField2)}] READ - VALUE [{_BackingField2}].",ConsoleColor.White);

				return(_BackingField2);
			}
			set
			{
				CConsoleHelpers.WriteLine($"PROPERTY [{nameof(BackingField2)}] WRITTEN - VALUE [{value}].",ConsoleColor.White);

				_BackingField2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityBackingFieldsConventions[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityBackingFieldsConventions					Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY BACKING FIELDS CONVENTIONS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY BACKING FIELDS CONVENTIONS:");
			}

			SB.AppendLine($"\tID [{MID}] !");

			SB.AppendLine($"\tNO BACKING FIELD [{MNoBackingField}] !");
			SB.AppendLine($"\tBACKING FIELD 1 [{m_BackingField1}] !");
			SB.AppendLine($"\tBACKING FIELD 2 [{_BackingField2}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------