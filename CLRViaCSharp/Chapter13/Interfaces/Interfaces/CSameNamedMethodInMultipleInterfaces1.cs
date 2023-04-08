using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Interfaces
{
//-------------------------------------------------------------------------------------------------------
	// Ak trieda implementuje 2 INTERFACES, ktore maju ROVANKO POMENOVANU METODU, tak MUSIM POUZIT EXPLICITNU IMPLEMENTACIU INTERFACE.
	public class CSameNamedMethodInMultipleInterfaces1 : IInterface1, IInterface2
	{
//-------------------------------------------------------------------------------------------------------
		// EXPLICITNE IMPLEMENTOVANA METODA INTERFACE IInterface1.
		void IInterface1.SameNamedMethod()
		{
			Console.WriteLine("IInterface1.SameNamedMethod() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
		// EXPLICITNE IMPLEMENTOVANA METODA INTERFACE IInterface2.
		void IInterface2.SameNamedMethod()
		{
			Console.WriteLine("IInterface2.SameNamedMethod() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
		// IMPLICITNE IMPLEMENTOVANA METODA INTERFACE IInterface1 a IInterface2.
		public void SameNamedMethod()
		{
			Console.WriteLine("SameNamedMethod() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------