using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// DERIVED CLASS v TABLE PER HIERARCHY.
	public sealed class CEntityTablePerHierarchyDerived2Conventions : CEntityTablePerHierarchyBaseConventions
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MDerivedValue2;
		private string											MDerivedValueWithSameName;
		private string											MDerivedValueInSharedColumn;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityTablePerHierarchyDerived2Conventions()
			: base()
		{
			MDerivedValue2=default;
			MDerivedValueWithSameName=default;
			MDerivedValueInSharedColumn=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityTablePerHierarchyDerived2Conventions(string BaseValue, string DerivedValue2, string DerivedValueWithSameName, string DerivedValueInSharedColumn)
			: base(BaseValue)
		{
			MDerivedValue2=DerivedValue2;
			MDerivedValueWithSameName=DerivedValueWithSameName;
			MDerivedValueInSharedColumn=DerivedValueInSharedColumn;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											DerivedValue2
		{
			get
			{
				return(MDerivedValue2);
			}
			set
			{
				MDerivedValue2=value;
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
		public static void PrintToConsole(CEntityTablePerHierarchyDerived2Conventions[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityTablePerHierarchyDerived2Conventions		Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY TABLE PER HIERARCHY DERIVED 2 CONVENTIONS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY TABLE PER HIERARCHY DERIVED 2 CONVENTIONS:");
			}

			SB.AppendLine($"\tENTITY ID [{EntityID}] !");
			SB.AppendLine($"\tBASE VALUE [{BaseValue}] !");
			SB.AppendLine($"\tDERIVED VALUE 2 [{MDerivedValue2}] !");
			SB.AppendLine($"\tDERIVED VALUE WITH SAME NAME [{MDerivedValueWithSameName}] !");
			SB.AppendLine($"\tDERIVED VALUE SHARED COLUMN [{MDerivedValueInSharedColumn}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------