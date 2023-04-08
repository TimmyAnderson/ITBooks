using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CParsingError
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MErrorDescription;
		private readonly CSymbol								MCurrentSourceCodeSymbol;
		private readonly CParsingStackItem						MCurrentItem;
		private readonly string									MSourceCode;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParsingError(string ErrorDescription, CSymbol CurrentSourceCodeSymbol, CParsingStackItem CurrentItem, string SourceCode)
		{
			MErrorDescription=ErrorDescription;
			MCurrentSourceCodeSymbol=CurrentSourceCodeSymbol;
			MCurrentItem=CurrentItem;
			MSourceCode=SourceCode;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											ErrorDescription
		{
			get
			{
				return(MErrorDescription);
			}
		}
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
		public string											SourceCode
		{
			get
			{
				return(MSourceCode);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder			SB=new StringBuilder();

			SB.AppendFormat("ErrorDescription: [{0}]",MErrorDescription);
			SB.AppendFormat(", CurrentSourceCodeSymbol: [{0}]",MCurrentSourceCodeSymbol);
			SB.AppendFormat(", CurrentItem: [{0}]",MCurrentItem);
			SB.AppendFormat(", SourceCode: [{0}]",MSourceCode);

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------