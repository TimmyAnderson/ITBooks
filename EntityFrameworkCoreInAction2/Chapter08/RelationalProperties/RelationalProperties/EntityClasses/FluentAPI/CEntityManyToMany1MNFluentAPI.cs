﻿using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje LINK ENTITY RELATIONSHIP M:N.
	public sealed class CEntityManyToMany1MNFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! PRIMARY KEY.
		private int												MEntityMNID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityMNValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! 1. cast COMPOSITE FOREIGN KEY.
		// !!! FOREIGN KEY do ENTITY M.
		private int												MEntityMID;
		// !!! 2. cast COMPOSITE FOREIGN KEY.
		// !!! FOREIGN KEY do ENTITY N.
		private int												MEntityNID;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY na ENTITY M.
		private CEntityManyToMany1MFluentAPI					MEntityM;
		// !!! NAVIGATION PROPERTY na ENTITY N.
		private CEntityManyToMany1NFluentAPI					MEntityN;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityManyToMany1MNFluentAPI()
		{
			MEntityMNID=default;
			MEntityMNValue=default;
			MEntityMID=default;
			MEntityNID=default;
			MEntityM=default;
			MEntityN=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityManyToMany1MNFluentAPI(string EntityMNValue)
		{
			MEntityMNID=default;
			MEntityMNValue=EntityMNValue;
			MEntityMID=default;
			MEntityNID=default;
			MEntityM=default;
			MEntityN=default;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityMNID
		{
			get
			{
				return(MEntityMNID);
			}
			set
			{
				MEntityMNID=value;
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
		public CEntityManyToMany1MFluentAPI						EntityM
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
		public CEntityManyToMany1NFluentAPI						EntityN
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
		public static void PrintToConsole(CEntityManyToMany1MNFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityManyToMany1MNFluentAPI					Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY MN FLUENT API 1 [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY MN FLUENT API 1:");
			}

			SB.AppendLine($"\tENTITY MN ID [{MEntityMNID}] !");
			SB.AppendLine($"\tENTITY MN VALUE [{MEntityMNValue}] !");
			SB.AppendLine($"\tENTITY M ID [{MEntityMID}] !");
			SB.AppendLine($"\tENTITY N ID [{MEntityNID}] !");

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