using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Interfaces
{
//-------------------------------------------------------------------------------------------------------
	// NON-GENERICS INTERFACE IComparable implementujem ako EXPLICITNE DEFINOVANY INTERFACE.
	public sealed class CExplicitlyImplementedInterface : IComparable
	{
//-------------------------------------------------------------------------------------------------------
		int IComparable.CompareTo(object Obj)
		{
			Console.WriteLine("IComparable.CompareTo(object Obj) CALLED !");

			return(0);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! Namiesto CompareTo(object Obj) definujem TYPOVO BEZPECNU metodu.
		public int CompareTo(CExplicitlyImplementedInterface Obj)
		{
			Console.WriteLine("CompareTo(CExplicitlyImplementedInterface Obj) CALLED !");

			return(0);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------