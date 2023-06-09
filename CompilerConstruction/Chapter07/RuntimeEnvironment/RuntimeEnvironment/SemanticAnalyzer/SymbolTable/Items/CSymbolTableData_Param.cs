﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSymbolTableData_Param : CSymbolTableData_Variable
	{
//-------------------------------------------------------------------------------------------------------
		public CSymbolTableData_Param(string SymbolName, ESymbolType SymbolType)
			: base(SymbolName,SymbolType)
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override int GetSizeof()
		{
			return(SymbolType.EXT_GetSizeof(EVariableType.E_VT_FUNCTION_PARAMETER));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------