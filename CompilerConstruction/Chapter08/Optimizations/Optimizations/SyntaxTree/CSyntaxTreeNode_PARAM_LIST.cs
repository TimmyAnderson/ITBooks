using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_PARAM_LIST : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_PARAM_LIST				MParamList;
		private readonly CSyntaxTreeNode_PARAM					MParam;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_PARAM_LIST(CChoice Choice, CParsingStackItem ParamList, CParsingStackItem Param)
			: base(Choice)
		{
			MParamList=(CSyntaxTreeNode_PARAM_LIST) ParamList.SyntaxTreeNode;
			MParam=(CSyntaxTreeNode_PARAM) Param.SyntaxTreeNode;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_PARAM_LIST(CChoice Choice, CParsingStackItem Param)
			: base(Choice)
		{
			MParam=(CSyntaxTreeNode_PARAM) Param.SyntaxTreeNode;
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
		public CSyntaxTreeNode_PARAM							Param
		{
			get
			{
				return(MParam);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string PrintTree()
		{
			if (MChoiceNumber==1)
			{
				StringBuilder									SB=new StringBuilder();

				if (MParamList!=null && MParam!=null)
				{
					SB.Append(string.Format("{0},{1}",MParamList.PrintTree(),MParam.PrintTree()));
				}
				else if (MParamList!=null && MParam==null)
				{
					SB.Append(string.Format("{0},{1}",MParamList.PrintTree(),"NULL"));
				}
				else if (MParamList==null && MParam!=null)
				{
					SB.Append(string.Format("{0},{1}","NULL",MParam.PrintTree()));
				}
				else
				{
					SB.Append(string.Format("{0},{1}","NULL","NULL"));
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder									SB=new StringBuilder();

				if (MParam!=null)
				{
					SB.Append(MParam.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				return(SB.ToString());
			}
			else
			{
				throw(new CCompilerException(string.Format("Invalid CHOICE [{0}] !",Choice)));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------