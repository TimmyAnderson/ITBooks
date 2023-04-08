﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CState_AcceptingKeywordToken : CState_Accepting
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MKeywordTokenID;
		private readonly string									MNonKeywordTokenID;
		private readonly string[]								MKeywords;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CState_AcceptingKeywordToken(string Name, string KeywordTokenID, string NonKeywordTokenID, string[] Keywords)
			: base(Name,false)
		{
			MKeywordTokenID=KeywordTokenID;
			MNonKeywordTokenID=NonKeywordTokenID;
			MKeywords=Keywords;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											KeywordTokenID
		{
			get
			{
				return(MKeywordTokenID);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											NonKeywordTokenID
		{
			get
			{
				return(MNonKeywordTokenID);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string[]											Keywords
		{
			get
			{
				return(MKeywords);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public bool CheckLexemaForKeyword(string Lexema)
		{
			if (MKeywords.Where(P => P==Lexema).FirstOrDefault()!=null)
				return(true);
			else
				return(false);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------