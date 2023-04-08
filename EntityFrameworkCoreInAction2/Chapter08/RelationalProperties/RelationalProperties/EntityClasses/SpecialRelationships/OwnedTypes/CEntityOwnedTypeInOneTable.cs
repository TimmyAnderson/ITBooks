using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityOwnedTypeInOneTable
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityValue;
		private COwnedTypeDataAnnotations						MOwnedTypeDataAnnotations;
		private COwnedTypeDataAnnotations						MOwnedTypeDataAnnotationsRequired;
		private COwnedTypeFluentAPI								MOwnedTypeFluentAPI;
		private CNestedOwnedType								MNestedOwnedType;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOwnedTypeInOneTable()
		{
			MEntityID=default;
			MEntityValue=default;
			MOwnedTypeDataAnnotations=default;
			MOwnedTypeDataAnnotationsRequired=default;
			MOwnedTypeFluentAPI=default;
			MNestedOwnedType=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOwnedTypeInOneTable(string EntityValue, COwnedTypeDataAnnotations OwnedTypeDataAnnotations, COwnedTypeDataAnnotations OwnedTypeDataAnnotationsRequired, COwnedTypeFluentAPI OwnedTypeFluentAPI, CNestedOwnedType NestedOwnedType)
		{
			MEntityID=default;
			MEntityValue=EntityValue;
			MOwnedTypeDataAnnotations=OwnedTypeDataAnnotations;
			MOwnedTypeDataAnnotationsRequired=OwnedTypeDataAnnotationsRequired;
			MOwnedTypeFluentAPI=OwnedTypeFluentAPI;
			MNestedOwnedType=NestedOwnedType;
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
		public COwnedTypeFluentAPI								OwnedTypeFluentAPI
		{
			get
			{
				return(MOwnedTypeFluentAPI);
			}
			set
			{
				MOwnedTypeFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CNestedOwnedType									NestedOwnedType
		{
			get
			{
				return(MNestedOwnedType);
			}
			set
			{
				MNestedOwnedType=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityOwnedTypeInOneTable[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityOwnedTypeInOneTable						Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY OWNED TYPE IN ONE TABLE [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY OWNED TYPE IN ONE TABLE:");
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

			if (MOwnedTypeFluentAPI!=null)
			{
				SB.AppendLine($"\tOWNED TYPE FLUENT API:");

				SB.AppendLine($"\t\tOWNED TYPE INT [{MOwnedTypeFluentAPI.OwnedTypeInt}] !");
				SB.AppendLine($"\t\tOWNED TYPE STRING [{MOwnedTypeFluentAPI.OwnedTypeString}] !");
				SB.AppendLine($"\t\tOWNED TYPE STRING REQUIRED [{MOwnedTypeFluentAPI.OwnedTypeStringRequired}] !");
			}
			else
			{
				SB.AppendLine($"\t--- OWNED TYPE FLUENT API is NULL ! ---");
			}

			if (MNestedOwnedType!=null)
			{
				SB.AppendLine($"\tNESTED OWNED TYPE:");

				SB.AppendLine($"\t\tNESTED OWNED TYPE INT [{MNestedOwnedType.NestedOwnedTypeInt}] !");
				SB.AppendLine($"\t\tNESTED OWNED TYPE STRING [{MNestedOwnedType.NestedOwnedTypeString}] !");

				if (MNestedOwnedType.OwnedType1!=null)
				{
					SB.AppendLine($"\t\tOWNED TYPE 1:");

					SB.AppendLine($"\t\t\tOWNED TYPE INT [{MNestedOwnedType.OwnedType1.OwnedTypeInt}] !");
					SB.AppendLine($"\t\t\tOWNED TYPE STRING [{MNestedOwnedType.OwnedType1.OwnedTypeString}] !");
					SB.AppendLine($"\t\t\tOWNED TYPE STRING REQUIRED [{MNestedOwnedType.OwnedType1.OwnedTypeStringRequired}] !");
				}
				else
				{
					SB.AppendLine($"\t\t--- OWNED TYPE 1 is NULL ! ---");
				}

				if (MNestedOwnedType.OwnedType2!=null)
				{
					SB.AppendLine($"\t\tOWNED TYPE 2:");

					SB.AppendLine($"\t\t\tOWNED TYPE INT [{MNestedOwnedType.OwnedType2.OwnedTypeInt}] !");
					SB.AppendLine($"\t\t\tOWNED TYPE STRING [{MNestedOwnedType.OwnedType2.OwnedTypeString}] !");
					SB.AppendLine($"\t\t\tOWNED TYPE STRING REQUIRED [{MNestedOwnedType.OwnedType2.OwnedTypeStringRequired}] !");
				}
				else
				{
					SB.AppendLine($"\t\t--- OWNED TYPE 2 is NULL ! ---");
				}
			}
			else
			{
				SB.AppendLine($"\t--- NESTED OWNED TYPE is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------