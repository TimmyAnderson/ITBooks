﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace TestServiceMetadataEndpoint
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IToUpperService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		string ToUpper(string Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------