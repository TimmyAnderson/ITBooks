﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public abstract class CSymbolTable_Block : CSymbolTable
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MFunctionName;
		private readonly int									MScopeLevelInFunction;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTable_Block(CSymbolTable ParentScopeTable, int ChildScopeIndexInParentTable, int BaseStackOffset, string FunctionName, int ScopeLevelInFunction)
			: base(ParentScopeTable,ChildScopeIndexInParentTable,BaseStackOffset)
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