﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//------------------------------------------------------------------------------------------------------
namespace HighlyAvialableApplications
{
//------------------------------------------------------------------------------------------------------
	public sealed class CFinalizer
	{
//------------------------------------------------------------------------------------------------------
		~CFinalizer()
		{
			Console.WriteLine("FINALIZER CFinalizer CALLED !");
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		public void DoSomething()
		{
			Console.WriteLine("CFinalizer.DoSomething() CALLED !");
		}
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------