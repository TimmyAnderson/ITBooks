using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace Generics
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CPrimaryConstraintReferenceType<TType> where TType : CBaseClass
	{
//-------------------------------------------------------------------------------------------------------
		public void PrintType(TType Type)
		{
			// !!! Kedze TType musi byt DERIVED z CBaseClass, CODE moze pristupovat k MEMBERS CBaseClass.
			Console.WriteLine(string.Format("METHOD PrintType() from TYPE [{0}] CALLED and NUMBER is [{1}] !",GetType(),Type.Number));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------