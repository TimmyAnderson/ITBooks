using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityOwnedTypeInMultiTables
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityValue;
		private COwnedTypeDataAnnotations						MOwnedTypeDataAnnotations;
		private COwnedTypeDataAnnotations						MOwnedTypeDataAnnotationsRequired;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOwnedTypeInMultiTables()
		{
			MEntityID=default;
			MEntityValue=default;
			MOwnedTypeDataAnnotations=default;
			MOwnedTypeDataAnnotationsRequired=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOwnedTypeInMultiTables(string EntityValue, COwnedTypeDataAnnotations OwnedTypeDataAnnotations, COwnedTypeDataAnnotations OwnedTypeDataAnnotationsRequired)
		{
			MEntityID=default;
			MEntityValue=EntityValue;
			MOwnedTypeDataAnnotations=OwnedTypeDataAnnotations;
			MOwnedTypeDataAnnotationsRequired=OwnedTypeDataAnnotationsRequired;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityID
		{
			get
			{
				return(MEntityID);
			}
			set
			{
				MEntityID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityValue
		{
			get
			{
				return(MEntityValue);
			}
			set
			{
				MEntityValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public COwnedTypeDataAnnotations						OwnedTypeDataAnnotations
		{
			get
			{
				return(MOwnedTypeDataAnnotations);
			}
			set
			{
				MOwnedTypeDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public COwnedTypeDataAnnotations						OwnedTypeDataAnnotationsRequired
		{
			get
			{
				return(MOwnedTypeDataAnnotationsRequired);
			}
			set
			{
				MOwnedTypeDataAnnotationsRequired=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityOwnedTypeInMultiTables[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityOwnedTypeInMultiTables					Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY OWNED TYPE IN MULTI TABLES [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY OWNED TYPE IN MULTI TABLES:");
			}

			SB.AppendLine($"\tENTITY ID [{MEntityID}] !");
			SB.AppendLine($"\tENTITY VALUE [{MEntityValue}] !");

			if (MOwnedTypeDataAnnotations!=null)
			{
				SB.AppendLine($"\tOWNED TYPE DATA ANNOTATIONS:");

				SB.AppendLine($"\t\tOWNED TYPE INT [{MOwnedTypeDataAnnotations.OwnedTypeInt}] !");
				SB.AppendLine($"\t\tOWNED TYPE STRING [{MOwnedTypeDataAnnotations.OwnedTypeString}] !");
				SB.AppendLine($"\t\tOWNED TYPE STRING REQUIRED [{MOwnedTypeDataAnnotations.OwnedTypeStringRequired}] !");
			}
			else
			{
				SB.AppendLine($"\t--- OWNED TYPE DATA ANNOTATIONS is NULL ! ---");
			}

			if (MOwnedTypeDataAnnotationsRequired!=null)
			{
				SB.AppendLine($"\tOWNED TYPE DATA ANNOTATIONS REQUIRED:");

				SB.AppendLine($"\t\tOWNED TYPE INT [{MOwnedTypeDataAnnotationsRequired.OwnedTypeInt}] !");
				SB.AppendLine($"\t\tOWNED TYPE STRING [{MOwnedTypeDataAnnotationsRequired.OwnedTypeString}] !");
				SB.AppendLine($"\t\tOWNED TYPE STRING REQUIRED [{MOwnedTypeDataAnnotationsRequired.OwnedTypeStringRequired}] !");
			}
			else
			{
				SB.AppendLine($"\t--- OWNED TYPE DATA ANNOTATIONS REQUIRED is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------