﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace IISHostingFactoryService
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IMySimpleService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		string ToUpper(string Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------