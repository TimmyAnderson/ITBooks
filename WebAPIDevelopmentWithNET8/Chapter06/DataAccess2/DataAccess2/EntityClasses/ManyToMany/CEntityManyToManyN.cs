using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess2
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje RIGHT SIDE RELATIONSHIP M:N.
	public sealed class CEntityManyToManyN
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityNID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityNValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY na ENTITY MN.
		private IList<CEntityManyToManyMN>						MEntitiesMN;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityManyToManyN()
		{
			MEntityNID=default;
			MEntityNValue=default;
			MEntitiesMN=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityManyToManyN(string EntityNValue)
		{
			MEntityNID=default;
			MEntityNValue=EntityNValue;
			MEntitiesMN=new List<CEntityManyToManyMN>();
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityManyToManyN(int EntityNID, string EntityNValue)
		{
			MEntityNID=EntityNID;
			MEntityNValue=EntityNValue;
			MEntitiesMN=new List<CEntityManyToManyMN>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
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
		public string											EntityNValue
		{
			get
			{
				return(MEntityNValue);
			}
			set
			{
				MEntityNValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IList<CEntityManyToManyMN>						EntitiesMN
		{
			get
			{
				return(MEntitiesMN);
			}
			set
			{
				MEntitiesMN=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityManyToManyN[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityManyToManyN								Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY N [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY N:");
			}

			SB.AppendLine($"\tENTITY N ID [{MEntityNID}] !");
			SB.AppendLine($"\tENTITY N VALUE [{MEntityNValue}] !");

			if (MEntitiesMN!=null)
			{
				SB.AppendLine($"\tENTITIES MN:");

				for(int EntityMNIndex=0;EntityMNIndex<MEntitiesMN.Count;EntityMNIndex++)
				{
					CEntityManyToManyMN							EntityMN=MEntitiesMN[EntityMNIndex];

					SB.AppendLine($"\t\tENTITY MN [{(EntityMNIndex+1)}]:");

					SB.AppendLine($"\t\t\tENTITY M ID [{EntityMN.EntityMID}] !");
					SB.AppendLine($"\t\t\tENTITY N ID [{EntityMN.EntityNID}] !");
					SB.AppendLine($"\t\t\tENTITY MN VALUE [{EntityMN.EntityMNValue}] !");

					if (EntityMN.EntityM!=null)
					{
						SB.AppendLine($"\t\t\tENTITY M [{(EntityMNIndex+1)}]:");

						SB.AppendLine($"\t\t\t\tENTITY M ID [{EntityMN.EntityM.EntityMID}] !");
						SB.AppendLine($"\t\t\t\tENTITY M VALUE [{EntityMN.EntityM.EntityMValue}] !");
					}
					else
					{
						SB.AppendLine($"\t\t\t--- ENTITY M is NULL ! ---");
					}
				}
			}
			else
			{
				SB.AppendLine($"\t--- ENTITIES MN is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------