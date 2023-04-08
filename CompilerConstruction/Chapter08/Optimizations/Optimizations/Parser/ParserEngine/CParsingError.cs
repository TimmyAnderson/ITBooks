using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CParsingError : CCompilerError
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSymbol								MCurrentSourceCodeSymbol;
		private readonly CParsingStackItem						MCurrentItem;
		private readonly int									MSourceCodeIndex;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParsingError(string ErrorDescription, CSymbol CurrentSourceCodeSymbol, CParsingStackItem CurrentItem, int SourceCodeIndex)
			: base(ErrorDescription)
		{
			MCurrentSourceCodeSymbol=CurrentSourceCodeSymbol;
			MCurrentItem=CurrentItem;
			MSourceCodeIndex=SourceCodeIndex;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbol											CurrentSourceCodeSymbol
		{
			get
			{
				return(MCurrentSourceCodeSymbol);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CParsingStackItem								CurrentItem
		{
			get
			{
				return(MCurrentItem);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int												SourceCodeIndex
		{
			get
			{
				return(MSourceCodeIndex);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string GetError(CSourceCode SourceCode)
		{
			StringBuilder										SB=new StringBuilder();

			SB.AppendFormat(base.GetError(SourceCode));
			SB.AppendFormat(", SourceCodeLine: [{0}]",SourceCode.GetSourceCodeLineAtIndex(MSourceCodeIndex).GetSouceCodeLineWithoutNewLineCharacter());

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------