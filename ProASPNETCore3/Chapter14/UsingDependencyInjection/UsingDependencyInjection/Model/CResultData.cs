﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CResultData
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly Dictionary<string,string>				MData;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CResultData(Dictionary<string,string> Data)
		{
			MData=Data;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public Dictionary<string,string>						Data
		{
			get
			{
				return(MData);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------