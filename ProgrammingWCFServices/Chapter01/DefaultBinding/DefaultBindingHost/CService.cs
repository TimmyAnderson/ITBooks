﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace DefaultBindingHost
{
//-------------------------------------------------------------------------------------------------------
	public class CService : IService
	{
//-------------------------------------------------------------------------------------------------------
		public string ToUpper(string Text)
		{
			return(Text.ToUpper());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------