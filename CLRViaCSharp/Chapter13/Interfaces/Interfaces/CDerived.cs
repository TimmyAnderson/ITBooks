﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Interfaces
{
//-------------------------------------------------------------------------------------------------------
	public class CDerived : CBase
	{
//-------------------------------------------------------------------------------------------------------
		public new void NonVirtualMethod()
		{
			Console.WriteLine("CDerived.NonVirtualMethod() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
		public override void VirtualMethod()
		{
			Console.WriteLine("CDerived.VirtualMethod() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
		public new virtual void VirtualMethodWithNew()
		{
			Console.WriteLine("CDerived.VirtualMethodWithNew() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------