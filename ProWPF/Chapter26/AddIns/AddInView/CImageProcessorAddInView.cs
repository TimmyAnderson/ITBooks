using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.AddIn.Pipeline;
//------------------------------------------------------------------------
// 1. AddInView MUSI mat TIE ISTE METODY AKO CONTRACT.
// !!! 2. Avsak z CONTRACT INTERFACE TRIEDA NEDEDI.
//------------------------------------------------------------------------
namespace AddInView
{
//------------------------------------------------------------------------
	[AddInBase]
	public abstract class CImageProcessorAddInView
	{
//------------------------------------------------------------------------
		public abstract byte[] ProcessImageBytes(byte[] Pixels);
		public abstract void Initialize(CHostObject host);
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------