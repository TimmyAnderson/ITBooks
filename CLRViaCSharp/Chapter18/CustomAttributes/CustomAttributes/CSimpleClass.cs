using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
//-------------------------------------------------------------------------------------------------------
namespace CustomAttributes
{
//-------------------------------------------------------------------------------------------------------
	// Explicitne definujem prefix.
	[type:CMySuperAttribute("Anderson",FirstName="Timmy")]
	public class CSimpleClass
	{
//-------------------------------------------------------------------------------------------------------
		[method:CMySuperAttribute("Anderson")]
		[method:CMySuperAttribute("Atreyu")]
		[return:CMySuperAttribute("Thompson",FirstName="Jenny")]
		[return:CMySuperAttribute("Anderson",FirstName="Timmy")]
		public string ToUpper([param:CMySuperAttribute("Thompson",FirstName="Jenny"), Out] string Param)
		{
			return(Param.ToUpper());
		}
//-------------------------------------------------------------------------------------------------------
		[method:CMyDerivedSuperAttribute("Anderson",FirstName="Timmy")]
		public void DoNothing()
		{
			Console.WriteLine("NOTHING !");
		}
//-------------------------------------------------------------------------------------------------------
		[CInheritable("Anderson",FirstName="Timmy")]
		public virtual void VirtualMethod1()
		{
			Console.WriteLine("CSimpleClass - VIRTUAL METHOD 1 !");
		}
//-------------------------------------------------------------------------------------------------------
		[CNonInheritable("Anderson",FirstName="Timmy")]
		public virtual void VirtualMethod2()
		{
			Console.WriteLine("CSimpleClass - VIRTUAL METHOD 2 !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------