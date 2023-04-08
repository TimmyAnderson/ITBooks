using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje RIGHT SIDE RELATIONSHIP M:N.
	public sealed class CEntityZeroManyToMany2NFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityNID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityNValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY na ENTITY MN.
		private IList<CEntityZeroManyToMany2MNFluentAPI>		MEntitiesMN;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityZeroManyToMany2NFluentAPI()
		{
			MEntityNID=default;
			MEntityNValue=default;
			MEntitiesMN=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityZeroManyToMany2NFluentAPI(string EntityNValue)
		{
			MEntityNID=default;
			MEntityNValue=EntityNValue;
			MEntitiesMN=new List<CEntityZeroManyToMany2MNFluentAPI>();
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
		public IList<CEntityZeroManyToMany2MNFluentAPI>			EntitiesMN
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
		public static void PrintToConsole(CEntityZeroManyToMany2NFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityZeroManyToMany2NFluentAPI				EntityN=Entities[Index];
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
				SB.AppendLine($"ENTITY N FLUENT API 2 [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY N FLUENT API 2:");
			}

			SB.AppendLine($"\tENTITY N ID [{MEntityNID}] !");
			SB.AppendLine($"\tENTITY N VALUE [{MEntityNValue}] !");

			if (MEntitiesMN!=null)
			{
				SB.AppendLine($"\tENTITIES MN:");

				for(int EntityMNIndex=0;EntityMNIndex<MEntitiesMN.Count;EntityMNIndex++)
				{
					CEntityZeroManyToMany2MNFluentAPI			EntityMN=MEntitiesMN[EntityMNIndex];

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