using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace DCDelegatesSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
	// Oznacim DELEGATE ako SERIALIZOVATELNY.
	[Serializable]
	public delegate void DMyDelegate(string SomeParam);
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------