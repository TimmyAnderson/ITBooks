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
	public sealed class CEntityColumnPropertiesDataAnnotations
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MStringNonNull;
		private string											MStringWithMaxLength;
		private DateTime										MDateTimeWithSQLTypeDATE;
		private int												MIntRenamed;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityColumnPropertiesDataAnnotations()
		{
			MID=default;
			MStringNonNull=default;
			MStringWithMaxLength=default;
			MDateTimeWithSQLTypeDATE=default;
			MIntRenamed=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityColumnPropertiesDataAnnotations(string StringNonNull, string StringWithMaxLength, DateTime DateTimeWithSQLTypeDATE, int IntRenamed)
		{
			MID=default;
			MStringNonNull=StringNonNull;
			MStringWithMaxLength=StringWithMaxLength;
			MDateTimeWithSQLTypeDATE=DateTimeWithSQLTypeDATE;
			MIntRenamed=IntRenamed;
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
		[Required]
		public string											StringNonNull
		{
			get
			{
				return(MStringNonNull);
			}
			set
			{
				MStringNonNull=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY je definovana BY DATA ANNOTATIONS.
		[MaxLength(50)]
		public string											StringWithMaxLength
		{
			get
			{
				return(MStringWithMaxLength);
			}
			set
			{
				MStringWithMaxLength=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Column(TypeName="date")]
		public DateTime											DateTimeWithSQLTypeDATE
		{
			get
			{
				return(MDateTimeWithSQLTypeDATE);
			}
			set
			{
				MDateTimeWithSQLTypeDATE=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Column("My_IntRenamed")]
		public int												IntRenamed
		{
			get
			{
				return(MIntRenamed);
			}
			set
			{
				MIntRenamed=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityColumnPropertiesDataAnnotations[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityColumnPropertiesDataAnnotations			Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY COLUMN PROPERTIES DATA ANNOTATIONS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY COLUMN PROPERTIES DATA ANNOTATIONS:");
			}

			SB.AppendLine($"\tID [{MID}] !");

			SB.AppendLine($"\tSTRING NON NULL [{MStringNonNull}] !");
			SB.AppendLine($"\tSTRING WITH MAX LENGTH [{MStringWithMaxLength}] !");
			SB.AppendLine($"\tDATE TIME WITH SQL TYPE DATE [{MDateTimeWithSQLTypeDATE}] !");
			SB.AppendLine($"\tINT RENAMED [{MIntRenamed}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------