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
	public class CConfiguredByConfigFile : IConfiguredByConfigFile
	{
//-------------------------------------------------------------------------------------------------------
		public void ThrowException(string Value)
		{
			throw(new Exception(Value));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------