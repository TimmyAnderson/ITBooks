﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RoutingTestService2
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CToLower : IToLower
	{
//-------------------------------------------------------------------------------------------------------
		public string ToLower(string Text)
		{
			string				Result=Text.ToLower();

			Console.WriteLine("ToLower() CALLED !");

			return(Result);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------