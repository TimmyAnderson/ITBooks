﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RoutingTestService1
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CToUpper : IToUpper
	{
//-------------------------------------------------------------------------------------------------------
		public string ToUpper(string Text)
		{
			string				Result=Text.ToUpper();

			Console.WriteLine("ToUpper() CALLED !");

			return(Result);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------