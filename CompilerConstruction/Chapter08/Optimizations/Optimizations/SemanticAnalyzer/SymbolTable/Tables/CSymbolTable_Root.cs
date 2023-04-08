﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSymbolTable_Root : CSymbolTable
	{
//-------------------------------------------------------------------------------------------------------
		public CSymbolTable_Root(CSymbolTable ParentScopeTable, int ChildScopeIndexInParentTable)
			: base(ParentScopeTable,ChildScopeIndexInParentTable,0)
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("[ROOT]"));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------