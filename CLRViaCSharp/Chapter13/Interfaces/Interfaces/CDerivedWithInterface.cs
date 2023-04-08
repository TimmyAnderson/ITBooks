using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace Interfaces
{
//-------------------------------------------------------------------------------------------------------
	// !!! EXPLICITNE implementuje INTERFACE IInterface.
	public sealed class CDerivedWithInterface : CBaseWithInterface, IInterface
	{
//-------------------------------------------------------------------------------------------------------
		// !!! Kedze METHOD Print1() NEBOLA v CBaseWithInterface oznacena KEYWORD [virtual], nemoze byt OVERRIDEN a MUSI sa pouzit KEYWORD [new].
		public new void Print1()
		{
			Console.WriteLine("CDerivedWithInterface.Print1() CALLED ");
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Kedze METHOD Print2() bola v CBaseWithInterface oznacena KEYWORD [virtual], moze byt OVERRIDEN.
		public override void Print2()
		{
			Console.WriteLine("CDerivedWithInterface.Print2() CALLED ");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------