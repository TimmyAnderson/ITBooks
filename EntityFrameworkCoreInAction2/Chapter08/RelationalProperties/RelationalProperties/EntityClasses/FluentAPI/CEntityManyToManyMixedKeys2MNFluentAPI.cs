using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje LINK ENTITY RELATIONSHIP M:N.
	public sealed class CEntityManyToManyMixedKeys2MNFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! 1. cast COMPOSITE PRIMARY KEY.
		// !!! FOREIGN KEY do ENTITY M.
		private int												MEntityMID;
		// !!! 2. cast COMPOSITE PRIMARY KEY.
		// !!! FOREIGN KEY do ENTITY N.
		private int												MEntityNID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityMNValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY na ENTITY M.
		private CEntityManyToManyMixedKeys2MFluentAPI			MEntityM;
		// !!! NAVIGATION PROPERTY na ENTITY N.
		private CEntityManyToManyMixedKeys2NFluentAPI			MEntityN;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityManyToManyMixedKeys2MNFluentAPI()
		{
			MEntityMID=default;
			MEntityNID=default;
			MEntityMNValue=default;
			MEntityM=default;
			MEntityN=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityManyToManyMixedKeys2MNFluentAPI(string EntityMNValue)
		{
			MEntityMID=default;
			MEntityNID=default;
			MEntityMNValue=EntityMNValue;
			MEntityM=default;
			MEntityN=default;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityMID
		{
			get
			{
				return(MEntityMID);
			}
			set
			{
				MEntityMID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityNID
		{
			get
			{
				return(MEntityNID);
			}
			set
			{
				MEntityNID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityMNValue
		{
			get
			{
				return(MEntityMNValue);
			}
			set
			{
				MEntityMNValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityManyToManyMixedKeys2MFluentAPI			EntityM
		{
			get
			{
				return(MEntityM);
			}
			set
			{
				MEntityM=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityManyToManyMixedKeys2NFluentAPI			EntityN
		{
			get
			{
				return(MEntityN);
			}
			set
			{
				MEntityN=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityManyToManyMixedKeys2MNFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityManyToManyMixedKeys2MNFluentAPI			EntityM=Entities[Index];
				string											EntityMText=EntityM.Print(Index+1);
							
				if (Index>0)
				{
					CConsoleHelpers.WriteLineSeparator();
				}

				CConsoleHelpers.Write(EntityMText,ConsoleColor.Green);
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
				SB.AppendLine($"ENTITY MN MIXED KEYS FLUENT API 2 [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY MN MIXED KEYS FLUENT API 2:");
			}

			SB.AppendLine($"\tENTITY M ID [{MEntityMID}] !");
			SB.AppendLine($"\tENTITY N ID [{MEntityNID}] !");
			SB.AppendLine($"\tENTITY MN VALUE [{MEntityMNValue}] !");

			if (MEntityM!=null)
			{
				SB.AppendLine($"\tENTITY M:");

				SB.AppendLine($"\t\tENTITY M ID [{MEntityM.EntityMID}] !");
				SB.AppendLine($"\t\tENTITY M VALUE [{MEntityM.EntityMValue}] !");
			}
			else
			{
				SB.AppendLine($"\t--- ENTITY M is NULL ! ---");
			}

			if (MEntityN!=null)
			{
				SB.AppendLine($"\tENTITY N:");

				SB.AppendLine($"\t\tENTITY N ID [{MEntityN.EntityNID}] !");
				SB.AppendLine($"\t\tENTITY N VALUE [{MEntityN.EntityNValue}] !");
			}
			else
			{
				SB.AppendLine($"\t--- ENTITY N is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------