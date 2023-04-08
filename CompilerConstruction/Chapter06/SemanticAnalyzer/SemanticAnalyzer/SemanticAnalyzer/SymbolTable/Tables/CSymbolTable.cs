using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public abstract class CSymbolTable
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CSymbolTableItem>					MSymbolItems;
		private readonly CSymbolTable							MParentScopeTable;
		private readonly int									MChildScopeIndexInParentTable;
		private readonly List<CSymbolTable>						MChildScopeTables;
//-------------------------------------------------------------------------------------------------------
		private int												MChildScopeTableIndex;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTable(CSymbolTable ParentScopeTable, int ChildScopeIndexInParentTable)
		{
			MParentScopeTable=ParentScopeTable;
			MChildScopeIndexInParentTable=ChildScopeIndexInParentTable;

			MSymbolItems=new List<CSymbolTableItem>();
			MChildScopeTables=new List<CSymbolTable>();
			MChildScopeTableIndex=0;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTableItem[]								SymbolItems
		{
			get
			{
				return(MSymbolItems.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbolTable										ParentScopeTable
		{
			get
			{
				return(MParentScopeTable);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int												ChildScopeIndexInParentTable
		{
			get
			{
				return(MChildScopeIndexInParentTable);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbolTable[]									ChildScopeTables
		{
			get
			{
				return(MChildScopeTables.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddSymbol(CSymbolTableItem Item)
		{
			MSymbolItems.Add(Item);
		}
//-------------------------------------------------------------------------------------------------------
		public void AddChildScopeTables(CSymbolTable ChildScopeTable)
		{
			MChildScopeTables.Add(ChildScopeTable);
		}
//-------------------------------------------------------------------------------------------------------
		public void ResetChildScopeTableIndex()
		{
			MChildScopeTableIndex=0;

			foreach(CSymbolTable SymbolTable in MChildScopeTables)
			{
				SymbolTable.ResetChildScopeTableIndex();
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbolTable MoveToNextChildScopeTableIndex()
		{
			CSymbolTable					ChildScopeTable=MChildScopeTables[MChildScopeTableIndex++];

			return(ChildScopeTable);
		}
//-------------------------------------------------------------------------------------------------------
		public bool ContainsSymbolInCurrentScope(string SymbolName)
		{
			CSymbolTableItem				ExistingTableItem=MSymbolItems.Where(P => P.SymbolName==SymbolName).FirstOrDefault();

			if (ExistingTableItem!=null)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool ContainsSymbolInCurrentOrParentScopes(string SymbolName)
		{
			CSymbolTableItem				ExistingTableItem=MSymbolItems.Where(P => P.SymbolName==SymbolName).FirstOrDefault();

			if (ExistingTableItem!=null)
			{
				return(true);
			}
			else
			{
				if (MParentScopeTable!=null)
				{
					return(MParentScopeTable.ContainsSymbolInCurrentOrParentScopes(SymbolName));
				}
				else
				{
					return(false);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool ContainsFunctionInCurrentOrParentScopes(string SymbolName)
		{
			CSymbolTableItem_Function		ExistingTableItem=MSymbolItems.OfType<CSymbolTableItem_Function>().Where(P => P.SymbolName==SymbolName).FirstOrDefault();

			if (ExistingTableItem!=null)
			{
				return(true);
			}
			else
			{
				if (MParentScopeTable!=null)
				{
					return(MParentScopeTable.ContainsFunctionInCurrentOrParentScopes(SymbolName));
				}
				else
				{
					return(false);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbolTableItem GetSymbolFromCurrentOrParentScopes(string SymbolName)
		{
			CSymbolTableItem				ExistingTableItem=MSymbolItems.Where(P => P.SymbolName==SymbolName).FirstOrDefault();

			if (ExistingTableItem!=null)
			{
				return(ExistingTableItem);
			}
			else
			{
				if (MParentScopeTable!=null)
				{
					return(MParentScopeTable.GetSymbolFromCurrentOrParentScopes(SymbolName));
				}
				else
				{
					return(null);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbolTable_Function GetFunctionSymbolTable(string FunctionName)
		{
			CSymbolTable_Function			FunctionTable=MChildScopeTables.OfType<CSymbolTable_Function>().Where(P => P.FunctionName==FunctionName).FirstOrDefault();

			if (FunctionTable!=null)
			{
				return(FunctionTable);
			}
			else
			{
				if (MParentScopeTable!=null)
				{
					return(MParentScopeTable.GetFunctionSymbolTable(FunctionName));
				}
				else
				{
					return(null);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void TraverseSymbolTableTree(Action<CSymbolTable> Action)
		{
			Action(this);

			foreach(CSymbolTable ChildTable in MChildScopeTables)
			{
				ChildTable.TraverseSymbolTableTree(Action);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------