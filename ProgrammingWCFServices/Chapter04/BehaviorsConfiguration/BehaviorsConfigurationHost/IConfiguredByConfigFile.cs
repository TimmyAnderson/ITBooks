﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace BehaviorsConfigurationHost
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IConfiguredByConfigFile
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void ThrowException(string Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------