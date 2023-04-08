using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedFeaturesAndConcurrency
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityDBGeneratedPropertiesDataAnnotations
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MDatabaseGeneratedIdentity;
		private int												MDatabaseGeneratedComputed;
		private int												MNonDatabaseGenerated;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDBGeneratedPropertiesDataAnnotations()
		{
			MDatabaseGeneratedIdentity=default;
			MDatabaseGeneratedComputed=default;
			MNonDatabaseGenerated=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDBGeneratedPropertiesDataAnnotations(int NonDatabaseGenerated)
		{
			MDatabaseGeneratedIdentity=default;
			MDatabaseGeneratedComputed=default;
			MNonDatabaseGenerated=NonDatabaseGenerated;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY reprezentuje IDENTITY PROPERTY.
		// !!! PROPERTY je PRIMARY KEY.
		[DatabaseGenerated(DatabaseGeneratedOption.Identity)]
		public int												DatabaseGeneratedIdentity
		{
			get
			{
				return(MDatabaseGeneratedIdentity);
			}
			set
			{
				MDatabaseGeneratedIdentity=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY reprezentuje COMPUTED PROPERTY.
		[DatabaseGenerated(DatabaseGeneratedOption.Computed)]
		public int												DatabaseGeneratedComputed
		{
			get
			{
				return(MDatabaseGeneratedComputed);
			}
			set
			{
				MDatabaseGeneratedComputed=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY reprezentuje PROPERTY, ktora NIE JE generovana v DATABASE.
		[DatabaseGenerated(DatabaseGeneratedOption.None)]
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
		public static void PrintToConsole(CEntityDBGeneratedPropertiesDataAnnotations[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityDBGeneratedPropertiesDataAnnotations		Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY DB GENERATED PROPERTIES DATA ANNOTATIONS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY DB GENERATED PROPERTIES DATA ANNOTATIONS:");
			}

			SB.AppendLine($"\tDATABASE GENERATED IDENTITY [{MDatabaseGeneratedIdentity}] !");
			SB.AppendLine($"\tDATABASE GENERATED COMPUTED [{MDatabaseGeneratedComputed}] !");
			SB.AppendLine($"\tNON DATABASE GENERATED [{MNonDatabaseGenerated}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------