﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace InheritanceTwoServices_Service
{
//-------------------------------------------------------------------------------------------------------
	public class CComplexTextService : IComplexTextContract
	{
//-------------------------------------------------------------------------------------------------------
		public string ToLower(string Value)
		{
			return(Value.ToLower());
		}
//-------------------------------------------------------------------------------------------------------
		public string  ToUpper(string Value)
		{
			return(Value.ToUpper());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------