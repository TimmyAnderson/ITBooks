﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace WCFCloseOneWayWithSessionTest
{
//-------------------------------------------------------------------------------------------------------
	public class CTestService : ITestService
	{
//-------------------------------------------------------------------------------------------------------
		public void ThrowException()
		{
			Console.WriteLine("ThrowException() CALLED !");

			throw(new Exception("Some EXCEPTION !"));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------