using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// DERIVED CLASS v TABLE PER HIERARCHY.
	public sealed class CEntityTablePerHierarchyDerived1Conventions : CEntityTablePerHierarchyBaseConventions
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MDerivedValue1;
		private string											MDerivedValueWithSameName;
		private string											MDerivedValueInSharedColumn;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityTablePerHierarchyDerived1Conventions()
			: base()
		{
			MDerivedValue1=default;
			MDerivedValueWithSameName=default;
			MDerivedValueInSharedColumn=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityTablePerHierarchyDerived1Conventions(string BaseValue, string DerivedValue1, string DerivedValueWithSameName, string DerivedValueInSharedColumn)
			: base(BaseValue)
		{
			MDerivedValue1=DerivedValue1;
			MDerivedValueWithSameName=DerivedValueWithSameName;
			MDerivedValueInSharedColumn=DerivedValueInSharedColumn;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											DerivedValue1
		{
			get
			{
				return(MDerivedValue1);
			}
			set
			{
				MDerivedValue1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											DerivedValueWithSameName
		{
			get
			{
				return(MDerivedValueWithSameName);
			}
			set
			{
				MDerivedValueWithSameName=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											DerivedValueInSharedColumn
		{
			get
			{
				return(MDerivedValueInSharedColumn);
			}
			set
			{
				MDerivedValueInSharedColumn=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityTablePerHierarchyDerived1Conventions[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityTablePerHierarchyDerived1Conventions		Entity=Entities[Index];
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
		public override string Print(int? Index)
		{
			StringBuilder										SB=new StringBuilder();

			if (Index!=null)
			{
				SB.AppendLine($"ENTITY TABLE PER HIERARCHY DERIVED 1 CONVENTIONS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY TABLE PER HIERARCHY DERIVED 1 CONVENTIONS:");
			}

			SB.AppendLine($"\tENTITY ID [{EntityID}] !");
			SB.AppendLine($"\tBASE VALUE [{BaseValue}] !");
			SB.AppendLine($"\tDERIVED VALUE 1 [{MDerivedValue1}] !");
			SB.AppendLine($"\tDERIVED VALUE WITH SAME NAME [{MDerivedValueWithSameName}] !");
			SB.AppendLine($"\tDERIVED VALUE SHARED COLUMN [{MDerivedValueInSharedColumn}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------