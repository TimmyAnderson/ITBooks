using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje LEFT SIDE RELATIONSHIP M:N.
	public sealed class CEntityAutoManyToMany1MFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityMID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityMValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY priamo na ENTITY M bez LINK ENTITY.
		private IList<CEntityAutoManyToMany1NFluentAPI>			MEntitiesN;
		// !!! NAVIGATION PROPERTY na ENTITY MN.
		private IList<CEntityAutoManyToMany1MNFluentAPI>		MEntitiesMN;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityAutoManyToMany1MFluentAPI()
		{
			MEntityMID=default;
			MEntityMValue=default;
			MEntitiesN=default;
			MEntitiesMN=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityAutoManyToMany1MFluentAPI(string EntityMValue)
		{
			MEntityMID=default;
			MEntityMValue=EntityMValue;
			MEntitiesN=new List<CEntityAutoManyToMany1NFluentAPI>();
			MEntitiesMN=new List<CEntityAutoManyToMany1MNFluentAPI>();
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
		public string											EntityMValue
		{
			get
			{
				return(MEntityMValue);
			}
			set
			{
				MEntityMValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IList<CEntityAutoManyToMany1NFluentAPI>			EntitiesN
		{
			get
			{
				return(MEntitiesN);
			}
			set
			{
				MEntitiesN=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public IList<CEntityAutoManyToMany1MNFluentAPI>			EntitiesMN
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
		public static void PrintToConsole(CEntityAutoManyToMany1MFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityAutoManyToMany1MFluentAPI				EntityM=Entities[Index];
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
				SB.AppendLine($"ENTITY AUTO M FLUENT API 1 [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY AUTO M FLUENT API 1:");
			}

			SB.AppendLine($"\tENTITY M ID [{MEntityMID}] !");
			SB.AppendLine($"\tENTITY M VALUE [{MEntityMValue}] !");

			if (MEntitiesN!=null)
			{
				SB.AppendLine($"\tENTITIES N:");

				for(int EntityMNIndex=0;EntityMNIndex<MEntitiesN.Count;EntityMNIndex++)
				{
					CEntityAutoManyToMany1NFluentAPI			EntityN=MEntitiesN[EntityMNIndex];

					SB.AppendLine($"\t\tENTITY N [{(EntityMNIndex+1)}]:");

					SB.AppendLine($"\t\t\tENTITY N ID [{EntityN.EntityNID}] !");
					SB.AppendLine($"\t\t\tENTITY N VALUE [{EntityN.EntityNValue}] !");
				}
			}
			else
			{
				SB.AppendLine($"\t--- ENTITIES N is NULL ! ---");
			}

			if (MEntitiesMN!=null)
			{
				SB.AppendLine($"\tENTITIES MN:");

				for(int EntityMNIndex=0;EntityMNIndex<MEntitiesMN.Count;EntityMNIndex++)
				{
					CEntityAutoManyToMany1MNFluentAPI			EntityMN=MEntitiesMN[EntityMNIndex];

					SB.AppendLine($"\t\tENTITY MN [{(EntityMNIndex+1)}]:");

					SB.AppendLine($"\t\t\tENTITY M ID [{EntityMN.EntityMID}] !");
					SB.AppendLine($"\t\t\tENTITY N ID [{EntityMN.EntityNID}] !");
					SB.AppendLine($"\t\t\tENTITY MN VALUE [{EntityMN.EntityMNValue}] !");

					if (EntityMN.EntityN!=null)
					{
						SB.AppendLine($"\t\t\tENTITY N [{(EntityMNIndex+1)}]:");

						SB.AppendLine($"\t\t\t\tENTITY N ID [{EntityMN.EntityN.EntityNID}] !");
						SB.AppendLine($"\t\t\t\tENTITY N VALUE [{EntityMN.EntityN.EntityNValue}] !");
					}
					else
					{
						SB.AppendLine($"\t\t\t--- ENTITY N is NULL ! ---");
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