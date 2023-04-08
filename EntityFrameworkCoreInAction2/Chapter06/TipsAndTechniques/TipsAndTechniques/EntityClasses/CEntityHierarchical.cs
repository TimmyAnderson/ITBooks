using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace TipsAndTechniques
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje HIERARCHICAL ENTITY, ktora referuje sama na seba.
	public sealed class CEntityHierarchical
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityPrincipalValue;
		private int												MLevel;
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! FOREIGN KEY PROPERTY na UPPER LEVEL.
		// !!!!! FOREIGN KEY PROPERTY MUSI byt NULLABLE, lebo navyssi LEVEL NEMA ziadnu PRINCIPAL ENTITY.
		private int?											MForeignKeyID;
		// !!!! NAVIGATION PROPERTY na UPPER LEVEL.
		private CEntityHierarchical								MEntityPrincipal;
		// !!!! NAVIGATION PROPERTY na LOWER LEVEL.
		private ICollection<CEntityHierarchical>				MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityHierarchical()
		{
			MEntityPrincipalID=default(int);
			MEntityPrincipalValue=default(string);
			MLevel=default(int);
			MForeignKeyID=default(int?);
			MEntityPrincipal=default(CEntityHierarchical);
			MEntitiesDependent=default(ICollection<CEntityHierarchical>);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityHierarchical(string EntityPrincipalValue, int Level, ICollection<CEntityHierarchical> EntitiesDependent)
		{
			MEntityPrincipalID=default(int);
			MEntityPrincipalValue=EntityPrincipalValue;
			MLevel=Level;
			MForeignKeyID=default(int?);
			MEntityPrincipal=default(CEntityHierarchical);
			MEntitiesDependent=EntitiesDependent;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityPrincipalID
		{
			get
			{
				return(MEntityPrincipalID);
			}
			set
			{
				MEntityPrincipalID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityPrincipalValue
		{
			get
			{
				return(MEntityPrincipalValue);
			}
			set
			{
				MEntityPrincipalValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												Level
		{
			get
			{
				return(MLevel);
			}
			set
			{
				MLevel=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int?												ForeignKeyID
		{
			get
			{
				return(MForeignKeyID);
			}
			set
			{
				MForeignKeyID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityHierarchical								EntityPrincipal
		{
			get
			{
				return(MEntityPrincipal);
			}
			set
			{
				MEntityPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ICollection<CEntityHierarchical>					EntitiesDependent
		{
			get
			{
				return(MEntitiesDependent);
			}
			set
			{
				MEntitiesDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityHierarchical[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityHierarchical								Entity=Entities[Index];
				string											EntityText=Entity.Print(Index+1);
							
				if (Index>0)
				{
					CConsoleHelpers.WriteLineSeparator();
				}

				CConsoleHelpers.Write(EntityText,ConsoleColor.Green);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private string Print(int? Index, int Level)
		{
			string												Tabs=new string('\t',2*(Level-1));
			StringBuilder										SB=new StringBuilder();

			if (Index!=null)
			{
				SB.AppendLine($"{Tabs}ENTITY HIERARCHICAL - LEVEL [{Level}] - [{Index}]:");
			}
			else
			{
				SB.AppendLine($"{Tabs}ENTITY HIERARCHICAL - LEVEL [{Level}]:");
			}

			SB.AppendLine($"{Tabs}\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");
			SB.AppendLine($"{Tabs}\tENTITY PRINCIPAL VALUE [{MEntityPrincipalValue}] !");
			SB.AppendLine($"{Tabs}\tLEVEL [{MLevel}] !");
			SB.AppendLine($"{Tabs}\tFOREIGN KEY ID [{MForeignKeyID}] !");

			if (MEntitiesDependent!=null)
			{
				SB.AppendLine($"{Tabs}\tENTITIES HIERARCHICAL:");

				int												EntityHierarchicalIndex=1;

				foreach(CEntityHierarchical EntityDependent in MEntitiesDependent)
				{
					string										EntityText=EntityDependent.Print(EntityHierarchicalIndex,Level+1);

					SB.Append(EntityText);

					EntityHierarchicalIndex++;
				}
			}
			else
			{
				SB.AppendLine($"{Tabs}\t--- ENTITIES DEPENDENT is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string Print(int? Index)
		{
			StringBuilder										SB=new StringBuilder();

			string												EntityText=Print(Index,1);

			SB.Append(EntityText);

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------