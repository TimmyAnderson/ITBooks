using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSymbolTable_SubScopeBlock : CSymbolTable_Block
	{
//-------------------------------------------------------------------------------------------------------
		public CSymbolTable_SubScopeBlock(CSymbolTable ParentScopeTable, int ChildScopeIndexInParentTable, string FunctionName, int ScopeLevelInFunction)
			: base(ParentScopeTable,ChildScopeIndexInParentTable,(ParentScopeTable.BaseStackOffset-ParentScopeTable.SymbolItemsStackSize),FunctionName,ScopeLevelInFunction)
		{
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------