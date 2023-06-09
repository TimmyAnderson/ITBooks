﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSymbolTableData_Function : CSymbolTableData
	{
//-------------------------------------------------------------------------------------------------------
		private readonly ESymbolType							MFunctionReturnType;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTableData_Function(string SymbolName, ESymbolType SymbolType, ESymbolType FunctionReturnType)
			: base(SymbolName,SymbolType)
		{
			MFunctionReturnType=FunctionReturnType;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public ESymbolType										FunctionReturnType
		{
			get
			{
				return(MFunctionReturnType);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override int GetSizeof()
		{
			return(0);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------