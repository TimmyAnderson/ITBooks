using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public class CInputChar_AnyLetter : CInputChar
	{
//-------------------------------------------------------------------------------------------------------
		private readonly bool									MAcceptUpperCaseLetters;
		private readonly bool									MAcceptLowerCaseLetters;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CInputChar_AnyLetter(string Name, bool AcceptUpperCaseLetters, bool AcceptLowerCaseLetters)
			: base(Name)
		{
			if (AcceptUpperCaseLetters==false && AcceptLowerCaseLetters==false)
				throw(new ArgumentException("AcceptUpperCaseLetters and AcceptLowerCaseLetters CAN'T be BOTH FALSE !"));

			MAcceptUpperCaseLetters=AcceptUpperCaseLetters;
			MAcceptLowerCaseLetters=AcceptLowerCaseLetters;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override bool IsValidChar(char CharToCheck)
		{
			if (MAcceptUpperCaseLetters==true && CharToCheck>='A' && CharToCheck<='Z')
				return(true);

			if (MAcceptLowerCaseLetters==true && CharToCheck>='a' && CharToCheck<='z')
				return(true);

			return(false);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------