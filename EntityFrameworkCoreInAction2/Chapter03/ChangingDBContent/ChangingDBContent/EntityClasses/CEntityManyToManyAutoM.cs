using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace ChangingDBContent
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje LEFT SIDE RELATIONSHIP M:N.
	public sealed class CEntityManyToManyAutoM
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityMID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityMValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY na ENTITY N.
		private ICollection<CEntityManyToManyAutoN>				MEntitiesN;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityManyToManyAutoM()
		{
			MEntityMID=default(int);
			MEntityMValue=default(string);
			MEntitiesN=default(ICollection<CEntityManyToManyAutoN>);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityManyToManyAutoM(string EntityMValue)
		{
			MEntityMID=default(int);
			MEntityMValue=EntityMValue;
			MEntitiesN=new List<CEntityManyToManyAutoN>();
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
		public ICollection<CEntityManyToManyAutoN>				EntitiesN
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityManyToManyAutoM[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityManyToManyAutoM							EntityM=Entities[Index];
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
				SB.AppendLine($"ENTITY M [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY M:");
			}

			SB.AppendLine($"\tENTITY M ID [{MEntityMID}] !");
			SB.AppendLine($"\tENTITY M VALUE [{MEntityMValue}] !");

			if (MEntitiesN!=null)
			{
				SB.AppendLine($"\tENTITIES N:");

				int												EntityNIndex=1;

				foreach(CEntityManyToManyAutoN EntityN in MEntitiesN)
				{
					SB.AppendLine($"\t\tENTITY N [{EntityNIndex}]:");

					SB.AppendLine($"\t\t\tENTITY N ID [{EntityN.EntityNID}] !");
					SB.AppendLine($"\t\t\tENTITY N VALUE [{EntityN.EntityNValue}] !");


					EntityNIndex++;
				}
			}
			else
			{
				SB.AppendLine($"\t--- ENTITIES N is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------