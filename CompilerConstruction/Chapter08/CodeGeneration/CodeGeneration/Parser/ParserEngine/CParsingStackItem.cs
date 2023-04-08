﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CParsingStackItem
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CDFAState								MDFAState;
		private readonly CParseTreeNode							MParseTreeNode;
		private readonly CSyntaxTreeNode						MSyntaxTreeNode;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParsingStackItem(CDFAState DFAState, CParseTreeNode ParseTreeNode, CSyntaxTreeNode SyntaxTreeNode)
		{
			MDFAState=DFAState;
			MParseTreeNode=ParseTreeNode;
			MSyntaxTreeNode=SyntaxTreeNode;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CDFAState										DFAState
		{
			get
			{
				return(MDFAState);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CParseTreeNode									ParseTreeNode
		{
			get
			{
				return(MParseTreeNode);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode									SyntaxTreeNode
		{
			get
			{
				return(MSyntaxTreeNode);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder			SB=new StringBuilder();

			if (MSyntaxTreeNode!=null)
			{
				SB.AppendFormat("[{0}] --- [{1}] --- [{2}]",MSyntaxTreeNode,MParseTreeNode,MDFAState);
			}
			else
			{
				SB.AppendFormat("[{0}] --- [{1}]",MParseTreeNode,MDFAState);
			}

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------