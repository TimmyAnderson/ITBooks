﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public class CSymbolTableData_Variable : CSymbolTableData
	{
//-------------------------------------------------------------------------------------------------------
		public readonly static int								INT_SIZE=4;
		public readonly static int								POINTER_SIZE=4;
//-------------------------------------------------------------------------------------------------------
		private readonly bool									MIsGlobalVariable;
//-------------------------------------------------------------------------------------------------------
		private object											MConstValue;
		private bool											MIsECXRegisterOccupied;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTableData_Variable(string SymbolName, ESymbolType SymbolType, bool IsGlobalVariable)
			: base(SymbolName,SymbolType)
		{
			MIsGlobalVariable=IsGlobalVariable;
			MIsECXRegisterOccupied=false;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public bool												IsGlobalVariable
		{
			get
			{
				return(MIsGlobalVariable);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public object											ConstValue
		{
			get
			{
				return(MConstValue);
			}
			set
			{
				MConstValue=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												IsECXRegisterOccupied
		{
			get
			{
				return(MIsECXRegisterOccupied);
			}
			set
			{
				MIsECXRegisterOccupied=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override int GetSizeof()
		{
			return(SymbolType.EXT_GetSizeof(EVariableType.E_VT_VALUE));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------