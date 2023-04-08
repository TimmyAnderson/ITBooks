using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedFeaturesAndConcurrency
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityMultipleConcurrencyTokensFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityID;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityValue1;
		private int												MEntityValue2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityMultipleConcurrencyTokensFluentAPI()
		{
			MEntityID=default;
			MEntityValue1=default;
			MEntityValue2=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityMultipleConcurrencyTokensFluentAPI(int EntityValue1, int EntityValue2)
		{
			MEntityID=default;
			MEntityValue1=EntityValue1;
			MEntityValue2=EntityValue2;
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
		// !!! PROPERTY je pomocou FLUENT API oznacena ako CONCURRENCY TOKEN PROPERTY.
		public int												EntityValue1
		{
			get
			{
				return(MEntityValue1);
			}
			set
			{
				MEntityValue1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY je pomocou FLUENT API oznacena ako CONCURRENCY TOKEN PROPERTY.
		public int												EntityValue2
		{
			get
			{
				return(MEntityValue2);
			}
			set
			{
				MEntityValue2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityMultipleConcurrencyTokensFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityMultipleConcurrencyTokensFluentAPI		Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY MUTLIPLE CONCURRENCY TOKENS FLUENT API [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY MUTLIPLE CONCURRENCY TOKENS FLUENT API:");
			}

			SB.AppendLine($"\tENTITY ID [{MEntityID}] !");
			SB.AppendLine($"\tENTITY VALUE 1 [{MEntityValue1}] !");
			SB.AppendLine($"\tENTITY VALUE 2 [{MEntityValue2}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------