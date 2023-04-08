using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace Generics
{
//-------------------------------------------------------------------------------------------------------
	// !!! NAKED TYPE PARAMETER CONSTRAINT umoznuju definovat vazby medzi TYPE PARAMETERS.
	// !!!!! CLR akceptuje aj ked TTypeBase==TTypeDerived.
	// !!!!! CLR akceptuje aj ked ak TTypeDerived ma IMPLEMENTOVANY INTERFACE TTypeBase.
	public sealed class CNakedTypeParameterConstraint<TTypeBase,TTypeDerived> where TTypeDerived : TTypeBase
	{
//-------------------------------------------------------------------------------------------------------
		public void PrintType()
		{
			Console.WriteLine(string.Format("METHOD PrintType() from TYPE [{0}] CALLED !",GetType()));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------