using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Interfaces
{
//-------------------------------------------------------------------------------------------------------
	public class CVirtualMethodTable1 : IDummy
	{
//-------------------------------------------------------------------------------------------------------
		// !!!!! Tato metoda reprezentuje CVirtualMethodTable1.DoSomething(), no KEDZE C# keneruje i pre IDummy.DoSomething() odkaz na TEN ISTY CODE, tak de-facto medzi tymito metodami z hladiska pouzitia NIE JE ZIADEN ROZDIEL.
		public void DoSomething()
		{
			Console.WriteLine("CVirtualMethodTable1.DoSomething() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------