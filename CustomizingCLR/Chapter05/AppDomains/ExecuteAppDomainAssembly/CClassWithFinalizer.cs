﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace ExecuteAppDomainAssembly
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CClassWithFinalizer
	{
//-------------------------------------------------------------------------------------------------------
		~CClassWithFinalizer()
		{
			Console.WriteLine(string.Format("!!!!! FINALIZER EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------