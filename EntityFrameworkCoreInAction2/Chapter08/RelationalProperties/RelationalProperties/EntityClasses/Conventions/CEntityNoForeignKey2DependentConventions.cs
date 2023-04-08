using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS je DEPENDENT ENTITY, pretoze OBSAHUJE FOREIGN KEY PROPERTY.
	// !!!!! DEPENDENT CLASS NEMA FOREIGN KEY ani NAVIGATION PROPERTY na PRINCIPAL ENTITY.
	// !!!!! ENTITY FRAMEWORK CORE vytvori pre FOREIGN KEY SHADOW PROPERTY s NAME [<PRINCIPAL_ENTITY_CLASS_NAME><PRINCIPAL_KEY_NAME>].
	// !!!!! FOREIGN KEY SHADOW PROPERTY je BY-DEFAULT NULLABLE.
	public sealed class CEntityNoForeignKey2DependentConventions
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityDependentValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityNoForeignKey2DependentConventions()
		{
			MEntityDependentID=default;
			MEntityDependentValue=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityNoForeignKey2DependentConventions(string EntityDependentValue)
		{
			MEntityDependentID=default;
			MEntityDependentValue=EntityDependentValue;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityDependentID
		{
			get
			{
				return(MEntityDependentID);
			}
			set
			{
				MEntityDependentID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityDependentValue
		{
			get
			{
				return(MEntityDependentValue);
			}
			set
			{
				MEntityDependentValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityNoForeignKey2DependentConventions[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityNoForeignKey2DependentConventions		Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY NO FOREIGN KEY 2 DEPENDENT CONVENTIONS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY NO FOREIGN KEY 2 DEPENDENT CONVENTIONS:");
			}

			SB.AppendLine($"\tENTITY DEPENDENT ID [{MEntityDependentID}] !");
			SB.AppendLine($"\tENTITY DEPENDENT VALUE [{MEntityDependentValue}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------