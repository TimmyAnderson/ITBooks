using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public class CInputChar_AnyLetter : CInputChar
	{
//-------------------------------------------------------------------------------------------------------
		private readonly bool									MAcceptUpperCaseLetters;
		private readonly bool									MAcceptLowerCaseLetters;
		private readonly bool									MAcceptUnderscore;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CInputChar_AnyLetter(string Name, bool AcceptUpperCaseLetters, bool AcceptLowerCaseLetters, bool AcceptUnderscore)
			: base(Name)
		{
			if (AcceptUpperCaseLetters==false && AcceptLowerCaseLetters==false)
			{
				throw(new CCompilerException("AcceptUpperCaseLetters and AcceptLowerCaseLetters CAN'T be BOTH FALSE !"));
			}

			MAcceptUpperCaseLetters=AcceptUpperCaseLetters;
			MAcceptLowerCaseLetters=AcceptLowerCaseLetters;
			MAcceptUnderscore=AcceptUnderscore;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override bool IsValidChar(char CharToCheck)
		{
			if (MAcceptUpperCaseLetters==true && CharToCheck>='A' && CharToCheck<='Z')
			{
				return(true);
			}

			if (MAcceptLowerCaseLetters==true && CharToCheck>='a' && CharToCheck<='z')
			{
				return(true);
			}

			if (MAcceptUnderscore==true && CharToCheck=='_')
			{
				return(true);
			}

			return(false);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------