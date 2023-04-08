using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public abstract class CSymbolTable
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CSymbolTableItem>					MSymbolItems;
		private readonly CSymbolTable							MParentScopeTable;
		private readonly int									MChildScopeIndexInParentTable;
		private readonly List<CSymbolTable>						MChildScopeTables;
		private readonly int									MSymbolTableLevel;
		private readonly int									MBaseStackOffset;
//-------------------------------------------------------------------------------------------------------
		private int												MChildScopeTableIndex;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTable(CSymbolTable ParentScopeTable, int ChildScopeIndexInParentTable, int BaseStackOffset)
		{
			MParentScopeTable=ParentScopeTable;
			MChildScopeIndexInParentTable=ChildScopeIndexInParentTable;
			MBaseStackOffset=BaseStackOffset;

			MSymbolItems=new List<CSymbolTableItem>();
			MChildScopeTables=new List<CSymbolTable>();
			MChildScopeTableIndex=0;

			if (ParentScopeTable==null)
			{
				MSymbolTableLevel=0;
			}
			else
			{
				MSymbolTableLevel=ParentScopeTable.MSymbolTableLevel+1;
			}
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
		public int												SymbolTableLevel
		{
			get
			{
				return(MSymbolTableLevel);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int												BaseStackOffset
		{
			get
			{
				return(MBaseStackOffset);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int												SymbolItemsStackSize
		{
			get
			{
				int						StackSize=0;

				foreach(CSymbolTableItem Item in MSymbolItems)
				{
					StackSize+=Item.SymbolTableData.GetSizeof();
				}

				return(StackSize);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddSymbol(CSymbolTableData Data)
		{
			int							StackOffset;

			// Na ROOT urovni je OFFSET 0, lebo GLOBALNE PREMENNE sa ukladaju MIMO STACK.
			if ((this is CSymbolTable_Root)==true)
			{
				StackOffset=0;
			}
			// !!! Aj na urovni DEKLARACI FUNKCIE je OFFSET 0, pretoze OFFSET sa vypocita az ked su VSETKY PREMENNE zaradene do SYMBOL TABLE a je jasne kolko parametrov ma dana funkcia.
			else if ((this is CSymbolTable_FunctionDeclaration)==true)
			{
				StackOffset=0;
			}
			else
			{
				StackOffset=MBaseStackOffset-SymbolItemsStackSize-Data.GetSizeof();
			}
			
			CSymbolTableItem			Item=new CSymbolTableItem(Data,StackOffset);

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
			CSymbolTableItem				ExistingTableItem=MSymbolItems.Where(P => P.SymbolTableData.SymbolName==SymbolName).FirstOrDefault();

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
			CSymbolTableItem				ExistingTableItem=MSymbolItems.Where(P => P.SymbolTableData.SymbolName==SymbolName).FirstOrDefault();

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
			CSymbolTableData_Function		ExistingTableItem=MSymbolItems.Select(P => P.SymbolTableData).OfType<CSymbolTableData_Function>().Where(P => P.SymbolName==SymbolName).FirstOrDefault();

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
			CSymbolTableItem				ExistingTableItem=MSymbolItems.Where(P => P.SymbolTableData.SymbolName==SymbolName).FirstOrDefault();

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
		public CSymbolTable_FunctionDeclaration GetFunctionSymbolTable(string FunctionName)
		{
			CSymbolTable_FunctionDeclaration	FunctionTable=MChildScopeTables.OfType<CSymbolTable_FunctionDeclaration>().Where(P => P.FunctionName==FunctionName).FirstOrDefault();

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
		public CSymbolTable_FunctionDeclaration GetFunctionSymbolTableInCurrentOrParentScope()
		{
			CSymbolTable_FunctionDeclaration	ExistingTableFunction=this as CSymbolTable_FunctionDeclaration;

			if (ExistingTableFunction!=null)
			{
				return(ExistingTableFunction);
			}
			else
			{
				if (MParentScopeTable!=null)
				{
					return(MParentScopeTable.GetFunctionSymbolTableInCurrentOrParentScope());
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
		public int CalculateTotalStackSize()
		{
			int						StackSize=SymbolItemsStackSize;
			int						MaxStackSizeInSubNode=0;

			foreach(CSymbolTable ChildScopeTable in MChildScopeTables)
			{
				int					StackSizeInSubNode=ChildScopeTable.CalculateTotalStackSize();

				MaxStackSizeInSubNode=Math.Max(MaxStackSizeInSubNode,StackSizeInSubNode);
			}

			StackSize+=MaxStackSizeInSubNode;

			return(StackSize);
		}
//-------------------------------------------------------------------------------------------------------
		public int CalculateSubNodesTotalStackSize()
		{
			int						MaxStackSizeInSubNode=0;

			foreach(CSymbolTable ChildScopeTable in MChildScopeTables)
			{
				// Musim volat CalculateTotalStackSize() a NIE SAM SEBA.
				int					StackSizeInSubNode=ChildScopeTable.CalculateTotalStackSize();

				MaxStackSizeInSubNode=Math.Max(MaxStackSizeInSubNode,StackSizeInSubNode);
			}

			return(MaxStackSizeInSubNode);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------