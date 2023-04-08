using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Interfaces
{
//-------------------------------------------------------------------------------------------------------
	public class CVirtualMethodTable2 : IDummy
	{
//-------------------------------------------------------------------------------------------------------
		// !!!!! Tato metoda reprezentuje CVirtualMethodTable2.DoSomething().
		public void DoSomething()
		{
			Console.WriteLine("CVirtualMethodTable2.DoSomething() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
		// EXPLICITNE implementovany INTERFACE.
		// !!!!! Tato metoda reprezentuje IDummy.DoSomething().
		void IDummy.DoSomething()
		{
			Console.WriteLine("IDummy.DoSomething() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------