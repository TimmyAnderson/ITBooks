using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// DERIVED CLASS v TABLE PER HIERARCHY.
	public sealed class CEntityTablePerHierarchyDerived2FluentAPI : CEntityTablePerHierarchyBaseFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MDerivedValue2;
		private string											MDerivedValueWithSameName;
		private string											MDerivedValueInSharedColumn;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityTablePerHierarchyDerived2FluentAPI()
			: base()
		{
			MDerivedValue2=default;
			MDerivedValueWithSameName=default;
			MDerivedValueInSharedColumn=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityTablePerHierarchyDerived2FluentAPI(string BaseValue, string DerivedValue2, string DerivedValueWithSameName, string DerivedValueInSharedColumn)
			: base(EDiscriminatorFluentAPI.E_DERIVED_2,BaseValue)
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
		public static void PrintToConsole(CEntityTablePerHierarchyDerived2FluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityTablePerHierarchyDerived2FluentAPI		Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY TABLE PER HIERARCHY DERIVED 2 FLUENT API [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY TABLE PER HIERARCHY DERIVED 2 FLUENT API:");
			}

			SB.AppendLine($"\tENTITY ID [{EntityID}] !");
			SB.AppendLine($"\tDISCRIMINATOR [{Discriminator}] !");
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