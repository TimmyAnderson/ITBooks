using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityOwnedTypeOneAndMany
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityValue;
		// !!!!! OWNED TYPE sa nachadza RAZ v ENTITY.
		private COwnedTypeOne									MOwnedTypeOne;
		// !!!!! OWNED TYPE sa nachadza VIACKRAT v ENTITY.
		private IList<COwnedTypeMany>							MOwnedTypesMany;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOwnedTypeOneAndMany()
		{
			MEntityID=default;
			MEntityValue=default;
			MOwnedTypeOne=default;
			MOwnedTypesMany=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOwnedTypeOneAndMany(string EntityValue, COwnedTypeOne OwnedTypeOne, IList<COwnedTypeMany> OwnedTypesMany)
		{
			MEntityID=default;
			MEntityValue=EntityValue;
			MOwnedTypeOne=OwnedTypeOne;
			MOwnedTypesMany=OwnedTypesMany;
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
		public COwnedTypeOne									OwnedTypeOne
		{
			get
			{
				return(MOwnedTypeOne);
			}
			set
			{
				MOwnedTypeOne=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public IList<COwnedTypeMany>							OwnedTypesMany
		{
			get
			{
				return(MOwnedTypesMany);
			}
			set
			{
				MOwnedTypesMany=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityOwnedTypeOneAndMany[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityOwnedTypeOneAndMany						Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY OWNED TYPE ONE AND MANY [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY OWNED TYPE ONE AND MANY:");
			}

			SB.AppendLine($"\tENTITY ID [{MEntityID}] !");
			SB.AppendLine($"\tENTITY VALUE [{MEntityValue}] !");


			if (MOwnedTypeOne!=null)
			{
				SB.AppendLine($"\tOWNED TYPE ONE:");

				SB.AppendLine($"\t\tOWNED TYPE INT [{MOwnedTypeOne.OwnedTypeInt}] !");
				SB.AppendLine($"\t\tOWNED TYPE STRING [{MOwnedTypeOne.OwnedTypeString}] !");
				SB.AppendLine($"\t\tOWNED TYPE STRING REQUIRED [{MOwnedTypeOne.OwnedTypeStringRequired}] !");
			}
			else
			{
				SB.AppendLine($"\t--- OWNED TYPE ONE is NULL ! ---");
			}

			if (MOwnedTypesMany!=null)
			{
				SB.AppendLine($"\tOWNED TYPES MANY:");

				for(int OwnedTypesManyIndex=0;OwnedTypesManyIndex<MOwnedTypesMany.Count;OwnedTypesManyIndex++)
				{
					COwnedTypeMany								OwnedTypeMany=MOwnedTypesMany[OwnedTypesManyIndex];

					SB.AppendLine($"\t\tOWNED TYPE MANY [{(OwnedTypesManyIndex+1)}]:");

					SB.AppendLine($"\t\t\tOWNED TYPE INT [{OwnedTypeMany.OwnedTypeInt}] !");
					SB.AppendLine($"\t\t\tOWNED TYPE STRING [{OwnedTypeMany.OwnedTypeString}] !");
					SB.AppendLine($"\t\t\tOWNED TYPE STRING REQUIRED [{OwnedTypeMany.OwnedTypeStringRequired}] !");
				}
			}
			else
			{
				SB.AppendLine($"\t--- OWNED TYPES MANY is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------