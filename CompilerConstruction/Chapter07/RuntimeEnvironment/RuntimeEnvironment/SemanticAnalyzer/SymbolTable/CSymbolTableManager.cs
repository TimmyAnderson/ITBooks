using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSymbolTableManager
	{
//-------------------------------------------------------------------------------------------------------
		private static readonly string							NAME_ID="TerminalID";
		private static readonly string							NAME_TYPE_SPECIFIER="TYPE_SPECIFIER";
		private static readonly string[]						NAME_INT_STRING_VOID=new string[]{"TerminalINT","TerminalSTRING","TerminalVOID"};
		private static readonly string							NAME_NUM="TerminalNumber";
//-------------------------------------------------------------------------------------------------------
		private readonly CSymbolTable							MRootTable;
		private readonly List<CSemanticError>					MSemanticErrors;
		private readonly bool									MPrintLog;
//-------------------------------------------------------------------------------------------------------
		private CSymbolTable									MCurrentTable;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTableManager(bool PrintLog)
		{
			MRootTable=new CSymbolTable_Root(null,0);
			MSemanticErrors=new List<CSemanticError>();
			MPrintLog=PrintLog;

			MCurrentTable=MRootTable;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTable										RootTable
		{
			get
			{
				return(MRootTable);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSemanticError[]									SemanticErrors
		{
			get
			{
				return(MSemanticErrors.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void DefaultPreOrderAction(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			Console.WriteLine(Node.Symbol.Name);
		}
//-------------------------------------------------------------------------------------------------------
		private ESymbolType GetSymbolType(CTerminal_Keyword TypeKeyword, bool IsArray)
		{
			if (TypeKeyword.KeywordLexema=="int")
			{
				if (IsArray==false)
				{
					return(ESymbolType.E_ST_INT);
				}
				else
				{
					return(ESymbolType.E_ST_INT_ARRAY);
				}
			}
			else if (TypeKeyword.KeywordLexema=="string")
			{
				if (IsArray==false)
				{
					return(ESymbolType.E_ST_STRING);
				}
				else
				{
					return(ESymbolType.E_ST_STRING_ARRAY);
				}
			}
			else if (TypeKeyword.KeywordLexema=="void")
			{
				if (IsArray==false)
				{
					return(ESymbolType.E_ST_VOID);
				}
				else
				{
					return(ESymbolType.E_ST_VOID_ARRAY);
				}
			}
			else
			{
				throw(new InvalidOperationException(string.Format("UNEXPECTED VALUE of KEYWORD VALUE [{0}] !",TypeKeyword.KeywordLexema)));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Choice - [VARIABLE_DECLARATION -> TYPE_SPECIFIER id;].
		private void TraversePreOrderAction_VARIABLE_DECLARATION_Choice1(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			if (MPrintLog==true)
			{
				Console.WriteLine("SYMBOL TABLE - VARIABLE_DECLARATION_Choice1 PRE !");
			}

			// Ziska MENO VARIABLE.
			CParseTreeNode								TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
			CToken_Identifier							TokenID=(CToken_Identifier) TreeNodeID.Token;
			string										SymbolName=TokenID.Lexema;

			// Kontroluje sa ci v danom SCOPE nie je deklarovana VARIABLE s ROVNAKYM MENOM.
			if (MCurrentTable.ContainsSymbolInCurrentScope(SymbolName)==true)
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("SYMBOL [{0}] has ALREADY BEEN DECLARED in SCOPE !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}

			// Kontroluje sa ci v nie je deklarovana FUNCTION s ROVNAKYM MENOM.
			if (MCurrentTable.ContainsFunctionInCurrentOrParentScopes(SymbolName)==true)
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("VARIABLE [{0}] has SAME NAME AS FUNCTION !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}

			// Zisti TYP VARIABLE.
			CParseTreeNode								TreeNodeIDParentTypeDeclaration=Node.GetChildTreeNodeBySymbolName(NAME_TYPE_SPECIFIER,0);
			CParseTreeNode								TreeNodeIDTypeDeclaration=TreeNodeIDParentTypeDeclaration.GetChildTreeNodeBySymbolName(NAME_INT_STRING_VOID,0);
			CTerminal_Keyword							TypeKeyword=(CTerminal_Keyword) TreeNodeIDTypeDeclaration.Symbol;
			ESymbolType									SymbolType=GetSymbolType(TypeKeyword,false);

			CSymbolTableData							Item=new CSymbolTableData_Variable(SymbolName,SymbolType);

			if (SymbolType==ESymbolType.E_ST_INT || SymbolType==ESymbolType.E_ST_STRING)
			{
				MCurrentTable.AddSymbol(Item);
			}
			else
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("VARIABLE [{0}] has INVALID TYPE !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;].
		private void TraversePreOrderAction_VARIABLE_DECLARATION_Choice2(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			if (MPrintLog==true)
			{
				Console.WriteLine("SYMBOL TABLE - VARIABLE_DECLARATION_Choice2 PRE !");
			}

			// Ziska MENO VARIABLE.
			CParseTreeNode								TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
			CToken_Identifier							TokenID=(CToken_Identifier) TreeNodeID.Token;
			string										SymbolName=TokenID.Lexema;

			// Kontroluje sa ci v danom SCOPE nie je deklarovana VARIABLE s ROVNAKYM MENOM.
			if (MCurrentTable.ContainsSymbolInCurrentScope(SymbolName)==true)
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("SYMBOL [{0}] has ALREADY BEEN DECLARED in SCOPE !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}

			// Kontroluje sa ci v nie je deklarovana FUNCTION s ROVNAKYM MENOM.
			if (MCurrentTable.ContainsFunctionInCurrentOrParentScopes(SymbolName)==true)
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("VARIABLE [{0}] has SAME NAME AS FUNCTION !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}

			// Zisti TYP VARIABLE.
			CParseTreeNode								TreeNodeIDParentTypeDeclaration=Node.GetChildTreeNodeBySymbolName(NAME_TYPE_SPECIFIER,0);
			CParseTreeNode								TreeNodeIDTypeDeclaration=TreeNodeIDParentTypeDeclaration.GetChildTreeNodeBySymbolName(NAME_INT_STRING_VOID,0);
			CTerminal_Keyword							TypeKeyword=(CTerminal_Keyword) TreeNodeIDTypeDeclaration.Symbol;
			ESymbolType									SymbolType=GetSymbolType(TypeKeyword,false);

			CSymbolTableData							Item=new CSymbolTableData_Variable(SymbolName,SymbolType);

			if (SymbolType==ESymbolType.E_ST_INT || SymbolType==ESymbolType.E_ST_STRING)
			{
				MCurrentTable.AddSymbol(Item);
			}
			else
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("VARIABLE [{0}] has INVALID TYPE !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [VARIABLE_DECLARATION -> TYPE_SPECIFIER id[num];].
		private void TraversePreOrderAction_VARIABLE_DECLARATION_Choice3(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			if (MPrintLog==true)
			{
				Console.WriteLine("SYMBOL TABLE - VARIABLE_DECLARATION_Choice3 PRE !");
			}

			// Ziska MENO VARIABLE.
			CParseTreeNode								TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
			CToken_Identifier							TokenID=(CToken_Identifier) TreeNodeID.Token;
			string										SymbolName=TokenID.Lexema;

			// Kontroluje sa ci v danom SCOPE nie je deklarovana VARIABLE s ROVNAKYM MENOM.
			if (MCurrentTable.ContainsSymbolInCurrentScope(SymbolName)==true)
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("SYMBOL [{0}] has ALREADY BEEN DECLARED in SCOPE !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}

			// Kontroluje sa ci v nie je deklarovana FUNCTION s ROVNAKYM MENOM.
			if (MCurrentTable.ContainsFunctionInCurrentOrParentScopes(SymbolName)==true)
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("VARIABLE [{0}] has SAME NAME AS FUNCTION !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}

			// Zisti TYP VARIABLE.
			CParseTreeNode								TreeNodeIDParentTypeDeclaration=Node.GetChildTreeNodeBySymbolName(NAME_TYPE_SPECIFIER,0);
			CParseTreeNode								TreeNodeIDTypeDeclaration=TreeNodeIDParentTypeDeclaration.GetChildTreeNodeBySymbolName(NAME_INT_STRING_VOID,0);
			CTerminal_Keyword							TypeKeyword=(CTerminal_Keyword) TreeNodeIDTypeDeclaration.Symbol;
			ESymbolType									SymbolType=GetSymbolType(TypeKeyword,true);

			// Zisti velkost ARRAY.
			CParseTreeNode								TreeNodeArraySize=Node.GetChildTreeNodeBySymbolName(NAME_NUM,0);
			CToken										TokenArraySize=(CToken) TreeNodeArraySize.Token;
			int											ArraySize=int.Parse(TokenArraySize.Lexema);

			CSymbolTableData_ArrayVariable				Item=new CSymbolTableData_ArrayVariable(SymbolName,SymbolType,ArraySize);

			if (SymbolType==ESymbolType.E_ST_INT_ARRAY || SymbolType==ESymbolType.E_ST_STRING_ARRAY)
			{
				MCurrentTable.AddSymbol(Item);
			}
			else
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("ARRAY VARIABLE [{0}] has INVALID TYPE !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT].
		private void TraversePreOrderAction_FUNCTION_DECLARATION(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			if (MPrintLog==true)
			{
				Console.WriteLine("SYMBOL TABLE - FUNCTION_DECLARATION PRE !");
			}

			// Ziska MENO FUNCTION.
			CParseTreeNode								TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
			CToken_Identifier							TokenID=(CToken_Identifier) TreeNodeID.Token;
			string										SymbolName=TokenID.Lexema;

			// Kontroluje sa ci v danom SCOPE nie je deklarovana FUNCTION s ROVNAKYM MENOM.
			if (MCurrentTable.ContainsSymbolInCurrentScope(SymbolName)==true)
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("SYMBOL [{0}] has ALREADY BEEN DECLARED in SCOPE !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}

			// Zisti RETURN TYPE FUNCTION.
			CParseTreeNode								TreeNodeIDParentFunctionTypeDeclaration=Node.GetChildTreeNodeBySymbolName(NAME_TYPE_SPECIFIER,0);
			CParseTreeNode								TreeNodeIDFunctionTypeDeclaration=TreeNodeIDParentFunctionTypeDeclaration.GetChildTreeNodeBySymbolName(NAME_INT_STRING_VOID,0);
			CTerminal_Keyword							FunctionTypeKeyword=(CTerminal_Keyword) TreeNodeIDFunctionTypeDeclaration.Symbol;
			ESymbolType									FunctionSymbolType=GetSymbolType(FunctionTypeKeyword,false);

			CSymbolTableData_Function					Item=new CSymbolTableData_Function(SymbolName,ESymbolType.E_ST_FUNCTION,FunctionSymbolType);

			if (FunctionSymbolType==ESymbolType.E_ST_VOID || FunctionSymbolType==ESymbolType.E_ST_INT || FunctionSymbolType==ESymbolType.E_ST_STRING)
			{
				MCurrentTable.AddSymbol(Item);
			}
			else
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("FUNCTION [{0}] has INVALID RETURN TYPE !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}

			// Vytvori NOVU SYMBOL TABLE reprezentujucu NOVY SCOPE.
			CSymbolTable								NewTable=new CSymbolTable_Function(MCurrentTable,MCurrentTable.ChildScopeTables.Length,SymbolName);

			MCurrentTable.AddChildScopeTables(NewTable);

			// Nastavi SYMBOL TABLE na SYMBOL TABLE reprezentujucu NOVY SCOPE.
			MCurrentTable=NewTable;
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT].
		private void TraversePostOrderAction_FUNCTION_DECLARATION(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			if (MPrintLog==true)
			{
				Console.WriteLine("SYMBOL TABLE - FUNCTION_DECLARATION POST !");
			}

			// Nastavi SYMBOL TABLE na PARENT SYMBOL TABLE reprezentujucu PREDCHADZAJUCI SCOPE.
			MCurrentTable=MCurrentTable.ParentScopeTable;
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [PARAM -> TYPE_SPECIFIER id].
		private void TraversePreOrderAction_PARAM_Choice1(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			if (MPrintLog==true)
			{
				Console.WriteLine("SYMBOL TABLE - PARAM_Choice1 PRE !");
			}

			// Ziska MENO VARIABLE.
			CParseTreeNode								TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
			CToken_Identifier							TokenID=(CToken_Identifier) TreeNodeID.Token;
			string										SymbolName=TokenID.Lexema;

			// Kontroluje sa ci v danom SCOPE nie je deklarovana VARIABLE s ROVNAKYM MENOM.
			if (MCurrentTable.ContainsSymbolInCurrentScope(SymbolName)==true)
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("SYMBOL [{0}] has ALREADY BEEN DECLARED in SCOPE !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}

			// Kontroluje sa ci v nie je deklarovana FUNCTION s ROVNAKYM MENOM.
			if (MCurrentTable.ContainsFunctionInCurrentOrParentScopes(SymbolName)==true)
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("VARIABLE [{0}] has SAME NAME AS FUNCTION !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}

			// Zisti TYP VARIABLE.
			CParseTreeNode								TreeNodeIDParentTypeDeclaration=Node.GetChildTreeNodeBySymbolName(NAME_TYPE_SPECIFIER,0);
			CParseTreeNode								TreeNodeIDTypeDeclaration=TreeNodeIDParentTypeDeclaration.GetChildTreeNodeBySymbolName(NAME_INT_STRING_VOID,0);
			CTerminal_Keyword							TypeKeyword=(CTerminal_Keyword) TreeNodeIDTypeDeclaration.Symbol;
			ESymbolType									SymbolType=GetSymbolType(TypeKeyword,false);

			CSymbolTableData							Item=new CSymbolTableData_Param(SymbolName,SymbolType);

			if (SymbolType==ESymbolType.E_ST_INT || SymbolType==ESymbolType.E_ST_STRING)
			{
				MCurrentTable.AddSymbol(Item);
			}
			else
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("VARIABLE [{0}] has INVALID TYPE !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [PARAM -> TYPE_SPECIFIER id[]].
		private void TraversePreOrderAction_PARAM_Choice2(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			if (MPrintLog==true)
			{
				Console.WriteLine("SYMBOL TABLE - PARAM_Choice2 PRE !");
			}

			// Ziska MENO ARRAY VARIABLE.
			CParseTreeNode								TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
			CToken_Identifier							TokenID=(CToken_Identifier) TreeNodeID.Token;
			string										SymbolName=TokenID.Lexema;

			// Kontroluje sa ci v danom SCOPE nie je deklarovana VARIABLE s ROVNAKYM MENOM.
			if (MCurrentTable.ContainsSymbolInCurrentScope(SymbolName)==true)
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("SYMBOL [{0}] has ALREADY BEEN DECLARED in SCOPE !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}

			// Kontroluje sa ci v nie je deklarovana FUNCTION s ROVNAKYM MENOM.
			if (MCurrentTable.ContainsFunctionInCurrentOrParentScopes(SymbolName)==true)
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("ARRAY VARIABLE [{0}] has SAME NAME AS FUNCTION !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}

			// Zisti TYP ARRAY VARIABLE.
			CParseTreeNode								TreeNodeIDParentTypeDeclaration=Node.GetChildTreeNodeBySymbolName(NAME_TYPE_SPECIFIER,0);
			CParseTreeNode								TreeNodeIDTypeDeclaration=TreeNodeIDParentTypeDeclaration.GetChildTreeNodeBySymbolName(NAME_INT_STRING_VOID,0);
			CTerminal_Keyword							TypeKeyword=(CTerminal_Keyword) TreeNodeIDTypeDeclaration.Symbol;
			ESymbolType									SymbolType=GetSymbolType(TypeKeyword,true);

			CSymbolTableData							Item=new CSymbolTableData_Param(SymbolName,SymbolType);

			if (SymbolType==ESymbolType.E_ST_INT_ARRAY || SymbolType==ESymbolType.E_ST_STRING_ARRAY)
			{
				MCurrentTable.AddSymbol(Item);
			}
			else
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("ARRAY VARIABLE [{0}] has INVALID TYPE !",SymbolName));

				MSemanticErrors.Add(SemanticError);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}].
		private void TraversePreOrderAction_COMPOUND_STATEMENT(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			if (MPrintLog==true)
			{
				Console.WriteLine("SYMBOL TABLE - COMPOUND_STATEMENT PRE !");
			}

			bool								Found=false;
			int									Level=1;
			CSymbolTable						Iterator=MCurrentTable;
			string								FunctionName=null;

			// Najde FUNCTION v ktorej je BLOK DEKLAROVANY.
			while(Iterator!=null)
			{
				if ((Iterator is CSymbolTable_Function)==true)
				{
					CSymbolTable_Function		Function=(CSymbolTable_Function) Iterator;

					FunctionName=Function.FunctionName;
					Found=true;
					break;
				}
				else
				{
					Level++;
					Iterator=Iterator.ParentScopeTable;
				}
			}

			if (Found==true)
			{
				// Vytvori NOVU SYMBOL TABLE reprezentujucu NOVY SCOPE.
				CSymbolTable					NewTable=new CSymbolTable_Block(MCurrentTable,MCurrentTable.ChildScopeTables.Length,FunctionName,Level);

				MCurrentTable.AddChildScopeTables(NewTable);

				MCurrentTable=NewTable;
			}
			else
			{
				throw(new InvalidOperationException(string.Format("Can't FIND FUNCTION for BLOCK in PARENT SYMBOL TABLES !")));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}].
		private void TraversePostOrderAction_COMPOUND_STATEMENT(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			if (MPrintLog==true)
			{
				Console.WriteLine("SYMBOL TABLE - COMPOUND_STATEMENT POST !");
			}

			// Nastavi SYMBOL TABLE na PARENT SYMBOL TABLE reprezentujucu PREDCHADZAJUCI SCOPE.
			MCurrentTable=MCurrentTable.ParentScopeTable;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParseTreeTraverseItemList CreateTraverseItemList(CNonterminalCollection NonterminalCollection)
		{
			CChoice							Choice_VARIABLE_DECLARATION_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="VARIABLE_DECLARATION").First().Choices[0];
			CChoice							Choice_VARIABLE_DECLARATION_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="VARIABLE_DECLARATION").First().Choices[1];
			CChoice							Choice_VARIABLE_DECLARATION_Choice3=NonterminalCollection.Nonterminals.Where(P => P.Name=="VARIABLE_DECLARATION").First().Choices[2];
			CChoice							Choice_FUNCTION_DECLARATION=NonterminalCollection.Nonterminals.Where(P => P.Name=="FUNCTION_DECLARATION").First().Choices[0];
			CChoice							Choice_PARAM_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="PARAM").First().Choices[0];
			CChoice							Choice_PARAM_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="PARAM").First().Choices[1];
			CChoice							Choice_COMPOUND_STATEMENT=NonterminalCollection.Nonterminals.Where(P => P.Name=="COMPOUND_STATEMENT").First().Choices[0];

			int[]							Order_VARIABLE_DECLARATION_Choice1=new int[]{0,1,2};
			int[]							Order_VARIABLE_DECLARATION_Choice2=new int[]{0,1,2,3,4};
			int[]							Order_VARIABLE_DECLARATION_Choice3=new int[]{0,1,2,3,4,5};
			int[]							Order_FUNCTION_DECLARATION=new int[]{0,1,2,3,4,5};
			int[]							Order_PARAM_Choice1=new int[]{0,1};
			int[]							Order_PARAM_Choice2=new int[]{0,1,2,3};
			int[]							Order_COMPOUND_STATEMENT=new int[]{0,1,2,3};

			CParseTreeTraverseItem			PTTI_VARIABLE_DECLARATION_Choice1=new CParseTreeTraverseItem(Choice_VARIABLE_DECLARATION_Choice1,TraversePreOrderAction_VARIABLE_DECLARATION_Choice1,null,Order_VARIABLE_DECLARATION_Choice1);
			CParseTreeTraverseItem			PTTI_VARIABLE_DECLARATION_Choice2=new CParseTreeTraverseItem(Choice_VARIABLE_DECLARATION_Choice2,TraversePreOrderAction_VARIABLE_DECLARATION_Choice2,null,Order_VARIABLE_DECLARATION_Choice2);
			CParseTreeTraverseItem			PTTI_VARIABLE_DECLARATION_Choice3=new CParseTreeTraverseItem(Choice_VARIABLE_DECLARATION_Choice3,TraversePreOrderAction_VARIABLE_DECLARATION_Choice3,null,Order_VARIABLE_DECLARATION_Choice3);
			CParseTreeTraverseItem			PTTI_FUNCTION_DECLARATION=new CParseTreeTraverseItem(Choice_FUNCTION_DECLARATION,TraversePreOrderAction_FUNCTION_DECLARATION,TraversePostOrderAction_FUNCTION_DECLARATION,Order_FUNCTION_DECLARATION);
			CParseTreeTraverseItem			PTTI_PARAM_Choice1=new CParseTreeTraverseItem(Choice_PARAM_Choice1,TraversePreOrderAction_PARAM_Choice1,null,Order_PARAM_Choice1);
			CParseTreeTraverseItem			PTTI_PARAM_Choice2=new CParseTreeTraverseItem(Choice_PARAM_Choice2,TraversePreOrderAction_PARAM_Choice2,null,Order_PARAM_Choice2);
			CParseTreeTraverseItem			PTTI_COMPOUND_STATEMENT=new CParseTreeTraverseItem(Choice_COMPOUND_STATEMENT,TraversePreOrderAction_COMPOUND_STATEMENT,TraversePostOrderAction_COMPOUND_STATEMENT,Order_COMPOUND_STATEMENT);

			CParseTreeTraverseItemList		List=new CParseTreeTraverseItemList(DefaultPreOrderAction,null);

			List.AddTraverseItem(PTTI_VARIABLE_DECLARATION_Choice1);
			List.AddTraverseItem(PTTI_VARIABLE_DECLARATION_Choice2);
			List.AddTraverseItem(PTTI_VARIABLE_DECLARATION_Choice3);
			List.AddTraverseItem(PTTI_FUNCTION_DECLARATION);
			List.AddTraverseItem(PTTI_PARAM_Choice1);
			List.AddTraverseItem(PTTI_PARAM_Choice2);
			List.AddTraverseItem(PTTI_COMPOUND_STATEMENT);

			return(List);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------