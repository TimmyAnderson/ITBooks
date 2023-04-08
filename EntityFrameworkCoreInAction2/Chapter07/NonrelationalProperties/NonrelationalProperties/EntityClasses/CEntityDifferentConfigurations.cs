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
	public sealed class CEntityDifferentConfigurations
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		private int												MIntNonNull;
		private int?											MIntNull;
		private string											MStringWithMaxLength;
		private string											MStringNonNullWithMaxLength;
		private string											MStringNonUnicodeWithMaxLength;
		private DateTime										MDateTimeWithSQLTypeDATEAndIndex;
		private double											MDoubleWithLimitedPrecision;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDifferentConfigurations()
		{
			MID=default(int);
			MIntNonNull=default(int);
			MIntNull=default(int);
			MStringWithMaxLength=default(string);
			MStringNonNullWithMaxLength=default(string);
			MStringNonUnicodeWithMaxLength=default(string);
			MDateTimeWithSQLTypeDATEAndIndex=default(DateTime);
			MDoubleWithLimitedPrecision=default(double);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDifferentConfigurations(int IntNonNull, int? IntNull, string StringWithMaxLength, string StringNonNullWithMaxLength, string StringNonUnicodeWithMaxLength, DateTime DateTimeWithSQLTypeDATEAndIndex, double DoubleWithLimitedPrecision)
		{
			MID=default(int);
			MIntNonNull=IntNonNull;
			MIntNull=IntNull;
			MStringWithMaxLength=StringWithMaxLength;
			MStringNonNullWithMaxLength=StringNonNullWithMaxLength;
			MStringNonUnicodeWithMaxLength=StringNonUnicodeWithMaxLength;
			MDateTimeWithSQLTypeDATEAndIndex=DateTimeWithSQLTypeDATEAndIndex;
			MDoubleWithLimitedPrecision=DoubleWithLimitedPrecision;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY je definovana BY CONVENTIONS.
		public int												Id
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
		// !!! PROPERTY je definovana BY CONVENTIONS.
		public int												IntNonNull
		{
			get
			{
				return(MIntNonNull);
			}
			set
			{
				MIntNonNull=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY je definovana BY CONVENTIONS.
		public int?												IntNull
		{
			get
			{
				return(MIntNull);
			}
			set
			{
				MIntNull=value;
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
		// !!! PROPERTY je definovana BY DATA ANNOTATIONS.
		[Required]
		[MaxLength(100)]
		public string											StringNonNullWithMaxLength
		{
			get
			{
				return(MStringNonNullWithMaxLength);
			}
			set
			{
				MStringNonNullWithMaxLength=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY je definovana BY DATA ANNOTATIONS a BY FLUENT API.
		[MaxLength(50)]
		public string											StringNonUnicodeWithMaxLength
		{
			get
			{
				return(MStringNonUnicodeWithMaxLength);
			}
			set
			{
				MStringNonUnicodeWithMaxLength=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY je definovana BY FLUENT API.
		public DateTime											DateTimeWithSQLTypeDATEAndIndex
		{
			get
			{
				return(MDateTimeWithSQLTypeDATEAndIndex);
			}
			set
			{
				MDateTimeWithSQLTypeDATEAndIndex=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY je definovana BY FLUENT API.
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
		public static void PrintToConsole(CEntityDifferentConfigurations[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityDifferentConfigurations					Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY DIFFERENT CONFIGURATIONS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY DIFFERENT CONFIGURATIONS:");
			}

			SB.AppendLine($"\tID [{MID}] !");

			SB.AppendLine($"\tINT NON NULL [{MIntNonNull}] !");
			SB.AppendLine($"\tINT NULL [{MIntNull}] !");
			SB.AppendLine($"\tSTRING WITH MAX LENGTH [{MStringWithMaxLength}] !");
			SB.AppendLine($"\tSTRING NON NULL WITH MAX LENGTH [{MStringNonNullWithMaxLength}] !");
			SB.AppendLine($"\tSTRING NON UNICODE WITH MAX LENGTH [{MStringNonUnicodeWithMaxLength}] !");
			SB.AppendLine($"\tDATE TIME WITH SQL TYPE DATE AND INDEX [{MDateTimeWithSQLTypeDATEAndIndex}] !");
			SB.AppendLine($"\tDOUBLE WITH LIMITED PRECISION [{MDoubleWithLimitedPrecision}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------