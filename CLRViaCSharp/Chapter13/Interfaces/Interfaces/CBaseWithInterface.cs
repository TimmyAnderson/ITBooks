using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace Interfaces
{
//-------------------------------------------------------------------------------------------------------
	// Implementuje INTERFACE IInterface.
	public class CBaseWithInterface : IInterface
	{
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD NEMA nastaveny FLAG VIRTUAL. C# AUTOMATICKY oznaci METHOD za VIRTUAL a SEALED.
		public void Print1()
		{
			Console.WriteLine("CBaseWithInterface.Print1() CALLED ");
		}
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD MA nastaveny FLAG VIRTUAL. C# oznaci METHOD za VIRTUAL, ale NIE SEALED.
		public virtual void Print2()
		{
			Console.WriteLine("CBaseWithInterface.Print2() CALLED ");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------