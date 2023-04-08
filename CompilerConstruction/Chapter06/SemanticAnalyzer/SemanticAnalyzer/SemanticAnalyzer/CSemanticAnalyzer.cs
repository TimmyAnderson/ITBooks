using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSemanticAnalyzer
	{
//-------------------------------------------------------------------------------------------------------
		public void DoAnalysis(CNonterminalCollection NonterminalCollection, CParseTreeNode ParseTreeRoot, List<CSemanticError> SemanticErrors, bool PrintLog)
		{
			CSymbolTableManager									SymbolTableManager=new CSymbolTableManager(PrintLog);
			CParseTreeTraverseItemList							SymbolTableTraverseItemList=SymbolTableManager.CreateTraverseItemList(NonterminalCollection);

			ParseTreeRoot.Traverse(SymbolTableTraverseItemList);

			SemanticErrors.AddRange(SymbolTableManager.SemanticErrors);

			if (SemanticErrors.Count>0)
			{
				return;
			}
			
			CTypeChecker										TypeChecker=new CTypeChecker(SymbolTableManager,PrintLog);

			SymbolTableManager.RootTable.ResetChildScopeTableIndex();

			CParseTreeTraverseItemList							TypeCheckTraverseItemList=TypeChecker.CreateTraverseItemList(NonterminalCollection);

			ParseTreeRoot.Traverse(TypeCheckTraverseItemList);

			SemanticErrors.AddRange(TypeChecker.SemanticErrors);

			if (SemanticErrors.Count>0)
			{
				return;
			}




		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------