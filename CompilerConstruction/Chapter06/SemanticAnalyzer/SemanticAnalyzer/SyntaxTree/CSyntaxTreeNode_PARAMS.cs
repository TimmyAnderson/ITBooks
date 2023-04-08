using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_PARAMS : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_PARAM_LIST				MParamList;
		private readonly bool									MIsVoid;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_PARAMS(CChoice Choice, CParsingStackItem ParamList)
			: base(Choice)
		{
			MParamList=(CSyntaxTreeNode_PARAM_LIST) ParamList.SyntaxTreeNode;
			MIsVoid=false;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_PARAMS(CChoice Choice)
			: base(Choice)
		{
			MIsVoid=true;
			MChoiceNumber=2;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_PARAM_LIST						ParamList
		{
			get
			{
				return(MParamList);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												IsVoid
		{
			get
			{
				return(MIsVoid);
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

				if (MParamList!=null)
				{
					SB.Append(MParamList.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder			SB=new StringBuilder();

				SB.Append("void");

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