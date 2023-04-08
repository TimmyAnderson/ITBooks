using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSemanticAnalyzer
	{
//-------------------------------------------------------------------------------------------------------
		private readonly StringBuilder							MLog;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSemanticAnalyzer()
		{
			MLog=new StringBuilder();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											Log
		{
			get
			{
				return(MLog.ToString());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void PrintSymbolTable(CSymbolTable SymbolTable)
		{
			int				Padding=SymbolTable.SymbolTableLevel*3;

			MLog.AppendLine(string.Format("{0}{1}, StackSize: [{2}], TotalStackSize: [{3}]","".PadRight(Padding,' '),SymbolTable.ToString(),SymbolTable.SymbolItemsStackSize,SymbolTable.CalculateTotalStackSize()));

			foreach(CSymbolTableItem Item in SymbolTable.SymbolItems)
			{
				CSymbolTableData			Data=Item.SymbolTableData;

				MLog.AppendLine(string.Format("{0}{1} {2} - SIZE: {3}, OFFSET: {4}","".PadRight(Padding+1,' '),Data.SymbolName,Data.SymbolType,Data.GetSizeof(),Item.StackOffset));
			}

			MLog.AppendLine("".PadRight(20,'-'));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public bool Analyze(CNonterminalCollection NonterminalCollection, CParseTreeNode ParseTreeRoot, out CSymbolTable SymbolTable, out CStringLiterals Literals, out CSymbolTableData_Variable[] GlobalVariables, CCompilerErrorCollection Errors)
		{
			MLog.Clear();

			MLog.AppendLine("".PadLeft(79,'-'));
			MLog.AppendLine("".PadLeft(79,'-'));
			MLog.AppendLine("".PadLeft(79,'-'));
			MLog.AppendLine("SYMBOL TABLE CREATION");
			MLog.AppendLine("".PadLeft(79,'-'));
			MLog.AppendLine("".PadLeft(79,'-'));
			MLog.AppendLine("".PadLeft(79,'-'));

			CSymbolTableManager									SymbolTableManager=new CSymbolTableManager();
			CParseTreeTraverseItemList							SymbolTableTraverseItemList=SymbolTableManager.CreateTraverseItemList(NonterminalCollection);

			ParseTreeRoot.Traverse(SymbolTableTraverseItemList);

			MLog.Append(SymbolTableManager.Log);
			MLog.AppendLine("".PadLeft(79,'-'));

			Errors.AddErrors(SymbolTableManager.SemanticErrors);

			if (Errors.HasErrors==true)
			{
				SymbolTable=null;
				Literals=null;
				GlobalVariables=null;
				return(false);
			}

			MLog.AppendLine("".PadLeft(79,'-'));
			MLog.AppendLine("".PadLeft(79,'-'));
			MLog.AppendLine("".PadLeft(79,'-'));
			MLog.AppendLine("TYPE CHECKER");
			MLog.AppendLine("".PadLeft(79,'-'));
			MLog.AppendLine("".PadLeft(79,'-'));
			MLog.AppendLine("".PadLeft(79,'-'));
			
			CTypeChecker										TypeChecker=new CTypeChecker(SymbolTableManager.RootTable);

			SymbolTableManager.RootTable.ResetChildScopeTableIndex();

			CParseTreeTraverseItemList							TypeCheckTraverseItemList=TypeChecker.CreateTraverseItemList(NonterminalCollection);

			ParseTreeRoot.Traverse(TypeCheckTraverseItemList);

			MLog.Append(SymbolTableManager.Log);
			MLog.AppendLine("".PadLeft(79,'-'));
			MLog.AppendLine("".PadLeft(79,'-'));
			MLog.AppendLine("".PadLeft(79,'-'));

			Errors.AddErrors(TypeChecker.SemanticErrors);

			if (Errors.HasErrors==false)
			{
				SymbolTable=SymbolTableManager.RootTable;

				MLog.AppendLine("".PadLeft(79,'-'));
				MLog.AppendLine("".PadLeft(79,'-'));
				MLog.AppendLine("".PadLeft(79,'-'));
				MLog.AppendLine("SYMBOL TABLE");
				MLog.AppendLine("".PadLeft(79,'-'));
				MLog.AppendLine("".PadLeft(79,'-'));
				MLog.AppendLine("".PadLeft(79,'-'));

				SymbolTable.TraverseSymbolTableTree(PrintSymbolTable);

				MLog.AppendLine("".PadLeft(79,'-'));
				MLog.AppendLine("".PadLeft(79,'-'));
				MLog.AppendLine("".PadLeft(79,'-'));

				Literals=new CStringLiterals();

				string[]										StringLiterals=TypeChecker.StringLiterals;

				foreach(string StringLiteral in StringLiterals)
				{
					Literals.AddLiteral(StringLiteral);
				}

				GlobalVariables=SymbolTableManager.GlobalVariables;

				return(true);
			}
			else
			{
				SymbolTable=null;
				Literals=null;
				GlobalVariables=null;
				return(false);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------