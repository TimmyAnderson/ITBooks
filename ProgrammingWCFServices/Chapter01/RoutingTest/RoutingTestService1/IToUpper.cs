﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace RoutingTestService1
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IToUpper
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		string ToUpper(string Text);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------