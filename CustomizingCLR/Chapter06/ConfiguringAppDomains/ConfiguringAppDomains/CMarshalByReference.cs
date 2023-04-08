using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
//------------------------------------------------------------------------------------------------------
namespace ConfiguringAppDomains
{
//------------------------------------------------------------------------------------------------------
	// !!!!! CLASS DEDI MarshalByRefObject a teda bude prenasana ako MARSHAL by REFERENCE.
	public sealed class CMarshalByReference : MarshalByRefObject
	{
//------------------------------------------------------------------------------------------------------
		public CMarshalByReference()
		{
			Console.WriteLine("CONSTRUCTOR - CMarshalByReference.CMarshalByReference() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		public void PrintAppDomain()
		{
			Console.WriteLine("CMarshalByReference.PrintAppDomain() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
		}
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------
