using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSymbolTable_Block : CSymbolTable
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MFunctionName;
		private readonly int									MScopeLevelInFunction;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTable_Block(CSymbolTable ParentScopeTable, int ChildScopeIndexInParentTable, string FunctionName, int ScopeLevelInFunction)
			: base(ParentScopeTable,ChildScopeIndexInParentTable,(ParentScopeTable.BaseStackOffset+ParentScopeTable.SymbolItemsStackSize))
		{
			MFunctionName=FunctionName;
			MScopeLevelInFunction=ScopeLevelInFunction;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("[{0}] - SCOPE LEVEL: [{1}]",MFunctionName,MScopeLevelInFunction));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------