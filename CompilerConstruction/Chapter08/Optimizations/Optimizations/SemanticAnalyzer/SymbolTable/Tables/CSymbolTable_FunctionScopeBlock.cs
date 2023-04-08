using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSymbolTable_FunctionScopeBlock : CSymbolTable_Block
	{
//-------------------------------------------------------------------------------------------------------
		public CSymbolTable_FunctionScopeBlock(CSymbolTable ParentScopeTable, int ChildScopeIndexInParentTable, string FunctionName, int ScopeLevelInFunction)
			: base(ParentScopeTable,ChildScopeIndexInParentTable,0,FunctionName,ScopeLevelInFunction)
		{
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------