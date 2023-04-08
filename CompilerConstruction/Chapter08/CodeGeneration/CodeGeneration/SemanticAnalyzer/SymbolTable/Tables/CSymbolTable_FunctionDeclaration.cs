using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSymbolTable_FunctionDeclaration : CSymbolTable
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MFunctionName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTable_FunctionDeclaration(CSymbolTable ParentScopeTable, int ChildScopeIndexInParentTable, string FunctionName)
			: base(ParentScopeTable,ChildScopeIndexInParentTable,0)
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
		public CSymbolTableData_Param[] GetParamTypes()
		{
			CSymbolTableData_Param[]			ParamSymbolItems=SymbolItems.Select(P => P.SymbolTableData).OfType<CSymbolTableData_Param>().ToArray();
			
			return(ParamSymbolItems);
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbolTableData_Function GetReturnValueType()
		{
			CSymbolTableData_Function				FunctionSymbolItem=ParentScopeTable.SymbolItems.Select(P => P.SymbolTableData).OfType<CSymbolTableData_Function>().FirstOrDefault();
			
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