﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesBearerTokens.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CLoginResult
	{
//----------------------------------------------------------------------------------------------------------------------
		private bool											MSuccess;
		private string											MToken;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CLoginResult()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CLoginResult(bool Success, string Token)
		{
			MSuccess=Success;
			MToken=Token;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public bool												Success
		{
			get
			{
				return(MSuccess);
			}
			set
			{
				MSuccess=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											Token
		{
			get
			{
				return(MToken);
			}
			set
			{
				MToken=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------