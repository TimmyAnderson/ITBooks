using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.AddIn.Contract;
using System.AddIn.Pipeline;
//------------------------------------------------------------------------
// 1. Contract DEFINUJE INTERFACE MEDZI APPLIKACIU A ADDINS.
// 2. Contract interface musi dedit od IContract.
// 3. Ak by som chcel prenasat cez AddIn aj komplexnejsie CUSTOM typy musia byt serializovatelne.
// !!!!! 4. AddIn nedokaze ziskat ziskavat objekty z Host Aplikacie. Ak chcem realizovat Callback a ten vyzaduje samozrejme nejaky objekt z Host Aplikacie, tak sa to robi cez konvenciu, kedy sa doplni metoda Initialize, ktora obsahuje v parametroch potrebne objekty z Host Applikacie, ktore AddIn potrebuje pre realizaciu callback.
//------------------------------------------------------------------------
namespace Contract
{
//------------------------------------------------------------------------
	[AddInContract]
	public interface IImageProcessorContract : IContract
	{
//------------------------------------------------------------------------
		byte[] ProcessImageBytes(byte[] Pixels);
		// !!! Cez tuto metodu prenesiem instanciu HostApplication.CAutomationHost do AddInu.
		void Initialize(IHostObjectContract HostObj);
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------