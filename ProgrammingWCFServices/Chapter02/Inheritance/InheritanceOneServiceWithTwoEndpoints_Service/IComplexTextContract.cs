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
	public interface IComplexTextContract : ISimpleTextOperations
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		string ToLower(string Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------