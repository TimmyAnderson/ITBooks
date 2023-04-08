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
	public sealed class CEntityColumnPropertiesFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MStringNonNull;
		private string											MStringWithMaxLength;
		private DateTime										MDateTimeWithSQLTypeDATE;
		private int												MIntRenamed;
		private string											MStringNonUnicode;
		private double											MDoubleWithLimitedPrecision;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityColumnPropertiesFluentAPI()
		{
			MID=default;
			MStringNonNull=default;
			MStringWithMaxLength=default;
			MDateTimeWithSQLTypeDATE=default;
			MIntRenamed=default;
			MStringNonUnicode=default;
			MDoubleWithLimitedPrecision=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityColumnPropertiesFluentAPI(string StringNonNull, string StringWithMaxLength, DateTime DateTimeWithSQLTypeDATE, int IntRenamed, string StringNonUnicode, double DoubleWithLimitedPrecision)
		{
			MID=default;
			MStringNonNull=StringNonNull;
			MStringWithMaxLength=StringWithMaxLength;
			MDateTimeWithSQLTypeDATE=DateTimeWithSQLTypeDATE;
			MIntRenamed=IntRenamed;
			MStringNonUnicode=StringNonUnicode;
			MDoubleWithLimitedPrecision=DoubleWithLimitedPrecision;
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
		public string											StringNonUnicode
		{
			get
			{
				return(MStringNonUnicode);
			}
			set
			{
				MStringNonUnicode=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public double											DoubleWithLimitedPrecision
		{
			get
			{
				return(MDoubleWithLimitedPrecision);
			}
			set
			{
				MDoubleWithLimitedPrecision=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityColumnPropertiesFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityColumnPropertiesFluentAPI				Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY COLUMN PROPERTIES FLUENT API [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY COLUMN PROPERTIES FLUENT API:");
			}

			SB.AppendLine($"\tID [{MID}] !");

			SB.AppendLine($"\tSTRING NON NULL [{MStringNonNull}] !");
			SB.AppendLine($"\tSTRING WITH MAX LENGTH [{MStringWithMaxLength}] !");
			SB.AppendLine($"\tDATE TIME WITH SQL TYPE DATE [{MDateTimeWithSQLTypeDATE}] !");
			SB.AppendLine($"\tINT RENAMED [{MIntRenamed}] !");
			SB.AppendLine($"\tSTRING NON UNICODE [{MStringNonUnicode}] !");
			SB.AppendLine($"\tDOUBLE WITH LIMITED PRECISION [{MDoubleWithLimitedPrecision}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------