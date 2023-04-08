using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CTypeChecker
	{
//-------------------------------------------------------------------------------------------------------
		private static readonly string							NAME_ID="TerminalID";
		private static readonly string							NAME_NUMBER="TerminalNumber";
		private static readonly string							NAME_CALL="CALL";
		private static readonly string							NAME_VARIABLE="VARIABLE";
		private static readonly string							NAME_EXPRESSION="EXPRESSION";
		private static readonly string							NAME_TERM="TERM";
		private static readonly string							NAME_FACTOR="FACTOR";
		private static readonly string							NAME_ADDITIVE_EXPRESSION="ADDITIVE_EXPRESSION";
		private static readonly string							NAME_ADD_OPERATION="ADD_OPERATION";
		private static readonly string							NAME_ARG_LIST="ARG_LIST";
		private static readonly string							NAME_ARGS="ARGS";
		private static readonly string							NAME_CONST="CONST";
		private static readonly string							NAME_STATEMENT="STATEMENT";
		private static readonly string							NAME_RETURN_STATEMENT="RETURN_STATEMENT";
		private static readonly string							NAME_ITERATION_STATEMENT="ITERATION_STATEMENT";
		private static readonly string							NAME_STATEMENT_LIST="STATEMENT_LIST";
		private static readonly string							NAME_SELECTION_STATEMENT="SELECTION_STATEMENT";
		private static readonly string							NAME_COMPOUND_STATEMENT="COMPOUND_STATEMENT";
		private static readonly string							NAME_TYPE_SPECIFIER="TYPE_SPECIFIER";
		private static readonly string							NAME_TERMINAL_IF="TerminalIF";
		private static readonly string							NAME_TERMINAL_WHILE="TerminalWHILE";
		private static readonly string							NAME_TERMINAL_RETURN="TerminalRETURN";
		private static readonly string[]						NAME_INT_STRING_VOID=new string[]{"TerminalINT","TerminalSTRING","TerminalVOID"};
		private static readonly string							NAME_STRING_LITERAL="TerminalString";
		private static readonly string							NAME_TERMINAL_PLUS="TerminalPlus";
//-------------------------------------------------------------------------------------------------------
		private readonly HashSet<string>						MStringLiterals;
		private readonly List<CSemanticError>					MSemanticErrors;
		private readonly StringBuilder							MLog;
//-------------------------------------------------------------------------------------------------------
		private CSymbolTable									MCurrentTable;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTypeChecker(CSymbolTable RootTable)
		{
			MStringLiterals=new HashSet<string>();
			MSemanticErrors=new List<CSemanticError>();
			MLog=new StringBuilder();

			MCurrentTable=RootTable;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string[]											StringLiterals
		{
			get
			{
				string[]										Literals=MStringLiterals.ToArray();

				return(Literals);
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
		private void DefaultPreOrderAction(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine(Node.Symbol.Name);
		}
//-------------------------------------------------------------------------------------------------------
		private ESymbolType ConvertArrayTypeToBaseType(ESymbolType ArrayType)
		{
			if (ArrayType==ESymbolType.E_ST_INT_ARRAY)
			{
				return(ESymbolType.E_ST_INT);
			}
			else if (ArrayType==ESymbolType.E_ST_STRING_ARRAY)
			{
				return(ESymbolType.E_ST_STRING);
			}
			else if (ArrayType==ESymbolType.E_ST_VOID_ARRAY)
			{
				return(ESymbolType.E_ST_VOID);
			}
			else
			{
				throw(new InvalidOperationException(string.Format("UNEXPECTED VALUE of ARRAY TYPE [{0}] !",ArrayType.EXT_GetFriendlyName())));
			}
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
				throw(new InvalidOperationException(string.Format("UNEXPECTED VALUE of TYPE VALUE [{0}] !",TypeKeyword.KeywordLexema)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private bool IsValidLiteral(string StringLiteral)
		{
			for(int i=0;i<StringLiteral.Length;i++)
			{
				char											Char=StringLiteral[i];

				if (Char=='\\')
				{
					char										NextChar=StringLiteral[i+1];

					if (NextChar=='n')
					{
						return(true);
					}
					else if (NextChar=='\\')
					{
						return(true);
					}
					else if (NextChar=='"')
					{
						return(true);
					}
					else
					{
						return(false);
					}
				}
			}

			return(true);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Choice - [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;].
		private void TraversePostOrderAction_VARIABLE_DECLARATION_Choice2(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("SYMBOL TABLE - VARIABLE_DECLARATION_Choice2 POST !");

			// Ziska MENO VARIABLE.
			CParseTreeNode								TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
			CToken_Identifier							TokenID=(CToken_Identifier) TreeNodeID.Token;
			string										SymbolName=TokenID.Lexema;

			CParseTreeNode								CONST=Node.GetChildTreeNodeBySymbolName(NAME_CONST,0);
			CParseTreeNodeData_Type						Type=CONST.GetTreeNodeData<CParseTreeNodeData_Type>();

			// Ziska TYP KONSTANTY.
			if (Type!=null)
			{
				if (MCurrentTable.ContainsSymbolInCurrentOrParentScopes(SymbolName)==true)
				{
					CSymbolTableItem					SymbolFromSymbolTable=MCurrentTable.GetSymbolFromCurrentOrParentScopes(SymbolName);
					CSymbolTableData_Variable			Variable=(CSymbolTableData_Variable) SymbolFromSymbolTable.SymbolTableData;
					
					// Porovna ci TYP konstanty je zhodny s TYPOM VARIABLE.
					if (SymbolFromSymbolTable.SymbolTableData.SymbolType!=Type.SymbolType)
					{
						CSemanticError					SemanticError=new CSemanticError(string.Format("CONSTANT has INVALID TYPE !"),TreeNodeID.Token);

						MSemanticErrors.Add(SemanticError);
					}
					else
					{
						if (SymbolFromSymbolTable.SymbolTableData.SymbolType==ESymbolType.E_ST_INT)
						{
							CParseTreeNode				INT=CONST.GetChildTreeNodeBySymbolName(NAME_NUMBER,0);
							CToken						Token=INT.Token;
							string						Lexema=Token.Lexema;
							int							Value=int.Parse(Lexema);

							Variable.ConstValue=Value;
						}
						else if (SymbolFromSymbolTable.SymbolTableData.SymbolType==ESymbolType.E_ST_STRING)
						{
							CParseTreeNode				STRING=CONST.GetChildTreeNodeBySymbolName(NAME_STRING_LITERAL,0);
							CToken						Token=STRING.Token;
							string						Lexema=Token.Lexema;
							
							Variable.ConstValue=Lexema;
						}
						else
						{
							throw(new InvalidOperationException(string.Format("INVALID TYPE of CONST !",Node)));
						}
					}
				}
				else
				{
					CSemanticError						SemanticError=new CSemanticError(string.Format("VARIABLE [{0}] is NOT DECLARED in SCOPE !",SymbolName),TreeNodeID.Token);

					MSemanticErrors.Add(SemanticError);
				}
			}
			// ATTRIBUTE CParseTreeNodeData_Type je POVINNY.
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain CONST TYPE INFORMATION !",Node)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [VARIABLE_DECLARATION -> TYPE_SPECIFIER id[num];].
		private void TraversePostOrderAction_VARIABLE_DECLARATION_Choice3(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("SYMBOL TABLE - VARIABLE_DECLARATION_Choice3 POST !");

			CParseTreeNode								TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
			CToken_Identifier							TokenID=(CToken_Identifier) TreeNodeID.Token;
			string										SymbolName=TokenID.Lexema;

			CParseTreeNode								NUMBER=Node.GetChildTreeNodeBySymbolName(NAME_NUMBER,0);
			CToken										TokenNumber=NUMBER.Token;
			int											ArraySize=int.Parse(TokenNumber.Lexema);

			if (ArraySize<=0)
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("VARIABLE [{0}] is ARRAY with INVALID SIZE !",SymbolName),TreeNodeID.Token);

				MSemanticErrors.Add(SemanticError);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT].
		private void TraversePreOrderAction_FUNCTION_DECLARATION(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - FUNCTION_DECLARATION PRE !");

			// Nastavi SYMBOL TABLE na SYMBOL TABLE reprezentujucu NOVY SCOPE.
			MCurrentTable=MCurrentTable.MoveToNextChildScopeTableIndex();
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT].
		private void TraversePostOrderAction_FUNCTION_DECLARATION(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - FUNCTION_DECLARATION POST !");

			// Ziska MENO FUNCTION.
			CParseTreeNode								TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
			CToken_Identifier							TokenID=(CToken_Identifier) TreeNodeID.Token;
			string										SymbolName=TokenID.Lexema;

			// Zisti RETURN TYPE FUNCTION.
			CParseTreeNode								TreeNodeIDParentTypeDeclaration=Node.GetChildTreeNodeBySymbolName(NAME_TYPE_SPECIFIER,0);
			CParseTreeNode								TreeNodeIDTypeDeclaration=TreeNodeIDParentTypeDeclaration.GetChildTreeNodeBySymbolName(NAME_INT_STRING_VOID,0);
			CTerminal_Keyword							TypeKeyword=(CTerminal_Keyword) TreeNodeIDTypeDeclaration.Symbol;
			ESymbolType									SymbolType=GetSymbolType(TypeKeyword,false);

			CParseTreeNode								COMPOUND_STATEMENT=Node.GetChildTreeNodeBySymbolName(NAME_COMPOUND_STATEMENT,0);
			CParseTreeNodeData_ReturnType				ReturnType=COMPOUND_STATEMENT.GetTreeNodeData<CParseTreeNodeData_ReturnType>();
			CParseTreeNodeData_HasReturn				HasReturn=COMPOUND_STATEMENT.GetTreeNodeData<CParseTreeNodeData_HasReturn>();

			// Skontroluje ci FUNCTION SKUTOCNE VRACIA NAVRATOVU HODNOTU - FUNCTION_DECLARATION ma ATTRIBUTE HasReturn. Ten je nastaveny ak v SCOPE na urovni FUNCTION (BLOK {} hned za DEKLARACIOU FUNCTION) ma RETURN_STATEMENT, alebo IF-ELSE BLOK v SCOPE na urovni FUNCTION ma v IF aj ELSE BLOKU RETURN_STATEMENT.
			if (SymbolType!=ESymbolType.E_ST_VOID && (ReturnType==null || HasReturn==null))
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("FUNCTION [{0}] does NOT RETURN VALUE !",SymbolName),TreeNodeID.Token);

				MSemanticErrors.Add(SemanticError);
			}

			// Skontroluje ci FUNCTION ma KOREKTNY TYP RETURN VALUE - ak nejaky RETURN VALUE vracia, alebo ci nema deklarovany RETURN_STATEMENT, ked v skutocnosti vracia VOID.
			if (ReturnType!=null && ReturnType.SymbolType!=SymbolType)
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("FUNCTION [{0}] EXPECTS to RETURN [{1}] VALUE but RETURNS [{2}] VALUE !",SymbolName,SymbolType,ReturnType.SymbolType),ReturnType.Token);

				MSemanticErrors.Add(SemanticError);
			}

			// Nastavi SYMBOL TABLE na PARENT SYMBOL TABLE reprezentujucu PREDCHADZAJUCI SCOPE.
			MCurrentTable=MCurrentTable.ParentScopeTable;
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}].
		private void TraversePreOrderAction_COMPOUND_STATEMENT(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - COMPOUND_STATEMENT PRE !");

			// Nastavi SYMBOL TABLE na SYMBOL TABLE reprezentujucu NOVY SCOPE.
			MCurrentTable=MCurrentTable.MoveToNextChildScopeTableIndex();
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}].
		private void TraversePostOrderAction_COMPOUND_STATEMENT(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - COMPOUND_STATEMENT POST !");

			CParseTreeNode								STATEMENT_LIST=Node.GetChildTreeNodeBySymbolName(NAME_STATEMENT_LIST,0);
			CParseTreeNodeData_ReturnType				ReturnType=STATEMENT_LIST.GetTreeNodeData<CParseTreeNodeData_ReturnType>();

			// Nepovinny ATTRIBUTE.
			if (ReturnType!=null)
			{
				CParseTreeNodeData_ReturnType			NewReturnType=new CParseTreeNodeData_ReturnType(ReturnType.SymbolType,ReturnType.Token);

				Node.SetTreeNodeData(NewReturnType);
			}

			CParseTreeNodeData_HasReturn				HasReturn=STATEMENT_LIST.GetTreeNodeData<CParseTreeNodeData_HasReturn>();

			// Nepovinny ATTRIBUTE.
			if (HasReturn!=null)
			{
				CParseTreeNodeData_HasReturn			NewHasReturn=new CParseTreeNodeData_HasReturn();

				Node.SetTreeNodeData(NewHasReturn);
			}

			// Nastavi SYMBOL TABLE na PARENT SYMBOL TABLE reprezentujucu PREDCHADZAJUCI SCOPE.
			MCurrentTable=MCurrentTable.ParentScopeTable;
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [VARIABLE -> id].
		private void TraversePostOrderAction_VARIABLE_Choice1(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - VARIABLE_Choice1 POST !");

			// Ziska MENO VARIABLE.
			CParseTreeNode								TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
			CToken_Identifier							TokenID=(CToken_Identifier) TreeNodeID.Token;
			string										SymbolName=TokenID.Lexema;

			// Zisti ci VARIABLE 'id' je deklarovana.
			if (MCurrentTable.ContainsSymbolInCurrentOrParentScopes(SymbolName)==true)
			{
				CSymbolTableItem						SymbolFromSymbolTable=MCurrentTable.GetSymbolFromCurrentOrParentScopes(SymbolName);

				// VARIABLE MUSI byt typu VARIABLE, alebo ARRAY VARIABLE - pri prenose ARRAY do FUNKCIE.
				if (SymbolFromSymbolTable.SymbolTableData.SymbolType==ESymbolType.E_ST_INT || SymbolFromSymbolTable.SymbolTableData.SymbolType==ESymbolType.E_ST_STRING || SymbolFromSymbolTable.SymbolTableData.SymbolType==ESymbolType.E_ST_INT_ARRAY || SymbolFromSymbolTable.SymbolTableData.SymbolType==ESymbolType.E_ST_STRING_ARRAY)
				{
					ESymbolType							SymbolType=SymbolFromSymbolTable.SymbolTableData.SymbolType;
					CParseTreeNodeData_Type				TreeNodeData=new CParseTreeNodeData_Type(SymbolType);

					// Nastavi ATTRIBUTE Type na TYPE VARIABLE.
					Node.SetTreeNodeData(TreeNodeData);
				}
				else
				{
					CParseTreeNodeData_Type				TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_ERROR);

					Node.SetTreeNodeData(TreeNodeData);

					CSemanticError						SemanticError=new CSemanticError(string.Format("VALUE [{0}] is EXPECTED to be VARIABLE or ARRAY VARIABLE !",SymbolName),TreeNodeID.Token);

					MSemanticErrors.Add(SemanticError);
				}
			}
			else
			{
				CParseTreeNodeData_Type					TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_ERROR);

				Node.SetTreeNodeData(TreeNodeData);

				CSemanticError							SemanticError=new CSemanticError(string.Format("VARIABLE [{0}] is NOT DECLARED in SCOPE !",SymbolName),TreeNodeID.Token);

				MSemanticErrors.Add(SemanticError);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [VARIABLE -> id[EXPRESSION]].
		private void TraversePostOrderAction_VARIABLE_Choice2(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - VARIABLE_Choice2 POST !");

			// Ziska MENO VARIABLE.
			CParseTreeNode								TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
			CToken_Identifier							TokenID=(CToken_Identifier) TreeNodeID.Token;
			string										SymbolName=TokenID.Lexema;

			// Zisti ci VARIABLE 'id' je deklarovana.
			if (MCurrentTable.ContainsSymbolInCurrentOrParentScopes(SymbolName)==true)
			{
				CSymbolTableItem						SymbolFromSymbolTable=MCurrentTable.GetSymbolFromCurrentOrParentScopes(SymbolName);

				// VARIABLE MUSI byt typu ARRAY VARIABLE.
				if (SymbolFromSymbolTable.SymbolTableData.SymbolType==ESymbolType.E_ST_INT_ARRAY || SymbolFromSymbolTable.SymbolTableData.SymbolType==ESymbolType.E_ST_STRING_ARRAY)
				{
					ESymbolType							SymbolType=SymbolFromSymbolTable.SymbolTableData.SymbolType;
					ESymbolType							BaseSymbolType=ConvertArrayTypeToBaseType(SymbolType);
					CParseTreeNodeData_Type				TreeNodeData=new CParseTreeNodeData_Type(BaseSymbolType);

					// Nastavi ATTRIBUTE Type na TYPE VARIABLE.
					Node.SetTreeNodeData(TreeNodeData);
				}
				else
				{
					CParseTreeNodeData_Type				TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_ERROR);

					Node.SetTreeNodeData(TreeNodeData);

					CSemanticError						SemanticError=new CSemanticError(string.Format("VALUE [{0}] is EXPECTED to be ARRAY VARIABLE !",SymbolName),TreeNodeID.Token);

					MSemanticErrors.Add(SemanticError);
				}
			}
			else
			{
				CParseTreeNodeData_Type					TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_ERROR);

				Node.SetTreeNodeData(TreeNodeData);

				CSemanticError							SemanticError=new CSemanticError(string.Format("ARRAY VARIABLE [{0}] is NOT DECLARED in SCOPE !",SymbolName),TreeNodeID.Token);

				MSemanticErrors.Add(SemanticError);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [STATEMENT_LIST -> STATEMENT_LIST STATEMENT].
		private void TraversePostOrderAction_STATEMENT_LIST_Choice1(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - STATEMENT_LIST_Choice1 POST !");

			CParseTreeNode								STATEMENT_LIST=Node.GetChildTreeNodeBySymbolName(NAME_STATEMENT_LIST,0);

			// Zisti ReturnType pre STATEMENT_LIST.
			CParseTreeNodeData_ReturnType				ReturnTypeSTATEMENT_LIST=STATEMENT_LIST.GetTreeNodeData<CParseTreeNodeData_ReturnType>();

			// Zisti HasReturn pre STATEMENT_LIST.
			CParseTreeNodeData_HasReturn				HasReturnSTATEMENT_LIST=STATEMENT_LIST.GetTreeNodeData<CParseTreeNodeData_HasReturn>();

			CParseTreeNode								STATEMENT=Node.GetChildTreeNodeBySymbolName(NAME_STATEMENT,0);

			// Zisti ReturnType pre STATEMENT.
			CParseTreeNodeData_ReturnType				ReturnTypeSTATEMENT=STATEMENT.GetTreeNodeData<CParseTreeNodeData_ReturnType>();

			// Zisti HasReturn pre STATEMENT.
			CParseTreeNodeData_HasReturn				HasReturnSTATEMENT=STATEMENT.GetTreeNodeData<CParseTreeNodeData_HasReturn>();

			// Urci ReturnType zo STATEMENT_LIST a STATEMENT a porovna ci nie su rozdielne. Ak su zhodne, prenesie ReturnType do PARENT NODE.
			if (ReturnTypeSTATEMENT_LIST!=null && ReturnTypeSTATEMENT!=null)
			{
				if (ReturnTypeSTATEMENT_LIST.SymbolType==ReturnTypeSTATEMENT.SymbolType)
				{
					CParseTreeNodeData_ReturnType		ReturnType=new CParseTreeNodeData_ReturnType(ReturnTypeSTATEMENT_LIST.SymbolType,ReturnTypeSTATEMENT_LIST.Token);

					Node.SetTreeNodeData(ReturnType);
				}
				else
				{
					CParseTreeNodeData_ReturnType		ReturnType=new CParseTreeNodeData_ReturnType(ESymbolType.E_ST_ERROR,ReturnTypeSTATEMENT.Token);

					Node.SetTreeNodeData(ReturnType);

					CSemanticError						SemanticError=new CSemanticError(string.Format("STATEMENT and STATEMENT LIST contain RETURN VALUES with DIFFERENT TYPES !"),ReturnTypeSTATEMENT.Token);

					MSemanticErrors.Add(SemanticError);
				}
			}
			else if (ReturnTypeSTATEMENT_LIST!=null && ReturnTypeSTATEMENT==null)
			{
				CParseTreeNodeData_ReturnType			ReturnType=new CParseTreeNodeData_ReturnType(ReturnTypeSTATEMENT_LIST.SymbolType,ReturnTypeSTATEMENT_LIST.Token);

				Node.SetTreeNodeData(ReturnType);
			}
			else if (ReturnTypeSTATEMENT_LIST==null && ReturnTypeSTATEMENT!=null)
			{
				CParseTreeNodeData_ReturnType			ReturnType=new CParseTreeNodeData_ReturnType(ReturnTypeSTATEMENT.SymbolType,ReturnTypeSTATEMENT.Token);

				Node.SetTreeNodeData(ReturnType);
			}

			// !!! Ak STATEMENT_LIST, alebo STATEMENT maju nastaveny HasReturn, potom ho posunie do PARENT NODE.
			if (HasReturnSTATEMENT_LIST!=null || HasReturnSTATEMENT!=null)
			{
				CParseTreeNodeData_HasReturn			HasReturn=new CParseTreeNodeData_HasReturn();

				Node.SetTreeNodeData(HasReturn);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [STATEMENT -> COMPOUND_STATEMENT].
		private void TraversePostOrderAction_STATEMENT_Choice2(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - STATEMENT_Choice2 POST !");

			CParseTreeNode								COMPOUND_STATEMENT=Node.GetChildTreeNodeBySymbolName(NAME_COMPOUND_STATEMENT,0);

			// Zisti ReturnType pre COMPOUND_STATEMENT.
			CParseTreeNodeData_ReturnType				ReturnType=COMPOUND_STATEMENT.GetTreeNodeData<CParseTreeNodeData_ReturnType>();

			// Nepovinny ATTRIBUTE.
			if (ReturnType!=null)
			{
				// Ak ReturnType existuje, tak je posunuty do PARENT NODE.
				CParseTreeNodeData_ReturnType			NewReturnType=new CParseTreeNodeData_ReturnType(ReturnType.SymbolType,ReturnType.Token);

				Node.SetTreeNodeData(NewReturnType);
			}

			// Zisti HasReturn pre COMPOUND_STATEMENT.
			CParseTreeNodeData_HasReturn				HasReturn=COMPOUND_STATEMENT.GetTreeNodeData<CParseTreeNodeData_HasReturn>();

			// Nepovinny ATTRIBUTE.
			if (HasReturn!=null)
			{
				// Ak HasReturn existuje, tak je posunuty do PARENT NODE.
				CParseTreeNodeData_HasReturn			NewHasReturn=new CParseTreeNodeData_HasReturn();

				Node.SetTreeNodeData(NewHasReturn);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [STATEMENT -> SELECTION_STATEMENT].
		private void TraversePostOrderAction_STATEMENT_Choice3(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - STATEMENT_Choice3 POST !");

			CParseTreeNode								SELECTION_STATEMENT=Node.GetChildTreeNodeBySymbolName(NAME_SELECTION_STATEMENT,0);

			// Zisti ReturnType pre SELECTION_STATEMENT.
			CParseTreeNodeData_ReturnType				ReturnType=SELECTION_STATEMENT.GetTreeNodeData<CParseTreeNodeData_ReturnType>();

			// Nepovinny ATTRIBUTE.
			if (ReturnType!=null)
			{
				// Ak ReturnType existuje, tak je posunuty do PARENT NODE.
				CParseTreeNodeData_ReturnType			NewReturnType=new CParseTreeNodeData_ReturnType(ReturnType.SymbolType,ReturnType.Token);

				Node.SetTreeNodeData(NewReturnType);
			}

			CParseTreeNodeData_HasReturn				HasReturn=SELECTION_STATEMENT.GetTreeNodeData<CParseTreeNodeData_HasReturn>();

			// Nepovinny ATTRIBUTE.
			if (HasReturn!=null)
			{
				// Ak HasReturn existuje, tak je posunuty do PARENT NODE.
				CParseTreeNodeData_HasReturn			NewHasReturn=new CParseTreeNodeData_HasReturn();

				Node.SetTreeNodeData(NewHasReturn);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [STATEMENT -> ITERATION_STATEMENT].
		private void TraversePostOrderAction_STATEMENT_Choice4(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - STATEMENT_Choice4 POST !");

			CParseTreeNode								ITERATION_STATEMENT=Node.GetChildTreeNodeBySymbolName(NAME_ITERATION_STATEMENT,0);

			// Zisti ReturnType pre ITERATION_STATEMENT.
			CParseTreeNodeData_ReturnType				ReturnType=ITERATION_STATEMENT.GetTreeNodeData<CParseTreeNodeData_ReturnType>();

			// Nepovinny ATTRIBUTE.
			if (ReturnType!=null)
			{
				// Ak ReturnType existuje, tak je posunuty do PARENT NODE.
				CParseTreeNodeData_ReturnType			NewReturnType=new CParseTreeNodeData_ReturnType(ReturnType.SymbolType,ReturnType.Token);

				Node.SetTreeNodeData(NewReturnType);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [STATEMENT -> RETURN_STATEMENT].
		private void TraversePostOrderAction_STATEMENT_Choice5(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - STATEMENT_Choice5 POST !");

			CParseTreeNode								RETURN_STATEMENT=Node.GetChildTreeNodeBySymbolName(NAME_RETURN_STATEMENT,0);

			// Zisti ReturnType pre RETURN_STATEMENT.
			CParseTreeNodeData_ReturnType				ReturnType=RETURN_STATEMENT.GetTreeNodeData<CParseTreeNodeData_ReturnType>();

			if (ReturnType!=null)
			{
				// ATTRIBUTE ReturnType je posunuty do PARENT NODE.
				CParseTreeNodeData_ReturnType			NewReturnType=new CParseTreeNodeData_ReturnType(ReturnType.SymbolType,ReturnType.Token);

				Node.SetTreeNodeData(NewReturnType);
			}
			// ATTRIBUTE je POVINNY.
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain RETURN TYPE INFORMATION !",Node)));
			}

			CParseTreeNodeData_HasReturn				HasReturn=RETURN_STATEMENT.GetTreeNodeData<CParseTreeNodeData_HasReturn>();

			// Nepovinny ATTRIBUTE.
			if (HasReturn!=null)
			{
				// Ak HasReturn existuje, tak je posunuty do PARENT NODE.
				CParseTreeNodeData_HasReturn			NewHasReturn=new CParseTreeNodeData_HasReturn();

				Node.SetTreeNodeData(NewHasReturn);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;].
		private void TraversePostOrderAction_EXPRESSION_STATEMENT_Choice1(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - EXPRESSION_STATEMENT_Choice1 POST !");

			CParseTreeNode								VARIABLE=Node.GetChildTreeNodeBySymbolName(NAME_VARIABLE,0);
			CParseTreeNode								TreeNodeID=VARIABLE.GetChildTreeNodeBySymbolName(NAME_ID,0);

			// Zisti Type pre VARIABLE.
			CParseTreeNodeData_Type						TypeVARIABLE=VARIABLE.GetTreeNodeData<CParseTreeNodeData_Type>();

			CParseTreeNode								EXPRESSION=Node.GetChildTreeNodeBySymbolName(NAME_EXPRESSION,0);

			// Zisti Type pre EXPRESSION.
			CParseTreeNodeData_Type						TypeEXPRESSION=EXPRESSION.GetTreeNodeData<CParseTreeNodeData_Type>();

			if (TypeVARIABLE!=null && TypeEXPRESSION!=null)
			{
				// Porovna TYPE pre VARIABLE a EXPRESSION ci su zhodne a posunie TYPE do PARENT NODE.
				if (TypeVARIABLE.SymbolType==TypeEXPRESSION.SymbolType)
				{
					if (TypeVARIABLE.SymbolType==ESymbolType.E_ST_INT && TypeEXPRESSION.SymbolType==ESymbolType.E_ST_INT)
					{
						CParseTreeNodeData_Type			TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_INT);

						Node.SetTreeNodeData(TreeNodeData);
					}
					else if (TypeVARIABLE.SymbolType==ESymbolType.E_ST_STRING && TypeEXPRESSION.SymbolType==ESymbolType.E_ST_STRING)
					{
						CParseTreeNodeData_Type			TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_STRING);

						Node.SetTreeNodeData(TreeNodeData);
					}
					// !!! Priradenie CELEHO ARRAY NIE JE PODPOROVANE.
					else
					{
						CParseTreeNodeData_Type			TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_ERROR);

						Node.SetTreeNodeData(TreeNodeData);

						CSemanticError					SemanticError=new CSemanticError(string.Format("VARIABLE [{0}] ASSIGMENT CONTAINS UNSUPPORTED TYPE !",TreeNodeID.Token.Lexema),TreeNodeID.Token);

						MSemanticErrors.Add(SemanticError);
					}
				}
				else
				{
					CParseTreeNodeData_Type				TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_ERROR);

					Node.SetTreeNodeData(TreeNodeData);

					CSemanticError						SemanticError=new CSemanticError(string.Format("VARIABLE [{0}] ASSIGMENT CONTAINS DIFFERENT TYPE on RIGHT SIDE as VARIABLE TYPE !",TreeNodeID.Token.Lexema),TreeNodeID.Token);

					MSemanticErrors.Add(SemanticError);
				}
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain TYPE INFORMATION !",TreeNodeID.Token.Lexema)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT].
		private void TraversePostOrderAction_SELECTION_STATEMENT_Choice1(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - SELECTION_STATEMENT_Choice1 POST !");

			CParseTreeNode								TERMINAL_IF=Node.GetChildTreeNodeBySymbolName(NAME_TERMINAL_IF,0);
			CParseTreeNode								EXPRESSION=Node.GetChildTreeNodeBySymbolName(NAME_EXPRESSION,0);

			// Zisti Type pre EXPRESSION.
			CParseTreeNodeData_Type						Type=EXPRESSION.GetTreeNodeData<CParseTreeNodeData_Type>();
			
			if (Type!=null)
			{
				// TYPE EXPRESSION MUSI byt INT.
				if (Type.SymbolType!=ESymbolType.E_ST_INT)
				{
					CSemanticError						SemanticError=new CSemanticError(string.Format("IF EXPRESSION has NOT CORRECT TYPE !"),TERMINAL_IF.Token);

					MSemanticErrors.Add(SemanticError);
				}
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain TYPE INFORMATION !",Node)));
			}

			CParseTreeNode								STATEMENT=Node.GetChildTreeNodeBySymbolName(NAME_STATEMENT,0);

			// Zisti ReturnType pre STATEMENT.
			CParseTreeNodeData_ReturnType				ReturnType=STATEMENT.GetTreeNodeData<CParseTreeNodeData_ReturnType>();

			// Ak je ReturnType nastaveny, posunie ho vyssie v TREE.
			if (ReturnType!=null)
			{
				CParseTreeNodeData_ReturnType			NewReturnType=new CParseTreeNodeData_ReturnType(ReturnType.SymbolType,ReturnType.Token);

				Node.SetTreeNodeData(NewReturnType);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT].
		private void TraversePostOrderAction_SELECTION_STATEMENT_Choice2(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - SELECTION_STATEMENT_Choice2 POST !");

			CParseTreeNode								TERMINAL_IF=Node.GetChildTreeNodeBySymbolName(NAME_TERMINAL_IF,0);
			CParseTreeNode								EXPRESSION=Node.GetChildTreeNodeBySymbolName(NAME_EXPRESSION,0);

			// Zisti Type pre EXPRESSION.
			CParseTreeNodeData_Type						TypeEXPRESSION=EXPRESSION.GetTreeNodeData<CParseTreeNodeData_Type>();

			if (TypeEXPRESSION!=null)
			{
				// TYPE EXPRESSION MUSI byt INT.
				if (TypeEXPRESSION.SymbolType!=ESymbolType.E_ST_INT)
				{
					CSemanticError						SemanticError=new CSemanticError(string.Format("IF EXPRESSION has NOT CORRECT TYPE !"),TERMINAL_IF.Token);

					MSemanticErrors.Add(SemanticError);
				}
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain TYPE INFORMATION !",Node)));
			}

			CParseTreeNode								STATEMENT1=Node.GetChildTreeNodeBySymbolName(NAME_STATEMENT,0);

			// Zisti ReturnType pre IF-STATEMENT.
			CParseTreeNodeData_ReturnType				ReturnTypeSTATEMENT1=STATEMENT1.GetTreeNodeData<CParseTreeNodeData_ReturnType>();

			// Zisti HasReturn pre IF-STATEMENT.
			CParseTreeNodeData_HasReturn				HasReturnSTATEMENT1=STATEMENT1.GetTreeNodeData<CParseTreeNodeData_HasReturn>();

			CParseTreeNode								STATEMENT2=Node.GetChildTreeNodeBySymbolName(NAME_STATEMENT,1);

			// Zisti ReturnType pre ELSE-STATEMENT.
			CParseTreeNodeData_ReturnType				ReturnTypeSTATEMENT2=STATEMENT2.GetTreeNodeData<CParseTreeNodeData_ReturnType>();

			// Zisti HasReturn pre ELSE-STATEMENT.
			CParseTreeNodeData_HasReturn				HasReturnSTATEMENT2=STATEMENT2.GetTreeNodeData<CParseTreeNodeData_HasReturn>();

			if (ReturnTypeSTATEMENT1!=null && ReturnTypeSTATEMENT2!=null)
			{
				// Porovna ci ReturnType pre IF-STATEMENT a ELSE-STATEMENT su zhodne.
				if (ReturnTypeSTATEMENT1.SymbolType==ReturnTypeSTATEMENT2.SymbolType)
				{
					CParseTreeNodeData_ReturnType		ReturnType=new CParseTreeNodeData_ReturnType(ReturnTypeSTATEMENT1.SymbolType,ReturnTypeSTATEMENT1.Token);

					Node.SetTreeNodeData(ReturnType);
				}
				else
				{
					CParseTreeNodeData_ReturnType		ReturnType=new CParseTreeNodeData_ReturnType(ESymbolType.E_ST_ERROR,ReturnTypeSTATEMENT2.Token);

					Node.SetTreeNodeData(ReturnType);

					CSemanticError						SemanticError=new CSemanticError(string.Format("IF and ELSE STATEMENTS contain RETURN VALUES with DIFFERENT TYPES !"),TERMINAL_IF.Token);

					MSemanticErrors.Add(SemanticError);
				}
			}
			else if (ReturnTypeSTATEMENT1!=null && ReturnTypeSTATEMENT2==null)
			{
				CParseTreeNodeData_ReturnType			ReturnType=new CParseTreeNodeData_ReturnType(ReturnTypeSTATEMENT1.SymbolType,ReturnTypeSTATEMENT1.Token);

				Node.SetTreeNodeData(ReturnType);
			}
			else if (ReturnTypeSTATEMENT1==null && ReturnTypeSTATEMENT2!=null)
			{
				CParseTreeNodeData_ReturnType			ReturnType=new CParseTreeNodeData_ReturnType(ReturnTypeSTATEMENT2.SymbolType,ReturnTypeSTATEMENT2.Token);

				Node.SetTreeNodeData(ReturnType);
			}

			// !!! Ak IF aj ELSE blok maju OBE HasReturn ATTRIBUTE, tak je nastaveny i na PARENT NODE - pretoze IBA VTEDY je ISTOTA, ze IF aj ELSE bloky URCITE MAJU RETURN_STATEMENT.
			if (HasReturnSTATEMENT1!=null && HasReturnSTATEMENT2!=null)
			{
				CParseTreeNodeData_HasReturn			HasReturn=new CParseTreeNodeData_HasReturn();

				Node.SetTreeNodeData(HasReturn);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT].
		private void TraversePostOrderAction_ITERATION_STATEMENT(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - ITERATION_STATEMENT POST !");

			CParseTreeNode								TERMINAL_WHILE=Node.GetChildTreeNodeBySymbolName(NAME_TERMINAL_WHILE,0);
			CParseTreeNode								EXPRESSION=Node.GetChildTreeNodeBySymbolName(NAME_EXPRESSION,0);

			// Zisti Type pre EXPRESSION.
			CParseTreeNodeData_Type						Type=EXPRESSION.GetTreeNodeData<CParseTreeNodeData_Type>();

			if (Type!=null)
			{
				// TYPE EXPRESSION MUSI byt INT.
				if (Type.SymbolType!=ESymbolType.E_ST_INT)
				{
					CSemanticError						SemanticError=new CSemanticError(string.Format("WHILE EXPRESSION has NOT CORRECT TYPE !"),TERMINAL_WHILE.Token);

					MSemanticErrors.Add(SemanticError);
				}
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain TYPE INFORMATION !",Node)));
			}

			CParseTreeNode								STATEMENT=Node.GetChildTreeNodeBySymbolName(NAME_STATEMENT,0);

			// Zisti ReturnType pre EXPRESSION.
			CParseTreeNodeData_ReturnType				ReturnTypeSTATEMENT=STATEMENT.GetTreeNodeData<CParseTreeNodeData_ReturnType>();

			if (ReturnTypeSTATEMENT!=null)
			{
				// Posunie ReturnType do PARENT NODE, aby mohol byt porovany s RETURN VALUE FUNCTION.
				CParseTreeNodeData_ReturnType			ReturnType=new CParseTreeNodeData_ReturnType(ReturnTypeSTATEMENT.SymbolType,ReturnTypeSTATEMENT.Token);

				Node.SetTreeNodeData(ReturnType);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [RETURN_STATEMENT -> return;].
		private void TraversePostOrderAction_RETURN_STATEMENT_Choice1(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - RETURN_STATEMENT_Choice1 POST !");

			CParseTreeNode								TERMINAL_RETURN=Node.GetChildTreeNodeBySymbolName(NAME_TERMINAL_RETURN,0);

			// Vytvori ReturnType a nastavi RETURN TYPE na VOID.
			CParseTreeNodeData_ReturnType			TreeNodeDataReturnType=new CParseTreeNodeData_ReturnType(ESymbolType.E_ST_VOID,TERMINAL_RETURN.Token);

			Node.SetTreeNodeData(TreeNodeDataReturnType);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [RETURN_STATEMENT -> return(EXPRESSION);].
		private void TraversePostOrderAction_RETURN_STATEMENT_Choice2(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - RETURN_STATEMENT_Choice2 POST !");

			CParseTreeNode								TERMINAL_RETURN=Node.GetChildTreeNodeBySymbolName(NAME_TERMINAL_RETURN,0);
			CParseTreeNode								EXPRESSION=Node.GetChildTreeNodeBySymbolName(NAME_EXPRESSION,0);

			// Zisti Type pre EXPRESSION.
			CParseTreeNodeData_Type						Type=EXPRESSION.GetTreeNodeData<CParseTreeNodeData_Type>();

			if (Type!=null)
			{
				// Vytvori ReturnType s RETURN VALUE obsahujucou TYPE daneho EXPRESSION a posunie ho do PARENT NODE.
				CParseTreeNodeData_ReturnType			TreeNodeDataReturnType=new CParseTreeNodeData_ReturnType(Type.SymbolType,TERMINAL_RETURN.Token);

				// Vytvori HasReturn a posunie ho do PARENT NODE.
				CParseTreeNodeData_HasReturn			TreeNodeDataHasReturn=new CParseTreeNodeData_HasReturn();

				Node.SetTreeNodeData(TreeNodeDataReturnType);
				Node.SetTreeNodeData(TreeNodeDataHasReturn);
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain TYPE INFORMATION !",Node)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION].
		private void TraversePostOrderAction_EXPRESSION_Choice1(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - EXPRESSION_Choice1 POST !");

			CParseTreeNode								ADDITIVE_EXPRESSION1=Node.GetChildTreeNodeBySymbolName(NAME_ADDITIVE_EXPRESSION,0);

			// Zisti Type pre ADDITIVE_EXPRESSION 1.
			CParseTreeNodeData_Type						TypeADDITIVE_EXPRESSION1=ADDITIVE_EXPRESSION1.GetTreeNodeData<CParseTreeNodeData_Type>();

			CParseTreeNode								ADDITIVE_EXPRESSION2=Node.GetChildTreeNodeBySymbolName(NAME_ADDITIVE_EXPRESSION,1);

			// Zisti Type pre ADDITIVE_EXPRESSION 2.
			CParseTreeNodeData_Type						TypeADDITIVE_EXPRESSION2=ADDITIVE_EXPRESSION2.GetTreeNodeData<CParseTreeNodeData_Type>();

			if (TypeADDITIVE_EXPRESSION1!=null && TypeADDITIVE_EXPRESSION2!=null)
			{
				// Porovna ci ADDITIVE_EXPRESSION 1 a ADDITIVE_EXPRESSION 2 maju rovnaky TYPE. Jediny povoleny TYPE je INT.
				if (TypeADDITIVE_EXPRESSION1.SymbolType==TypeADDITIVE_EXPRESSION2.SymbolType)
				{
					if (TypeADDITIVE_EXPRESSION1.SymbolType==ESymbolType.E_ST_INT && TypeADDITIVE_EXPRESSION2.SymbolType==ESymbolType.E_ST_INT)
					{
						// Ak je Type INT posunie ho do PARENT NODE.
						CParseTreeNodeData_Type			TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_INT);

						Node.SetTreeNodeData(TreeNodeData);
					}
					else
					{
						CParseTreeNodeData_Type			TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_ERROR);

						Node.SetTreeNodeData(TreeNodeData);

						CSemanticError					SemanticError=new CSemanticError(string.Format("SYMBOL [{0}] CONTAINS OPERANDS with SAME but NOT CORRECT TYPES !",Node.Symbol.Name),Node.Token);

						MSemanticErrors.Add(SemanticError);
					}
				}
				else
				{
					CParseTreeNodeData_Type				TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_ERROR);

					Node.SetTreeNodeData(TreeNodeData);

					CSemanticError						SemanticError=new CSemanticError(string.Format("SYMBOL [{0}] CONTAINS OPERANDS with DIFFERENT TYPES !",Node.Symbol.Name),Node.Token);

					MSemanticErrors.Add(SemanticError);
				}
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain TYPE INFORMATION !",Node)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [EXPRESSION -> ADDITIVE_EXPRESSION].
		private void TraversePostOrderAction_EXPRESSION_Choice2(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - EXPRESSION_Choice2 POST !");

			CParseTreeNode								ADDITIVE_EXPRESSION=Node.GetChildTreeNodeBySymbolName(NAME_ADDITIVE_EXPRESSION,0);

			// Zisti Type pre ADDITIVE_EXPRESSION.
			CParseTreeNodeData_Type						Type=ADDITIVE_EXPRESSION.GetTreeNodeData<CParseTreeNodeData_Type>();

			if (Type!=null)
			{
				// Posunie Type do PARENT NODE.
				CParseTreeNodeData_Type					TreeNodeData=new CParseTreeNodeData_Type(Type.SymbolType);

				Node.SetTreeNodeData(TreeNodeData);
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain TYPE INFORMATION !",Node)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM].
		private void TraversePostOrderAction_ADDITIVE_EXPRESSION_Choice1(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - ADDITIVE_EXPRESSION_Choice1 POST !");

			CParseTreeNode								ADDITIVE_EXPRESSION=Node.GetChildTreeNodeBySymbolName(NAME_ADDITIVE_EXPRESSION,0);

			// Zisti Type pre ADDITIVE_EXPRESSION.
			CParseTreeNodeData_Type						TypeADDITIVE_EXPRESSION=ADDITIVE_EXPRESSION.GetTreeNodeData<CParseTreeNodeData_Type>();

			CParseTreeNode								TERM=Node.GetChildTreeNodeBySymbolName(NAME_TERM,0);

			// Zisti Type pre TERM.
			CParseTreeNodeData_Type						TypeTERM=TERM.GetTreeNodeData<CParseTreeNodeData_Type>();

			CParseTreeNode								ADD_OPERATION=Node.GetChildTreeNodeBySymbolName(NAME_ADD_OPERATION,0);
			CParseTreeNode								PLUS=ADD_OPERATION.GetChildTreeNodeBySymbolNameOrNULL(NAME_TERMINAL_PLUS,0);
			bool										IsPlus=false;

			if (PLUS!=null)
			{
				IsPlus=true;
			}
			
			if (TypeADDITIVE_EXPRESSION!=null && TypeTERM!=null)
			{
				// Porovna ci ADDITIVE_EXPRESSION a TERM maju rovnaky TYPE.
				if (TypeADDITIVE_EXPRESSION.SymbolType==TypeTERM.SymbolType)
				{
					if (TypeADDITIVE_EXPRESSION.SymbolType==ESymbolType.E_ST_INT && TypeTERM.SymbolType==ESymbolType.E_ST_INT)
					{
						CParseTreeNodeData_Type			TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_INT);

						Node.SetTreeNodeData(TreeNodeData);
					}
					// !!!!! VYHODIL SOM TO. Bolo by to zlozite pri CODE GENERATION.
					// !!! Ak ADD_OPERATION je '+', tak i STRING je PODPOROVANY TYPE.
					else if (IsPlus==true && (TypeADDITIVE_EXPRESSION.SymbolType==ESymbolType.E_ST_STRING && TypeTERM.SymbolType==ESymbolType.E_ST_STRING))
					{
						CParseTreeNodeData_Type			TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_STRING);

						Node.SetTreeNodeData(TreeNodeData);
					}
					else
					{
						CParseTreeNodeData_Type			TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_ERROR);

						Node.SetTreeNodeData(TreeNodeData);

						// Ak by som chcel najst NOT NULL TOKEN (posledny parameter) s RIADKOM, kde chyba vznikla, musel by som prehladat CHILD NODES TREE.
						CSemanticError					SemanticError=new CSemanticError(string.Format("SYMBOL [{0}] CONTAINS OPERANDS with SAME but NOT CORRECT TYPES !",Node.Symbol.Name),Node.Token);

						MSemanticErrors.Add(SemanticError);
					}
				}
				else
				{
					CParseTreeNodeData_Type				TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_ERROR);

					Node.SetTreeNodeData(TreeNodeData);

					// Ak by som chcel najst NOT NULL TOKEN (posledny parameter) s RIADKOM, kde chyba vznikla, musel by som prehladat CHILD NODES TREE.
					CSemanticError						SemanticError=new CSemanticError(string.Format("SYMBOL [{0}] CONTAINS OPERANDS with DIFFERENT TYPES !",Node.Symbol.Name),Node.Token);

					MSemanticErrors.Add(SemanticError);
				}
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain TYPE INFORMATION !",Node)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [ADDITIVE_EXPRESSION -> TERM].
		private void TraversePostOrderAction_ADDITIVE_EXPRESSION_Choice2(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - ADDITIVE_EXPRESSION_Choice2 POST !");

			CParseTreeNode								TERM=Node.GetChildTreeNodeBySymbolName(NAME_TERM,0);

			// Zisti Type pre TERM.
			CParseTreeNodeData_Type						Type=TERM.GetTreeNodeData<CParseTreeNodeData_Type>();

			if (Type!=null)
			{
				// Posunie Type do PARENT NODE.
				CParseTreeNodeData_Type					TreeNodeData=new CParseTreeNodeData_Type(Type.SymbolType);

				Node.SetTreeNodeData(TreeNodeData);
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain TYPE INFORMATION !",Node)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [TERM -> TERM MUL_OPERATION FACTOR].
		private void TraversePostOrderAction_TERM_Choice1(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - TERM_Choice1 POST !");

			CParseTreeNode								TERM=Node.GetChildTreeNodeBySymbolName(NAME_TERM,0);

			// Zisti Type pre TERM.
			CParseTreeNodeData_Type						TypeTERM=TERM.GetTreeNodeData<CParseTreeNodeData_Type>();

			CParseTreeNode								FACTOR=Node.GetChildTreeNodeBySymbolName(NAME_FACTOR,0);

			// Zisti Type pre FACTOR.
			CParseTreeNodeData_Type						TypeFACTOR=FACTOR.GetTreeNodeData<CParseTreeNodeData_Type>();

			if (TypeTERM!=null && TypeFACTOR!=null)
			{
				// Porovna ci TERM a FACTOR maju rovnaky TYPE. Jediny povoleny TYPE je INT.
				if (TypeTERM.SymbolType==TypeFACTOR.SymbolType)
				{
					if (TypeTERM.SymbolType==ESymbolType.E_ST_INT && TypeFACTOR.SymbolType==ESymbolType.E_ST_INT)
					{
						// Ak je Type INT posunie ho do PARENT NODE.
						CParseTreeNodeData_Type			TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_INT);

						Node.SetTreeNodeData(TreeNodeData);
					}
					else
					{
						CParseTreeNodeData_Type			TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_ERROR);

						Node.SetTreeNodeData(TreeNodeData);

						// Ak by som chcel najst NOT NULL TOKEN (posledny parameter) s RIADKOM, kde chyba vznikla, musel by som prehladat CHILD NODES TREE.
						CSemanticError					SemanticError=new CSemanticError(string.Format("SYMBOL [{0}] CONTAINS OPERANDS with SAME but NOT CORRECT TYPES !",Node.Symbol.Name),Node.Token);

						MSemanticErrors.Add(SemanticError);
					}
				}
				else
				{
					CParseTreeNodeData_Type				TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_ERROR);

					Node.SetTreeNodeData(TreeNodeData);

					// Ak by som chcel najst NOT NULL TOKEN (posledny parameter) s RIADKOM, kde chyba vznikla, musel by som prehladat CHILD NODES TREE.
					CSemanticError						SemanticError=new CSemanticError(string.Format("SYMBOL [{0}] CONTAINS OPERANDS with DIFFERENT TYPES !",Node.Symbol.Name),Node.Token);

					MSemanticErrors.Add(SemanticError);
				}
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain TYPE INFORMATION !",Node)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [TERM -> FACTOR].
		private void TraversePostOrderAction_TERM_Choice2(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - TERM_Choice2 POST !");

			CParseTreeNode								FACTOR=Node.GetChildTreeNodeBySymbolName(NAME_FACTOR,0);

			// Zisti Type pre FACTOR.
			CParseTreeNodeData_Type						Type=FACTOR.GetTreeNodeData<CParseTreeNodeData_Type>();

			if (Type!=null)
			{
				// Posunie Type do PARENT NODE.
				CParseTreeNodeData_Type					TreeNodeData=new CParseTreeNodeData_Type(Type.SymbolType);

				Node.SetTreeNodeData(TreeNodeData);
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain TYPE INFORMATION !",Node)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [FACTOR -> (EXPRESSION)].
		private void TraversePostOrderAction_FACTOR_Choice1(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - FACTOR_Choice1 POST !");

			CParseTreeNode								EXPRESSION=Node.GetChildTreeNodeBySymbolName(NAME_EXPRESSION,0);

			// Zisti Type pre EXPRESSION.
			CParseTreeNodeData_Type						Type=EXPRESSION.GetTreeNodeData<CParseTreeNodeData_Type>();

			if (Type!=null)
			{
				// Posunie Type do PARENT NODE.
				CParseTreeNodeData_Type					TreeNodeData=new CParseTreeNodeData_Type(Type.SymbolType);

				Node.SetTreeNodeData(TreeNodeData);
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain TYPE INFORMATION !",Node)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [FACTOR -> VARIABLE].
		private void TraversePostOrderAction_FACTOR_Choice2(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - FACTOR_Choice2 POST !");

			CParseTreeNode								VARIABLE=Node.GetChildTreeNodeBySymbolName(NAME_VARIABLE,0);

			// Zisti Type pre VARIABLE.
			CParseTreeNodeData_Type						Type=VARIABLE.GetTreeNodeData<CParseTreeNodeData_Type>();

			if (Type!=null)
			{
				// Posunie Type do PARENT NODE.
				CParseTreeNodeData_Type					TreeNodeData=new CParseTreeNodeData_Type(Type.SymbolType);

				Node.SetTreeNodeData(TreeNodeData);
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain TYPE INFORMATION !",Node)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [FACTOR -> CALL].
		private void TraversePostOrderAction_FACTOR_Choice3(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - FACTOR_Choice3 POST !");

			CParseTreeNode								CALL=Node.GetChildTreeNodeBySymbolName(NAME_CALL,0);

			// Zisti Type pre CALL.
			CParseTreeNodeData_Type						Type=CALL.GetTreeNodeData<CParseTreeNodeData_Type>();

			if (Type!=null)
			{
				// Posunie Type do PARENT NODE.
				CParseTreeNodeData_Type					TreeNodeData=new CParseTreeNodeData_Type(Type.SymbolType);

				Node.SetTreeNodeData(TreeNodeData);
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain TYPE INFORMATION !",Node)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [FACTOR -> num].
		private void TraversePostOrderAction_FACTOR_Choice4(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - FACTOR_Choice4 POST !");

			// Vytvori Type s hodnotu INT.
			CParseTreeNodeData_Type						TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_INT);

			// Posunie Type do PARENT NODE.
			Node.SetTreeNodeData(TreeNodeData);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [FACTOR -> string_literal].
		private void TraversePostOrderAction_FACTOR_Choice5(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - FACTOR_Choice5 POST !");

			CParseTreeNode								STRING_LITERAL=Node.GetChildTreeNodeBySymbolName(NAME_STRING_LITERAL,0);
			CToken										Token=STRING_LITERAL.Token;
			string										StringLiteral=Token.Lexema;

			MStringLiterals.Add(StringLiteral);

			// Vytvori Type s hodnotu STRING.
			CParseTreeNodeData_Type						TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_STRING);

			// Posunie Type do PARENT NODE.
			Node.SetTreeNodeData(TreeNodeData);

			if (IsValidLiteral(StringLiteral)==false)
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("LIETERAL contains INVALID ESCAPE SEQUENCE !"),STRING_LITERAL.Token);

				MSemanticErrors.Add(SemanticError);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [CALL -> id(ARGS)].
		private void TraversePostOrderAction_CALL(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - CALL POST !");

			CParseTreeNode								ARGS=Node.GetChildTreeNodeBySymbolName(NAME_ARGS,0);

			// Zisti ParamTypes pre ARGS.
			CParseTreeNodeData_ParamTypes				ParamTypes=ARGS.GetTreeNodeData<CParseTreeNodeData_ParamTypes>();

			if (ParamTypes!=null)
			{
				CParseTreeNodeData_Type[]				FunctionParamTypes=ParamTypes.ParamTypes;
				CParseTreeNode							TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
				CToken_Identifier						TokenID=(CToken_Identifier) TreeNodeID.Token;
				string									SymbolName=TokenID.Lexema;

				// Ziska MENO FUNCTION.
				if (MCurrentTable.ContainsSymbolInCurrentOrParentScopes(SymbolName)==true)
				{
					CSymbolTableItem					SymbolFromSymbolTable=MCurrentTable.GetSymbolFromCurrentOrParentScopes(SymbolName);

					// Zisti ci 'id' reprezentuje FUNCTION.
					if ((SymbolFromSymbolTable.SymbolTableData is CSymbolTableData_Function)==true)
					{
						CSymbolTable_FunctionDeclaration	FunctionTable=MCurrentTable.GetFunctionSymbolTable(SymbolName);

						if (FunctionTable!=null)
						{
							CSymbolTableData_Function	TypedSymbolFromSymbolTable=(CSymbolTableData_Function) SymbolFromSymbolTable.SymbolTableData;

							// Zisti RETURN TYPE pre FUNCTION.
							ESymbolType					SymbolType=TypedSymbolFromSymbolTable.FunctionReturnType;

							// Nastavi Type ATTRIBUTE na RETURN TYPE FUNCTION, ktory vracia operacia volania FUNCTION.
							CParseTreeNodeData_Type		TreeNodeData=new CParseTreeNodeData_Type(SymbolType);

							Node.SetTreeNodeData(TreeNodeData);

							CSymbolTableData_Param[]	Params=FunctionTable.GetParamTypes();

							// Skontroluje pocet parametrov v DEKLARACII FUNCTION a jej volani.
							if (FunctionParamTypes.Length==Params.Length)
							{
								// Skontroluje TYPE vsetkych parametrov v DEKLARACII FUNCTION a jej volani.
								for (int i=0;i<FunctionParamTypes.Length;i++)
								{
									ESymbolType			FunctionType=FunctionParamTypes[i].SymbolType;
									ESymbolType			ParamType=Params[i].SymbolType;

									if (FunctionType!=ParamType)
									{
										CSemanticError	SemanticError=new CSemanticError(string.Format("{0}. PARAMETER in FUNCTION [{1}] has TYPE [{2}] but EXCPECTED TYPE is [{3}] !",(i+1),SymbolName,ParamType,FunctionType),TreeNodeID.Token);

										MSemanticErrors.Add(SemanticError);
									}
								}
							}
							else
							{
								CSemanticError			SemanticError=new CSemanticError(string.Format("FUNCTION [{0}] CONTAINS [{1}] PARAMS but REQUIRES [{2}] PARAMS !",SymbolName,FunctionParamTypes.Length,Params.Length),TreeNodeID.Token);

								MSemanticErrors.Add(SemanticError);
							}
						}
						else
						{
							throw(new InvalidOperationException(string.Format("Can't FIND FUNCTION TABLE for FUNCTION [{0}] !",SymbolName)));
						}
					}
					else
					{
						CParseTreeNodeData_Type			TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_ERROR);

						Node.SetTreeNodeData(TreeNodeData);

						CSemanticError					SemanticError=new CSemanticError(string.Format("SYMBOL [{0}] is NOT FUNCTION !",SymbolName),TreeNodeID.Token);

						MSemanticErrors.Add(SemanticError);
					}
				}
				else
				{
					CParseTreeNodeData_Type				TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_ERROR);

					Node.SetTreeNodeData(TreeNodeData);

					CSemanticError						SemanticError=new CSemanticError(string.Format("FUNCTION [{0}] is NOT DECLARED in SCOPE !",SymbolName),TreeNodeID.Token);

					MSemanticErrors.Add(SemanticError);
				}
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain PARAM TYPES INFORMATION !",Node)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [ARGS -> ARG_LIST].
		private void TraversePostOrderAction_ARGS_Choice1(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - ARGS_Choice1 POST !");

			CParseTreeNode								ARG_LIST=Node.GetChildTreeNodeBySymbolName(NAME_ARG_LIST,0);

			// Zisti ParamTypes pre ARG_LIST.
			CParseTreeNodeData_ParamTypes				ParamTypes=ARG_LIST.GetTreeNodeData<CParseTreeNodeData_ParamTypes>();

			if (ParamTypes!=null)
			{
				// Posunie ParamTypes do PARENT NODE.
				CParseTreeNodeData_ParamTypes			TreeNodeDataARG_LIST=new CParseTreeNodeData_ParamTypes(ParamTypes);

				Node.SetTreeNodeData(TreeNodeDataARG_LIST);
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain PARAM TYPES INFORMATION !",Node)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [ARGS -> ɛ].
		private void TraversePostOrderAction_ARGS_Choice2(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - ARGS_Choice2 POST !");

			// Vytvori PRAZDY ParamTypes.
			CParseTreeNodeData_ParamTypes				ParamTypes=new CParseTreeNodeData_ParamTypes();

			Node.SetTreeNodeData(ParamTypes);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [ARG_LIST -> ARG_LIST,EXPRESSION].
		private void TraversePostOrderAction_ARG_LIST_Choice1(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - ARG_LIST_Choice1 POST !");

			CParseTreeNode								EXPRESSION=Node.GetChildTreeNodeBySymbolName(NAME_EXPRESSION,0);

			// Zisti Type pre EXPRESSION.
			CParseTreeNodeData_Type						TypeEXPRESSION=EXPRESSION.GetTreeNodeData<CParseTreeNodeData_Type>();

			CParseTreeNode								ARG_LIST=Node.GetChildTreeNodeBySymbolName(NAME_ARG_LIST,0);

			// Zisti ParamTypes pre ARG_LIST.
			CParseTreeNodeData_ParamTypes				ParamTypesARG_LIST=ARG_LIST.GetTreeNodeData<CParseTreeNodeData_ParamTypes>();

			if (TypeEXPRESSION!=null && ParamTypesARG_LIST!=null)
			{
				// Prida Type EXPRESSION, reprezentujuci nasledujuci parameter FUNCTION na koniec POLA ParamTypes, ktory reprezentuje ostatne parametre FUNCTION.
				CParseTreeNodeData_Type					TreeNodeDataEXPRESSION=new CParseTreeNodeData_Type(TypeEXPRESSION.SymbolType);
				CParseTreeNodeData_ParamTypes			TreeNodeDataARG_LIST=new CParseTreeNodeData_ParamTypes(ParamTypesARG_LIST,TreeNodeDataEXPRESSION);

				Node.SetTreeNodeData(TreeNodeDataARG_LIST);
			}
			// Parametre Type a ParamTypes su POVINNE.
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain TYPE or PARAM TYPES INFORMATION !",Node)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [ARG_LIST -> EXPRESSION].
		private void TraversePostOrderAction_ARG_LIST_Choice2(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - ARG_LIST_Choice2 POST !");

			CParseTreeNode								EXPRESSION=Node.GetChildTreeNodeBySymbolName(NAME_EXPRESSION,0);

			// Zisti Type pre EXPRESSION.
			CParseTreeNodeData_Type						Type=EXPRESSION.GetTreeNodeData<CParseTreeNodeData_Type>();

			if (Type!=null)
			{
				// Vytvori novy ParamTypes do ktoreho prida Type EXPRESSION reprezentujuci paramter FUNCTION.
				CParseTreeNodeData_Type					TreeNodeDataEXPRESSION=new CParseTreeNodeData_Type(Type.SymbolType);
				CParseTreeNodeData_ParamTypes			TreeNodeDataARG_LIST=new CParseTreeNodeData_ParamTypes(TreeNodeDataEXPRESSION);

				Node.SetTreeNodeData(TreeNodeDataARG_LIST);
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain PARAM TYPES INFORMATION !",Node)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [CONST -> num].
		private void TraversePostOrderAction_CONST_Choice1(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - CONST_Choice1 POST !");

			// Vytvori Type s hodnotu INT.
			CParseTreeNodeData_Type						TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_INT);

			// Posunie Type do PARENT NODE.
			Node.SetTreeNodeData(TreeNodeData);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [CONST -> string_literal].
		private void TraversePostOrderAction_CONST_Choice2(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			MLog.AppendLine("TYPE CHECKER - CONST_Choice2 POST !");

			CParseTreeNode								STRING_LITERAL=Node.GetChildTreeNodeBySymbolName(NAME_STRING_LITERAL,0);
			CToken										Token=STRING_LITERAL.Token;
			string										StringLiteral=Token.Lexema;

			MStringLiterals.Add(StringLiteral);

			// Vytvori Type s hodnotu STRING.
			CParseTreeNodeData_Type						TreeNodeData=new CParseTreeNodeData_Type(ESymbolType.E_ST_STRING);

			// Posunie Type do PARENT NODE.
			Node.SetTreeNodeData(TreeNodeData);

			if (IsValidLiteral(StringLiteral)==false)
			{
				CSemanticError							SemanticError=new CSemanticError(string.Format("LIETERAL contains INVALID ESCAPE SEQUENCE !"),STRING_LITERAL.Token);

				MSemanticErrors.Add(SemanticError);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParseTreeTraverseItemList CreateTraverseItemList(CNonterminalCollection NonterminalCollection)
		{
			MLog.Clear();
			MCurrentTable.ResetChildScopeTableIndex();
			MStringLiterals.Clear();

			CChoice										Choice_VARIABLE_DECLARATION_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="VARIABLE_DECLARATION").First().Choices[1];
			CChoice										Choice_VARIABLE_DECLARATION_Choice3=NonterminalCollection.Nonterminals.Where(P => P.Name=="VARIABLE_DECLARATION").First().Choices[2];
			CChoice										Choice_FUNCTION_DECLARATION=NonterminalCollection.Nonterminals.Where(P => P.Name=="FUNCTION_DECLARATION").First().Choices[0];
			CChoice										Choice_COMPOUND_STATEMENT=NonterminalCollection.Nonterminals.Where(P => P.Name=="COMPOUND_STATEMENT").First().Choices[0];
			CChoice										Choice_STATEMENT_LIST_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="STATEMENT_LIST").First().Choices[0];
			CChoice										Choice_STATEMENT_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="STATEMENT").First().Choices[1];
			CChoice										Choice_STATEMENT_Choice3=NonterminalCollection.Nonterminals.Where(P => P.Name=="STATEMENT").First().Choices[2];
			CChoice										Choice_STATEMENT_Choice4=NonterminalCollection.Nonterminals.Where(P => P.Name=="STATEMENT").First().Choices[3];
			CChoice										Choice_STATEMENT_Choice5=NonterminalCollection.Nonterminals.Where(P => P.Name=="STATEMENT").First().Choices[4];
			CChoice										Choice_EXPRESSION_STATEMENT_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="EXPRESSION_STATEMENT").First().Choices[0];
			CChoice										Choice_SELECTION_STATEMENT_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="SELECTION_STATEMENT").First().Choices[0];
			CChoice										Choice_SELECTION_STATEMENT_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="SELECTION_STATEMENT").First().Choices[1];
			CChoice										Choice_ITERATION_STATEMENT=NonterminalCollection.Nonterminals.Where(P => P.Name=="ITERATION_STATEMENT").First().Choices[0];
			CChoice										Choice_RETURN_STATEMENT_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="RETURN_STATEMENT").First().Choices[0];
			CChoice										Choice_RETURN_STATEMENT_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="RETURN_STATEMENT").First().Choices[1];
			CChoice										Choice_VARIABLE_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="VARIABLE").First().Choices[0];
			CChoice										Choice_VARIABLE_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="VARIABLE").First().Choices[1];
			CChoice										Choice_EXPRESSION_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="EXPRESSION").First().Choices[0];
			CChoice										Choice_EXPRESSION_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="EXPRESSION").First().Choices[1];
			CChoice										Choice_ADDITIVE_EXPRESSION_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="ADDITIVE_EXPRESSION").First().Choices[0];
			CChoice										Choice_ADDITIVE_EXPRESSION_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="ADDITIVE_EXPRESSION").First().Choices[1];
			CChoice										Choice_TERM_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="TERM").First().Choices[0];
			CChoice										Choice_TERM_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="TERM").First().Choices[1];
			CChoice										Choice_FACTOR_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="FACTOR").First().Choices[0];
			CChoice										Choice_FACTOR_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="FACTOR").First().Choices[1];
			CChoice										Choice_FACTOR_Choice3=NonterminalCollection.Nonterminals.Where(P => P.Name=="FACTOR").First().Choices[2];
			CChoice										Choice_FACTOR_Choice4=NonterminalCollection.Nonterminals.Where(P => P.Name=="FACTOR").First().Choices[3];
			CChoice										Choice_FACTOR_Choice5=NonterminalCollection.Nonterminals.Where(P => P.Name=="FACTOR").First().Choices[4];
			CChoice										Choice_CALL=NonterminalCollection.Nonterminals.Where(P => P.Name=="CALL").First().Choices[0];
			CChoice										Choice_ARGS_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="ARGS").First().Choices[0];
			CChoice										Choice_ARGS_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="ARGS").First().Choices[1];
			CChoice										Choice_ARG_LIST_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="ARG_LIST").First().Choices[0];
			CChoice										Choice_ARG_LIST_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="ARG_LIST").First().Choices[1];
			CChoice										Choice_CONST_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="CONST").First().Choices[0];
			CChoice										Choice_CONST_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="CONST").First().Choices[1];

			int[]										Order_VARIABLE_DECLARATION_Choice2=new int[]{0,1,2,3,4};
			int[]										Order_VARIABLE_DECLARATION_Choice3=new int[]{0,1,2,3,4,5};
			int[]										Order_FUNCTION_DECLARATION=new int[]{0,1,2,3,4,5};
			int[]										Order_COMPOUND_STATEMENT=new int[]{0,1,2,3};
			int[]										Order_STATEMENT_LIST_Choice1=new int[]{0,1};
			int[]										Order_STATEMENT_Choice2=new int[]{0};
			int[]										Order_STATEMENT_Choice3=new int[]{0};
			int[]										Order_STATEMENT_Choice4=new int[]{0};
			int[]										Order_STATEMENT_Choice5=new int[]{0};
			int[]										Order_EXPRESSION_STATEMENT_Choice1=new int[]{0,1,2,3};
			int[]										Order_SELECTION_STATEMENT_Choice1=new int[]{0,1,2,3,4};
			int[]										Order_SELECTION_STATEMENT_Choice2=new int[]{0,1,2,3,4,5,6};
			int[]										Order_ITERATION_STATEMENT=new int[]{0,1,2,3,4};
			int[]										Order_RETURN_STATEMENT_Choice1=new int[]{0,1};
			int[]										Order_RETURN_STATEMENT_Choice2=new int[]{0,1,2,3,4};
			int[]										Order_VARIABLE_Choice1=new int[]{0};
			int[]										Order_VARIABLE_Choice2=new int[]{0,1,2,3};
			int[]										Order_EXPRESSION_Choice1=new int[]{0,1,2};
			int[]										Order_EXPRESSION_Choice2=new int[]{0};
			int[]										Order_TERM_Choice1=new int[]{0,1,2};
			int[]										Order_TERM_Choice2=new int[]{0};
			int[]										Order_ADDITIVE_EXPRESSION_Choice1=new int[]{0,1,2};
			int[]										Order_ADDITIVE_EXPRESSION_Choice2=new int[]{0};
			int[]										Order_FACTOR_Choice1=new int[]{0,1,2};
			int[]										Order_FACTOR_Choice2=new int[]{0};
			int[]										Order_FACTOR_Choice3=new int[]{0};
			int[]										Order_FACTOR_Choice4=new int[]{0};
			int[]										Order_FACTOR_Choice5=new int[]{0};
			int[]										Order_CALL=new int[]{0,1,2,3};
			int[]										Order_ARGS_Choice1=new int[]{0};
			int[]										Order_ARGS_Choice2=new int[]{0};
			int[]										Order_ARG_LIST_Choice1=new int[]{0,1,2};
			int[]										Order_ARG_LIST_Choice2=new int[]{0};
			int[]										Order_CONST_Choice1=new int[]{0};
			int[]										Order_CONST_Choice2=new int[]{0};

			CParseTreeTraverseItem						PTTI_VARIABLE_DECLARATION_Choice2=new CParseTreeTraverseItem(Choice_VARIABLE_DECLARATION_Choice2,null,TraversePostOrderAction_VARIABLE_DECLARATION_Choice2,Order_VARIABLE_DECLARATION_Choice2);
			CParseTreeTraverseItem						PTTI_VARIABLE_DECLARATION_Choice3=new CParseTreeTraverseItem(Choice_VARIABLE_DECLARATION_Choice3,null,TraversePostOrderAction_VARIABLE_DECLARATION_Choice3,Order_VARIABLE_DECLARATION_Choice3);
			CParseTreeTraverseItem						PTTI_FUNCTION_DECLARATION=new CParseTreeTraverseItem(Choice_FUNCTION_DECLARATION,TraversePreOrderAction_FUNCTION_DECLARATION,TraversePostOrderAction_FUNCTION_DECLARATION,Order_FUNCTION_DECLARATION);
			CParseTreeTraverseItem						PTTI_COMPOUND_STATEMENT=new CParseTreeTraverseItem(Choice_COMPOUND_STATEMENT,TraversePreOrderAction_COMPOUND_STATEMENT,TraversePostOrderAction_COMPOUND_STATEMENT,Order_COMPOUND_STATEMENT);
			CParseTreeTraverseItem						PTTI_STATEMENT_LIST_Choice1=new CParseTreeTraverseItem(Choice_STATEMENT_LIST_Choice1,null,TraversePostOrderAction_STATEMENT_LIST_Choice1,Order_STATEMENT_LIST_Choice1);
			CParseTreeTraverseItem						PTTI_STATEMENT_Choice2=new CParseTreeTraverseItem(Choice_STATEMENT_Choice2,null,TraversePostOrderAction_STATEMENT_Choice2,Order_STATEMENT_Choice2);
			CParseTreeTraverseItem						PTTI_STATEMENT_Choice3=new CParseTreeTraverseItem(Choice_STATEMENT_Choice3,null,TraversePostOrderAction_STATEMENT_Choice3,Order_STATEMENT_Choice3);
			CParseTreeTraverseItem						PTTI_STATEMENT_Choice4=new CParseTreeTraverseItem(Choice_STATEMENT_Choice4,null,TraversePostOrderAction_STATEMENT_Choice4,Order_STATEMENT_Choice4);
			CParseTreeTraverseItem						PTTI_STATEMENT_Choice5=new CParseTreeTraverseItem(Choice_STATEMENT_Choice5,null,TraversePostOrderAction_STATEMENT_Choice5,Order_STATEMENT_Choice5);
			CParseTreeTraverseItem						PTTI_EXPRESSION_STATEMENT_Choice1=new CParseTreeTraverseItem(Choice_EXPRESSION_STATEMENT_Choice1,null,TraversePostOrderAction_EXPRESSION_STATEMENT_Choice1,Order_EXPRESSION_STATEMENT_Choice1);
			CParseTreeTraverseItem						PTTI_SELECTION_STATEMENT_Choice1=new CParseTreeTraverseItem(Choice_SELECTION_STATEMENT_Choice1,null,TraversePostOrderAction_SELECTION_STATEMENT_Choice1,Order_SELECTION_STATEMENT_Choice1);
			CParseTreeTraverseItem						PTTI_SELECTION_STATEMENT_Choice2=new CParseTreeTraverseItem(Choice_SELECTION_STATEMENT_Choice2,null,TraversePostOrderAction_SELECTION_STATEMENT_Choice2,Order_SELECTION_STATEMENT_Choice2);
			CParseTreeTraverseItem						PTTI_ITERATION_STATEMENT=new CParseTreeTraverseItem(Choice_ITERATION_STATEMENT,null,TraversePostOrderAction_ITERATION_STATEMENT,Order_ITERATION_STATEMENT);
			CParseTreeTraverseItem						PTTI_RETURN_STATEMENT_Choice1=new CParseTreeTraverseItem(Choice_RETURN_STATEMENT_Choice1,null,TraversePostOrderAction_RETURN_STATEMENT_Choice1,Order_RETURN_STATEMENT_Choice1);
			CParseTreeTraverseItem						PTTI_RETURN_STATEMENT_Choice2=new CParseTreeTraverseItem(Choice_RETURN_STATEMENT_Choice2,null,TraversePostOrderAction_RETURN_STATEMENT_Choice2,Order_RETURN_STATEMENT_Choice2);
			CParseTreeTraverseItem						PTTI_VARIABLE_Choice1=new CParseTreeTraverseItem(Choice_VARIABLE_Choice1,null,TraversePostOrderAction_VARIABLE_Choice1,Order_VARIABLE_Choice1);
			CParseTreeTraverseItem						PTTI_VARIABLE_Choice2=new CParseTreeTraverseItem(Choice_VARIABLE_Choice2,null,TraversePostOrderAction_VARIABLE_Choice2,Order_VARIABLE_Choice2);
			CParseTreeTraverseItem						PTTI_EXPRESSION_Choice1=new CParseTreeTraverseItem(Choice_EXPRESSION_Choice1,null,TraversePostOrderAction_EXPRESSION_Choice1,Order_EXPRESSION_Choice1);
			CParseTreeTraverseItem						PTTI_EXPRESSION_Choice2=new CParseTreeTraverseItem(Choice_EXPRESSION_Choice2,null,TraversePostOrderAction_EXPRESSION_Choice2,Order_EXPRESSION_Choice2);
			CParseTreeTraverseItem						PTTI_ADDITIVE_EXPRESSION_Choice1=new CParseTreeTraverseItem(Choice_ADDITIVE_EXPRESSION_Choice1,null,TraversePostOrderAction_ADDITIVE_EXPRESSION_Choice1,Order_ADDITIVE_EXPRESSION_Choice1);
			CParseTreeTraverseItem						PTTI_ADDITIVE_EXPRESSION_Choice2=new CParseTreeTraverseItem(Choice_ADDITIVE_EXPRESSION_Choice2,null,TraversePostOrderAction_ADDITIVE_EXPRESSION_Choice2,Order_ADDITIVE_EXPRESSION_Choice2);
			CParseTreeTraverseItem						PTTI_TERM_Choice1=new CParseTreeTraverseItem(Choice_TERM_Choice1,null,TraversePostOrderAction_TERM_Choice1,Order_TERM_Choice1);
			CParseTreeTraverseItem						PTTI_TERM_Choice2=new CParseTreeTraverseItem(Choice_TERM_Choice2,null,TraversePostOrderAction_TERM_Choice2,Order_TERM_Choice2);
			CParseTreeTraverseItem						PTTI_FACTOR_Choice1=new CParseTreeTraverseItem(Choice_FACTOR_Choice1,null,TraversePostOrderAction_FACTOR_Choice1,Order_FACTOR_Choice1);
			CParseTreeTraverseItem						PTTI_FACTOR_Choice2=new CParseTreeTraverseItem(Choice_FACTOR_Choice2,null,TraversePostOrderAction_FACTOR_Choice2,Order_FACTOR_Choice2);
			CParseTreeTraverseItem						PTTI_FACTOR_Choice3=new CParseTreeTraverseItem(Choice_FACTOR_Choice3,null,TraversePostOrderAction_FACTOR_Choice3,Order_FACTOR_Choice3);
			CParseTreeTraverseItem						PTTI_FACTOR_Choice4=new CParseTreeTraverseItem(Choice_FACTOR_Choice4,null,TraversePostOrderAction_FACTOR_Choice4,Order_FACTOR_Choice4);
			CParseTreeTraverseItem						PTTI_FACTOR_Choice5=new CParseTreeTraverseItem(Choice_FACTOR_Choice5,null,TraversePostOrderAction_FACTOR_Choice5,Order_FACTOR_Choice5);
			CParseTreeTraverseItem						PTTI_CALL=new CParseTreeTraverseItem(Choice_CALL,null,TraversePostOrderAction_CALL,Order_CALL);
			CParseTreeTraverseItem						PTTI_ARGS_Choice1=new CParseTreeTraverseItem(Choice_ARGS_Choice1,null,TraversePostOrderAction_ARGS_Choice1,Order_ARGS_Choice1);
			CParseTreeTraverseItem						PTTI_ARGS_Choice2=new CParseTreeTraverseItem(Choice_ARGS_Choice2,null,TraversePostOrderAction_ARGS_Choice2,Order_ARGS_Choice2);
			CParseTreeTraverseItem						PTTI_ARG_LIST_Choice1=new CParseTreeTraverseItem(Choice_ARG_LIST_Choice1,null,TraversePostOrderAction_ARG_LIST_Choice1,Order_ARG_LIST_Choice1);
			CParseTreeTraverseItem						PTTI_ARG_LIST_Choice2=new CParseTreeTraverseItem(Choice_ARG_LIST_Choice2,null,TraversePostOrderAction_ARG_LIST_Choice2,Order_ARG_LIST_Choice2);
			CParseTreeTraverseItem						PTTI_CONST_Choice1=new CParseTreeTraverseItem(Choice_CONST_Choice1,null,TraversePostOrderAction_CONST_Choice1,Order_CONST_Choice1);
			CParseTreeTraverseItem						PTTI_CONST_Choice2=new CParseTreeTraverseItem(Choice_CONST_Choice2,null,TraversePostOrderAction_CONST_Choice2,Order_CONST_Choice2);

			CParseTreeTraverseItemList					List=new CParseTreeTraverseItemList(DefaultPreOrderAction,null);

			List.AddTraverseItem(PTTI_VARIABLE_DECLARATION_Choice2);
			List.AddTraverseItem(PTTI_VARIABLE_DECLARATION_Choice3);
			List.AddTraverseItem(PTTI_FUNCTION_DECLARATION);
			List.AddTraverseItem(PTTI_COMPOUND_STATEMENT);
			List.AddTraverseItem(PTTI_STATEMENT_LIST_Choice1);
			List.AddTraverseItem(PTTI_STATEMENT_Choice2);
			List.AddTraverseItem(PTTI_STATEMENT_Choice3);
			List.AddTraverseItem(PTTI_STATEMENT_Choice4);
			List.AddTraverseItem(PTTI_STATEMENT_Choice5);
			List.AddTraverseItem(PTTI_EXPRESSION_STATEMENT_Choice1);
			List.AddTraverseItem(PTTI_SELECTION_STATEMENT_Choice1);
			List.AddTraverseItem(PTTI_SELECTION_STATEMENT_Choice2);
			List.AddTraverseItem(PTTI_ITERATION_STATEMENT);
			List.AddTraverseItem(PTTI_RETURN_STATEMENT_Choice1);
			List.AddTraverseItem(PTTI_RETURN_STATEMENT_Choice2);
			List.AddTraverseItem(PTTI_VARIABLE_Choice1);
			List.AddTraverseItem(PTTI_VARIABLE_Choice2);
			List.AddTraverseItem(PTTI_EXPRESSION_Choice1);
			List.AddTraverseItem(PTTI_EXPRESSION_Choice2);
			List.AddTraverseItem(PTTI_ADDITIVE_EXPRESSION_Choice1);
			List.AddTraverseItem(PTTI_ADDITIVE_EXPRESSION_Choice2);
			List.AddTraverseItem(PTTI_TERM_Choice1);
			List.AddTraverseItem(PTTI_TERM_Choice2);
			List.AddTraverseItem(PTTI_FACTOR_Choice1);
			List.AddTraverseItem(PTTI_FACTOR_Choice2);
			List.AddTraverseItem(PTTI_FACTOR_Choice3);
			List.AddTraverseItem(PTTI_FACTOR_Choice4);
			List.AddTraverseItem(PTTI_FACTOR_Choice5);
			List.AddTraverseItem(PTTI_CALL);
			List.AddTraverseItem(PTTI_ARGS_Choice1);
			List.AddTraverseItem(PTTI_ARGS_Choice2);
			List.AddTraverseItem(PTTI_ARG_LIST_Choice1);
			List.AddTraverseItem(PTTI_ARG_LIST_Choice2);
			List.AddTraverseItem(PTTI_CONST_Choice1);
			List.AddTraverseItem(PTTI_CONST_Choice2);

			return(List);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------