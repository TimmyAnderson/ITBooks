using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_CALL : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MFunctionName;
		private readonly CSyntaxTreeNode_ARGS					MArguments;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_CALL(CChoice Choice, CParsingStackItem FunctionName, CParsingStackItem Arguments)
			: base(Choice)
		{
			MFunctionName=FunctionName.ParseTreeNode.Token.Lexema;
			MArguments=(CSyntaxTreeNode_ARGS) Arguments.SyntaxTreeNode;
			MChoiceNumber=1;
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
		public CSyntaxTreeNode_ARGS								Arguments
		{
			get
			{
				return(MArguments);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string PrintTree()
		{
			if (MChoiceNumber==1)
			{
				StringBuilder			SB=new StringBuilder();

				if (MArguments!=null)
				{
					SB.Append(string.Format("{0}({1})",MFunctionName,MArguments.PrintTree()));
				}
				else
				{
					SB.Append(string.Format("{0}({1})",MFunctionName,"NULL"));
				}

				return(SB.ToString());
			}
			else
			{
				throw(new InvalidOperationException(string.Format("Invalid CHOICE [{0}] !",Choice)));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------