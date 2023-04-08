using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Interfaces
{
//-------------------------------------------------------------------------------------------------------
	public class CBase
	{
//-------------------------------------------------------------------------------------------------------
		public void NonVirtualMethod()
		{
			Console.WriteLine("CBase.NonVirtualMethod() CALLED !");

			/*
			// Volam VirtualMethod().
			VirtualMethod();

			// Volam VirtualMethodWithNew().
			VirtualMethodWithNew();
			*/
		}
//-------------------------------------------------------------------------------------------------------
		public virtual void VirtualMethod()
		{
			Console.WriteLine("CBase.VirtualMethod() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
		public virtual void VirtualMethodWithNew()
		{
			Console.WriteLine("CBase.VirtualMethodWithNew() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------