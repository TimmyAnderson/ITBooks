﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace InheritanceOneServiceWithTwoEndpoints_Service
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface ISimpleTextOperations
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		string ToUpper(string Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------