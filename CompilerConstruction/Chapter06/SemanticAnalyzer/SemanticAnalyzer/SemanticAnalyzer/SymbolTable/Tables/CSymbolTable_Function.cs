using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSymbolTable_Function : CSymbolTable
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MFunctionName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTable_Function(CSymbolTable ParentScopeTable, int ChildScopeIndexInParentTable, string FunctionName)
			: base(ParentScopeTable,ChildScopeIndexInParentTable)
		{
			MFunctionName=FunctionName;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											FunctionName
		{
			get
			{
				return(MFunctionName);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTableItem_Param[] GetParamTypes()
		{
			CSymbolTableItem_Param[]			ParamSymbolItems=SymbolItems.OfType<CSymbolTableItem_Param>().ToArray();
			
			return(ParamSymbolItems);
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbolTableItem_Function GetReturnValueType()
		{
			CSymbolTableItem_Function				FunctionSymbolItem=ParentScopeTable.SymbolItems.OfType<CSymbolTableItem_Function>().FirstOrDefault();
			
			if (FunctionSymbolItem!=null)
			{
				return(FunctionSymbolItem);
			}
			else
			{
				throw(new InvalidOperationException(string.Format("Can't find FUNCTION SYMBOL ITEM !")));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("[{0}]",MFunctionName));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------