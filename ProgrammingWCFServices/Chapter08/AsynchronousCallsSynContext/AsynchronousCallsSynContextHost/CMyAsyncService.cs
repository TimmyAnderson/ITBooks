﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//--------------------------------------------------------------------------------------------------------------------------------------
namespace AsynchronousCallsSynContextHost
{
//--------------------------------------------------------------------------------------------------------------------------------------
	public class CMyAsyncService : IMyAsyncService
	{
//--------------------------------------------------------------------------------------------------------------------------------------
		public string ToUpper(string Value)
		{
			Console.WriteLine("Operation CALLED !");

			return(Value.ToUpper());
		}
//--------------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------------