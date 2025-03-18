using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess2
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje LINK ENTITY RELATIONSHIP M:N.
	public sealed class CEntityManyToManyMN
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
		private CEntityManyToManyM								MEntityM;
		// !!! NAVIGATION PROPERTY na ENTITY N.
		private CEntityManyToManyN								MEntityN;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityManyToManyMN()
		{
			MEntityMNID=default;
			MEntityMNValue=default;
			MEntityMID=default;
			MEntityNID=default;
			MEntityM=default;
			MEntityN=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityManyToManyMN(string EntityMNValue)
		{
			MEntityMNID=default;
			MEntityMNValue=EntityMNValue;
			MEntityMID=default;
			MEntityNID=default;
			MEntityM=default;
			MEntityN=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityManyToManyMN(int EntityMNID, string EntityMNValue, int EntityMID, int EntityNID)
		{
			MEntityMNID=EntityMNID;
			MEntityMNValue=EntityMNValue;
			MEntityMID=EntityMID;
			MEntityNID=EntityNID;
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
		public CEntityManyToManyM								EntityM
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
		public CEntityManyToManyN								EntityN
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
		public static void PrintToConsole(CEntityManyToManyMN[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityManyToManyMN								Entity=Entities[Index];
				string											EntityText=Entity.Print(Index+1);
							
				if (Index>0)
				{
					Console.WriteLine(new string('-',80));
				}

				Console.Write(EntityText);
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
				SB.AppendLine($"ENTITY MN [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY MN:");
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