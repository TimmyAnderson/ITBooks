using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public static class CSyntaxTreeNodeFactory
	{
//-------------------------------------------------------------------------------------------------------
		public static CSyntaxTreeNode CreateParseTreeNode(CChoice Choice, CParsingStackItem[] ParsingStackItems)
		{
			if (Choice.Nonterminal.Name=="PROGRAM")
			{
				if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="DECLARATION_LIST")
				{
					CSyntaxTreeNode_PROGRAM					TreeNode=new CSyntaxTreeNode_PROGRAM(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="DECLARATION_LIST")
			{
				if (Choice.Symbols.Length==2 && Choice.Symbols[0].Name=="DECLARATION_LIST" && Choice.Symbols[1].Name=="DECLARATION")
				{
					CSyntaxTreeNode_DECLARATION_LIST			TreeNode=new CSyntaxTreeNode_DECLARATION_LIST(Choice,ParsingStackItems[0],ParsingStackItems[1]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="DECLARATION")
				{
					CSyntaxTreeNode_DECLARATION_LIST			TreeNode=new CSyntaxTreeNode_DECLARATION_LIST(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="DECLARATION")
			{
				if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="VARIABLE_DECLARATION")
				{
					CSyntaxTreeNode_DECLARATION				TreeNode=new CSyntaxTreeNode_DECLARATION(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="FUNCTION_DECLARATION")
				{
					CSyntaxTreeNode_DECLARATION				TreeNode=new CSyntaxTreeNode_DECLARATION(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="VARIABLE_DECLARATION")
			{
				if (Choice.Symbols.Length==3 && Choice.Symbols[0].Name=="TYPE_SPECIFIER" && Choice.Symbols[1].Name=="TerminalID" && Choice.Symbols[2].Name=="TerminalSemicolon")
				{
					CSyntaxTreeNode_VARIABLE_DECLARATION	TreeNode=new CSyntaxTreeNode_VARIABLE_DECLARATION(Choice,ParsingStackItems[0],ParsingStackItems[1]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==5 && Choice.Symbols[0].Name=="TYPE_SPECIFIER" && Choice.Symbols[1].Name=="TerminalID" && Choice.Symbols[2].Name=="TerminalAssigment" && Choice.Symbols[3].Name=="CONST" && Choice.Symbols[4].Name=="TerminalSemicolon")
				{
					CSyntaxTreeNode_VARIABLE_DECLARATION	TreeNode=new CSyntaxTreeNode_VARIABLE_DECLARATION(Choice,ParsingStackItems[0],ParsingStackItems[1],ParsingStackItems[3]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==6 && Choice.Symbols[0].Name=="TYPE_SPECIFIER" && Choice.Symbols[1].Name=="TerminalID" && Choice.Symbols[2].Name=="TerminalSquareBracketLeft" && Choice.Symbols[3].Name=="TerminalNumber" && Choice.Symbols[4].Name=="TerminalSquareBracketRight" && Choice.Symbols[5].Name=="TerminalSemicolon")
				{
					CSyntaxTreeNode_VARIABLE_DECLARATION	TreeNode=new CSyntaxTreeNode_VARIABLE_DECLARATION(Choice,ParsingStackItems[0],ParsingStackItems[1],ParsingStackItems[3]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="TYPE_SPECIFIER")
			{
				if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalINT")
				{
					CSyntaxTreeNode_TYPE_SPECIFIER			TreeNode=new CSyntaxTreeNode_TYPE_SPECIFIER(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalSTRING")
				{
					CSyntaxTreeNode_TYPE_SPECIFIER			TreeNode=new CSyntaxTreeNode_TYPE_SPECIFIER(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalVOID")
				{
					CSyntaxTreeNode_TYPE_SPECIFIER			TreeNode=new CSyntaxTreeNode_TYPE_SPECIFIER(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="FUNCTION_DECLARATION")
			{
				if (Choice.Symbols.Length==6 && Choice.Symbols[0].Name=="TYPE_SPECIFIER" && Choice.Symbols[1].Name=="TerminalID" && Choice.Symbols[2].Name=="TerminalRoundBracketLeft" && Choice.Symbols[3].Name=="PARAMS" && Choice.Symbols[4].Name=="TerminalRoundBracketRight" && Choice.Symbols[5].Name=="COMPOUND_STATEMENT")
				{
					CSyntaxTreeNode_FUNCTION_DECLARATION	TreeNode=new CSyntaxTreeNode_FUNCTION_DECLARATION(Choice,ParsingStackItems[0],ParsingStackItems[1],ParsingStackItems[3],ParsingStackItems[5]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="PARAMS")
			{
				if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="PARAM_LIST")
				{
					CSyntaxTreeNode_PARAMS					TreeNode=new CSyntaxTreeNode_PARAMS(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalVOID")
				{
					CSyntaxTreeNode_PARAMS					TreeNode=new CSyntaxTreeNode_PARAMS(Choice);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="PARAM_LIST")
			{
				if (Choice.Symbols.Length==3 && Choice.Symbols[0].Name=="PARAM_LIST" && Choice.Symbols[1].Name=="TerminalComma" && Choice.Symbols[2].Name=="PARAM")
				{
					CSyntaxTreeNode_PARAM_LIST				TreeNode=new CSyntaxTreeNode_PARAM_LIST(Choice,ParsingStackItems[0],ParsingStackItems[2]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="PARAM")
				{
					CSyntaxTreeNode_PARAM_LIST				TreeNode=new CSyntaxTreeNode_PARAM_LIST(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="PARAM")
			{
				if (Choice.Symbols.Length==2 && Choice.Symbols[0].Name=="TYPE_SPECIFIER" && Choice.Symbols[1].Name=="TerminalID")
				{
					CSyntaxTreeNode_PARAM					TreeNode=new CSyntaxTreeNode_PARAM(Choice,ParsingStackItems[0],ParsingStackItems[1]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==4 && Choice.Symbols[0].Name=="TYPE_SPECIFIER" && Choice.Symbols[1].Name=="TerminalID" && Choice.Symbols[2].Name=="TerminalSquareBracketLeft" && Choice.Symbols[3].Name=="TerminalSquareBracketRight")
				{
					CSyntaxTreeNode_PARAM					TreeNode=new CSyntaxTreeNode_PARAM(Choice,ParsingStackItems[0],ParsingStackItems[1]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="COMPOUND_STATEMENT")
			{
				if (Choice.Symbols.Length==4 && Choice.Symbols[0].Name=="TerminalCurlyBracketLeft" && Choice.Symbols[1].Name=="LOCAL_DECLARATIONS" && Choice.Symbols[2].Name=="STATEMENT_LIST" && Choice.Symbols[3].Name=="TerminalCurlyBracketRight")
				{
					CSyntaxTreeNode_COMPOUND_STATEMENT		TreeNode=new CSyntaxTreeNode_COMPOUND_STATEMENT(Choice,ParsingStackItems[1],ParsingStackItems[2]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="LOCAL_DECLARATIONS")
			{
				if (Choice.Symbols.Length==2 && Choice.Symbols[0].Name=="LOCAL_DECLARATIONS" && Choice.Symbols[1].Name=="VARIABLE_DECLARATION")
				{
					CSyntaxTreeNode_LOCAL_DECLARATIONS		TreeNode=new CSyntaxTreeNode_LOCAL_DECLARATIONS(Choice,ParsingStackItems[0],ParsingStackItems[1]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalEMPTY")
				{
					CSyntaxTreeNode_LOCAL_DECLARATIONS		TreeNode=new CSyntaxTreeNode_LOCAL_DECLARATIONS(Choice);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="STATEMENT_LIST")
			{
				if (Choice.Symbols.Length==2 && Choice.Symbols[0].Name=="STATEMENT_LIST" && Choice.Symbols[1].Name=="STATEMENT")
				{
					CSyntaxTreeNode_STATEMENT_LIST			TreeNode=new CSyntaxTreeNode_STATEMENT_LIST(Choice,ParsingStackItems[0],ParsingStackItems[1]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalEMPTY")
				{
					CSyntaxTreeNode_STATEMENT_LIST			TreeNode=new CSyntaxTreeNode_STATEMENT_LIST(Choice);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="STATEMENT")
			{
				if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="EXPRESSION_STATEMENT")
				{
					CSyntaxTreeNode_STATEMENT				TreeNode=new CSyntaxTreeNode_STATEMENT(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="COMPOUND_STATEMENT")
				{
					CSyntaxTreeNode_STATEMENT				TreeNode=new CSyntaxTreeNode_STATEMENT(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="SELECTION_STATEMENT")
				{
					CSyntaxTreeNode_STATEMENT				TreeNode=new CSyntaxTreeNode_STATEMENT(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="ITERATION_STATEMENT")
				{
					CSyntaxTreeNode_STATEMENT				TreeNode=new CSyntaxTreeNode_STATEMENT(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="RETURN_STATEMENT")
				{
					CSyntaxTreeNode_STATEMENT				TreeNode=new CSyntaxTreeNode_STATEMENT(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="EXPRESSION_STATEMENT")
			{
				if (Choice.Symbols.Length==4 && Choice.Symbols[0].Name=="VARIABLE" && Choice.Symbols[1].Name=="TerminalAssigment" && Choice.Symbols[2].Name=="EXPRESSION" && Choice.Symbols[3].Name=="TerminalSemicolon")
				{
					CSyntaxTreeNode_EXPRESSION_STATEMENT	TreeNode=new CSyntaxTreeNode_EXPRESSION_STATEMENT(Choice,ParsingStackItems[0],ParsingStackItems[2]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==2 && Choice.Symbols[0].Name=="CALL" && Choice.Symbols[1].Name=="TerminalSemicolon")
				{
					CSyntaxTreeNode_EXPRESSION_STATEMENT	TreeNode=new CSyntaxTreeNode_EXPRESSION_STATEMENT(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalSemicolon")
				{
					CSyntaxTreeNode_EXPRESSION_STATEMENT	TreeNode=new CSyntaxTreeNode_EXPRESSION_STATEMENT(Choice);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="SELECTION_STATEMENT")
			{
				if (Choice.Symbols.Length==5 && Choice.Symbols[0].Name=="TerminalIF" && Choice.Symbols[1].Name=="TerminalRoundBracketLeft" && Choice.Symbols[2].Name=="EXPRESSION" && Choice.Symbols[3].Name=="TerminalRoundBracketRight" && Choice.Symbols[4].Name=="STATEMENT")
				{
					CSyntaxTreeNode_SELECTION_STATEMENT		TreeNode=new CSyntaxTreeNode_SELECTION_STATEMENT(Choice,ParsingStackItems[2],ParsingStackItems[4]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==7 && Choice.Symbols[0].Name=="TerminalIF" && Choice.Symbols[1].Name=="TerminalRoundBracketLeft" && Choice.Symbols[2].Name=="EXPRESSION" && Choice.Symbols[3].Name=="TerminalRoundBracketRight" && Choice.Symbols[4].Name=="STATEMENT" && Choice.Symbols[5].Name=="TerminalELSE" && Choice.Symbols[6].Name=="STATEMENT")
				{
					CSyntaxTreeNode_SELECTION_STATEMENT		TreeNode=new CSyntaxTreeNode_SELECTION_STATEMENT(Choice,ParsingStackItems[2],ParsingStackItems[4],ParsingStackItems[6]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="ITERATION_STATEMENT")
			{
				if (Choice.Symbols.Length==5 && Choice.Symbols[0].Name=="TerminalWHILE" && Choice.Symbols[1].Name=="TerminalRoundBracketLeft" && Choice.Symbols[2].Name=="EXPRESSION" && Choice.Symbols[3].Name=="TerminalRoundBracketRight" && Choice.Symbols[4].Name=="STATEMENT")
				{
					CSyntaxTreeNode_ITERATION_STATEMENT		TreeNode=new CSyntaxTreeNode_ITERATION_STATEMENT(Choice,ParsingStackItems[2],ParsingStackItems[4]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="RETURN_STATEMENT")
			{
				if (Choice.Symbols.Length==2 && Choice.Symbols[0].Name=="TerminalRETURN" && Choice.Symbols[1].Name=="TerminalSemicolon")
				{
					CSyntaxTreeNode_RETURN_STATEMENT		TreeNode=new CSyntaxTreeNode_RETURN_STATEMENT(Choice);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==5 && Choice.Symbols[0].Name=="TerminalRETURN" && Choice.Symbols[1].Name=="TerminalRoundBracketLeft" && Choice.Symbols[2].Name=="EXPRESSION" && Choice.Symbols[3].Name=="TerminalRoundBracketRight" && Choice.Symbols[4].Name=="TerminalSemicolon")
				{
					CSyntaxTreeNode_RETURN_STATEMENT		TreeNode=new CSyntaxTreeNode_RETURN_STATEMENT(Choice,ParsingStackItems[2]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="VARIABLE")
			{
				if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalID")
				{
					CSyntaxTreeNode_VARIABLE				TreeNode=new CSyntaxTreeNode_VARIABLE(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==4 && Choice.Symbols[0].Name=="TerminalID" && Choice.Symbols[1].Name=="TerminalSquareBracketLeft" && Choice.Symbols[2].Name=="EXPRESSION" && Choice.Symbols[3].Name=="TerminalSquareBracketRight")
				{
					CSyntaxTreeNode_VARIABLE				TreeNode=new CSyntaxTreeNode_VARIABLE(Choice,ParsingStackItems[0],ParsingStackItems[2]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="EXPRESSION")
			{
				if (Choice.Symbols.Length==3 && Choice.Symbols[0].Name=="ADDITIVE_EXPRESSION" && Choice.Symbols[1].Name=="COMPARE_OPERATION" && Choice.Symbols[2].Name=="ADDITIVE_EXPRESSION")
				{
					CSyntaxTreeNode_EXPRESSION				TreeNode=new CSyntaxTreeNode_EXPRESSION(Choice,ParsingStackItems[0],ParsingStackItems[1],ParsingStackItems[2]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="ADDITIVE_EXPRESSION")
				{
					CSyntaxTreeNode_EXPRESSION				TreeNode=new CSyntaxTreeNode_EXPRESSION(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="COMPARE_OPERATION")
			{
				if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalLesserOrEqual")
				{
					CSyntaxTreeNode_COMPARE_OPERATION		TreeNode=new CSyntaxTreeNode_COMPARE_OPERATION(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalLesser")
				{
					CSyntaxTreeNode_COMPARE_OPERATION		TreeNode=new CSyntaxTreeNode_COMPARE_OPERATION(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalGreater")
				{
					CSyntaxTreeNode_COMPARE_OPERATION		TreeNode=new CSyntaxTreeNode_COMPARE_OPERATION(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalGreaterOrEqual")
				{
					CSyntaxTreeNode_COMPARE_OPERATION		TreeNode=new CSyntaxTreeNode_COMPARE_OPERATION(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalEqual")
				{
					CSyntaxTreeNode_COMPARE_OPERATION		TreeNode=new CSyntaxTreeNode_COMPARE_OPERATION(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalNotEqual")
				{
					CSyntaxTreeNode_COMPARE_OPERATION		TreeNode=new CSyntaxTreeNode_COMPARE_OPERATION(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="ADDITIVE_EXPRESSION")
			{
				if (Choice.Symbols.Length==3 && Choice.Symbols[0].Name=="ADDITIVE_EXPRESSION" && Choice.Symbols[1].Name=="ADD_OPERATION" && Choice.Symbols[2].Name=="TERM")
				{
					CSyntaxTreeNode_ADDITIVE_EXPRESSION		TreeNode=new CSyntaxTreeNode_ADDITIVE_EXPRESSION(Choice,ParsingStackItems[0],ParsingStackItems[1],ParsingStackItems[2]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TERM")
				{
					CSyntaxTreeNode_ADDITIVE_EXPRESSION		TreeNode=new CSyntaxTreeNode_ADDITIVE_EXPRESSION(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="ADD_OPERATION")
			{
				if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalPlus")
				{
					CSyntaxTreeNode_ADD_OPERATION			TreeNode=new CSyntaxTreeNode_ADD_OPERATION(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalMinus")
				{
					CSyntaxTreeNode_ADD_OPERATION			TreeNode=new CSyntaxTreeNode_ADD_OPERATION(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="TERM")
			{
				if (Choice.Symbols.Length==3 && Choice.Symbols[0].Name=="TERM" && Choice.Symbols[1].Name=="MUL_OPERATION" && Choice.Symbols[2].Name=="FACTOR")
				{
					CSyntaxTreeNode_TERM					TreeNode=new CSyntaxTreeNode_TERM(Choice,ParsingStackItems[0],ParsingStackItems[1],ParsingStackItems[2]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="FACTOR")
				{
					CSyntaxTreeNode_TERM					TreeNode=new CSyntaxTreeNode_TERM(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="MUL_OPERATION")
			{
				if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalAsterisk")
				{
					CSyntaxTreeNode_MUL_OPERATION			TreeNode=new CSyntaxTreeNode_MUL_OPERATION(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalSlash")
				{
					CSyntaxTreeNode_MUL_OPERATION			TreeNode=new CSyntaxTreeNode_MUL_OPERATION(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="FACTOR")
			{
				if (Choice.Symbols.Length==3 && Choice.Symbols[0].Name=="TerminalRoundBracketLeft" && Choice.Symbols[1].Name=="EXPRESSION" && Choice.Symbols[2].Name=="TerminalRoundBracketRight")
				{
					CSyntaxTreeNode_FACTOR					TreeNode=new CSyntaxTreeNode_FACTOR(Choice,ParsingStackItems[1]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="VARIABLE")
				{
					CSyntaxTreeNode_FACTOR					TreeNode=new CSyntaxTreeNode_FACTOR(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="CALL")
				{
					CSyntaxTreeNode_FACTOR					TreeNode=new CSyntaxTreeNode_FACTOR(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalNumber")
				{
					CSyntaxTreeNode_FACTOR					TreeNode=new CSyntaxTreeNode_FACTOR(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalString")
				{
					CSyntaxTreeNode_FACTOR					TreeNode=new CSyntaxTreeNode_FACTOR(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="CALL")
			{
				if (Choice.Symbols.Length==4 && Choice.Symbols[0].Name=="TerminalID" && Choice.Symbols[1].Name=="TerminalRoundBracketLeft" && Choice.Symbols[2].Name=="ARGS" && Choice.Symbols[3].Name=="TerminalRoundBracketRight")
				{
					CSyntaxTreeNode_CALL					TreeNode=new CSyntaxTreeNode_CALL(Choice,ParsingStackItems[0],ParsingStackItems[2]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="ARGS")
			{
				if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="ARG_LIST")
				{
					CSyntaxTreeNode_ARGS					TreeNode=new CSyntaxTreeNode_ARGS(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalEMPTY")
				{
					CSyntaxTreeNode_ARGS					TreeNode=new CSyntaxTreeNode_ARGS(Choice);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="ARG_LIST")
			{
				if (Choice.Symbols.Length==3 && Choice.Symbols[0].Name=="ARG_LIST" && Choice.Symbols[1].Name=="TerminalComma" && Choice.Symbols[2].Name=="EXPRESSION")
				{
					CSyntaxTreeNode_ARG_LIST				TreeNode=new CSyntaxTreeNode_ARG_LIST(Choice,ParsingStackItems[0],ParsingStackItems[2]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="EXPRESSION")
				{
					CSyntaxTreeNode_ARG_LIST				TreeNode=new CSyntaxTreeNode_ARG_LIST(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
			}
			else if (Choice.Nonterminal.Name=="CONST")
			{
				if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalNumber")
				{
					CSyntaxTreeNode_CONST					TreeNode=new CSyntaxTreeNode_CONST(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
				else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalString")
				{
					CSyntaxTreeNode_CONST					TreeNode=new CSyntaxTreeNode_CONST(Choice,ParsingStackItems[0]);

					return(TreeNode);
				}
			}

			throw(new InvalidOperationException(string.Format("Invalid CHOICE [{0}] !",Choice)));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------