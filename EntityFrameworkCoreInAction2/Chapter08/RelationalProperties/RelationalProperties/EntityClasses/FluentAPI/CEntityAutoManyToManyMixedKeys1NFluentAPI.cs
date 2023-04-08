using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje RIGHT SIDE RELATIONSHIP M:N.
	public sealed class CEntityAutoManyToManyMixedKeys1NFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityNID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityNValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY priamo na ENTITY M bez LINK ENTITY.
		private IList<CEntityAutoManyToManyMixedKeys1MFluentAPI>	MEntitiesM;
		// !!! NAVIGATION PROPERTY na ENTITY MN.
		private IList<CEntityAutoManyToManyMixedKeys1MNFluentAPI>	MEntitiesMN;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityAutoManyToManyMixedKeys1NFluentAPI()
		{
			MEntityNID=default;
			MEntityNValue=default;
			MEntitiesM=default;
			MEntitiesMN=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityAutoManyToManyMixedKeys1NFluentAPI(string EntityNValue)
		{
			MEntityNID=default;
			MEntityNValue=EntityNValue;
			MEntitiesM=new List<CEntityAutoManyToManyMixedKeys1MFluentAPI>();
			MEntitiesMN=new List<CEntityAutoManyToManyMixedKeys1MNFluentAPI>();
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
		public IList<CEntityAutoManyToManyMixedKeys1MFluentAPI>	EntitiesM
		{
			get
			{
				return(MEntitiesM);
			}
			set
			{
				MEntitiesM=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public IList<CEntityAutoManyToManyMixedKeys1MNFluentAPI>			EntitiesMN
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
		public static void PrintToConsole(CEntityAutoManyToManyMixedKeys1NFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityAutoManyToManyMixedKeys1NFluentAPI		EntityN=Entities[Index];
				string											EntityNText=EntityN.Print(Index+1);
							
				if (Index>0)
				{
					CConsoleHelpers.WriteLineSeparator();
				}

				CConsoleHelpers.Write(EntityNText,ConsoleColor.Green);
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
				SB.AppendLine($"ENTITY AUTO N MIXED KEYS FLUENT API 1 [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY AUTO N MIXED KEYS FLUENT API 1:");
			}

			SB.AppendLine($"\tENTITY N ID [{MEntityNID}] !");
			SB.AppendLine($"\tENTITY N VALUE [{MEntityNValue}] !");

			if (MEntitiesM!=null)
			{
				SB.AppendLine($"\tENTITIES M:");

				for(int EntityMNIndex=0;EntityMNIndex<MEntitiesM.Count;EntityMNIndex++)
				{
					CEntityAutoManyToManyMixedKeys1MFluentAPI	EntityM=MEntitiesM[EntityMNIndex];

					SB.AppendLine($"\t\tENTITY M [{(EntityMNIndex+1)}]:");

					SB.AppendLine($"\t\t\tENTITY M ID [{EntityM.EntityMID}] !");
					SB.AppendLine($"\t\t\tENTITY M VALUE [{EntityM.EntityMValue}] !");
				}
			}
			else
			{
				SB.AppendLine($"\t--- ENTITIES M is NULL ! ---");
			}

			if (MEntitiesMN!=null)
			{
				SB.AppendLine($"\tENTITIES MN:");

				for(int EntityMNIndex=0;EntityMNIndex<MEntitiesMN.Count;EntityMNIndex++)
				{
					CEntityAutoManyToManyMixedKeys1MNFluentAPI	EntityMN=MEntitiesMN[EntityMNIndex];

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