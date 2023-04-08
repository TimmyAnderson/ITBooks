using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedFeaturesAndConcurrency
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityDBGeneratedPropertiesFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MDatabaseGeneratedOnAdd;
		private int												MDatabaseGeneratedOnAddOrUpdate;
		private int												MDatabaseGeneratedOnUpdate;
		private int												MNonDatabaseGenerated;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDBGeneratedPropertiesFluentAPI()
		{
			MDatabaseGeneratedOnAdd=default;
			MDatabaseGeneratedOnAddOrUpdate=default;
			MDatabaseGeneratedOnUpdate=default;
			MNonDatabaseGenerated=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDBGeneratedPropertiesFluentAPI(int DatabaseGeneratedOnUpdate, int NonDatabaseGenerated)
		{
			MDatabaseGeneratedOnAdd=default;
			MDatabaseGeneratedOnAddOrUpdate=default;
			MDatabaseGeneratedOnUpdate=DatabaseGeneratedOnUpdate;
			MNonDatabaseGenerated=NonDatabaseGenerated;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												DatabaseGeneratedOnAdd
		{
			get
			{
				return(MDatabaseGeneratedOnAdd);
			}
			set
			{
				MDatabaseGeneratedOnAdd=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												DatabaseGeneratedOnAddOrUpdate
		{
			get
			{
				return(MDatabaseGeneratedOnAddOrUpdate);
			}
			set
			{
				MDatabaseGeneratedOnAddOrUpdate=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												DatabaseGeneratedOnUpdate
		{
			get
			{
				return(MDatabaseGeneratedOnUpdate);
			}
			set
			{
				MDatabaseGeneratedOnUpdate=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												NonDatabaseGenerated
		{
			get
			{
				return(MNonDatabaseGenerated);
			}
			set
			{
				MNonDatabaseGenerated=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityDBGeneratedPropertiesFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityDBGeneratedPropertiesFluentAPI			Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY DB GENERATED PROPERTIES FLUENT API [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY DB GENERATED PROPERTIES FLUENT API:");
			}

			SB.AppendLine($"\tDATABASE GENERATED ON ADD [{MDatabaseGeneratedOnAdd}] !");
			SB.AppendLine($"\tDATABASE GENERATED ON ADD OR UPDATE [{MDatabaseGeneratedOnAddOrUpdate}] !");
			SB.AppendLine($"\tDATABASE GENERATED ON UPDATE [{MDatabaseGeneratedOnUpdate}] !");
			SB.AppendLine($"\tNON DATABASE GENERATED [{MNonDatabaseGenerated}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------