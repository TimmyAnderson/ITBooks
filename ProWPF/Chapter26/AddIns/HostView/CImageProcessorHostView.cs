using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//------------------------------------------------------------------------
// 1. AddInView MUSI mat TIE ISTE METODY AKO CONTRACT.
// !!! 2. Avsak z CONTRACT INTERFACE TRIEDA NEDEDI.
//------------------------------------------------------------------------
namespace HostView
{
//------------------------------------------------------------------------
	public abstract class CImageProcessorHostView
	{
//------------------------------------------------------------------------
		public abstract byte[] ProcessImageBytes(byte[] Pixels);
		public abstract void Initialize(CHostObject Host);
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------