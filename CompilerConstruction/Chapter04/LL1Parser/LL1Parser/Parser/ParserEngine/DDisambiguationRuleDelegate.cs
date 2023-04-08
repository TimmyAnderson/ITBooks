using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace LL1Parser
{
//-------------------------------------------------------------------------------------------------------
	public delegate CChoice DDisambiguationRuleDelegate(CChoice[] Choices, CSyntaxTreeNode NextNode, CToken NextToken, CToken[] RemainingTokens, CParserErrorList Errors);
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------