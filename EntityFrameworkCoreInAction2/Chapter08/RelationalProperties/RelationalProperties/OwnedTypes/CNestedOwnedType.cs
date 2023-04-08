using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS je NESTED OWNED TYPE, ktory obsahuje dalsi OWNED TYPE.
	[Owned]
	public sealed class CNestedOwnedType
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MNestedOwnedTypeInt;
		private string											MNestedOwnedTypeString;
		private COwnedTypeDataAnnotations						MOwnedType1;
		private COwnedTypeDataAnnotations						MOwnedType2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CNestedOwnedType()
		{
			MNestedOwnedTypeInt=default;
			MNestedOwnedTypeString=default;
			MOwnedType1=default;
			MOwnedType2=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CNestedOwnedType(int NestedOwnedTypeInt, string NestedOwnedTypeString, COwnedTypeDataAnnotations OwnedType1, COwnedTypeDataAnnotations OwnedType2)
		{
			MNestedOwnedTypeInt=NestedOwnedTypeInt;
			MNestedOwnedTypeString=NestedOwnedTypeString;
			MOwnedType1=OwnedType1;
			MOwnedType2=OwnedType2;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												NestedOwnedTypeInt
		{
			get
			{
				return(MNestedOwnedTypeInt);
			}
			set
			{
				MNestedOwnedTypeInt=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											NestedOwnedTypeString
		{
			get
			{
				return(MNestedOwnedTypeString);
			}
			set
			{
				MNestedOwnedTypeString=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public COwnedTypeDataAnnotations						OwnedType1
		{
			get
			{
				return(MOwnedType1);
			}
			set
			{
				MOwnedType1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public COwnedTypeDataAnnotations						OwnedType2
		{
			get
			{
				return(MOwnedType2);
			}
			set
			{
				MOwnedType2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CNestedOwnedType[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CNestedOwnedType								Entity=Entities[Index];
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
				SB.AppendLine($"NESTED OWNED TYPE [{Index}]:");
			}
			else
			{
				SB.AppendLine($"NESTED OWNED TYPE:");
			}

			SB.AppendLine($"\tNESTED OWNED TYPE INT [{MNestedOwnedTypeInt}] !");
			SB.AppendLine($"\tNESTED OWNED TYPE STRING [{MNestedOwnedTypeString}] !");

			if (MOwnedType1!=null)
			{
				SB.AppendLine($"\tOWNED TYPE 1:");

				SB.AppendLine($"\t\tOWNED TYPE INT [{MOwnedType1.OwnedTypeInt}] !");
				SB.AppendLine($"\t\tOWNED TYPE STRING [{MOwnedType1.OwnedTypeString}] !");
				SB.AppendLine($"\t\tOWNED TYPE STRING REQUIRED [{MOwnedType1.OwnedTypeStringRequired}] !");
			}
			else
			{
				SB.AppendLine($"\t--- OWNED TYPE 1 is NULL ! ---");
			}

			if (MOwnedType2!=null)
			{
				SB.AppendLine($"\tOWNED TYPE 2:");

				SB.AppendLine($"\t\tOWNED TYPE INT [{MOwnedType2.OwnedTypeInt}] !");
				SB.AppendLine($"\t\tOWNED TYPE STRING [{MOwnedType2.OwnedTypeString}] !");
				SB.AppendLine($"\t\tOWNED TYPE STRING REQUIRED [{MOwnedType2.OwnedTypeStringRequired}] !");
			}
			else
			{
				SB.AppendLine($"\t--- OWNED TYPE 2 is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------