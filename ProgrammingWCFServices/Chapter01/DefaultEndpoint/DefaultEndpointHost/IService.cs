﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Security;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace DefaultEndpointHost
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		string ToUpper(string Text);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------