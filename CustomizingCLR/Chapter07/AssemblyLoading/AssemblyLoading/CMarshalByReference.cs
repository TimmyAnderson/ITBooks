using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Runtime.Serialization;
//------------------------------------------------------------------------------------------------------
namespace AssemblyLoading
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
		public void HasPrintTextAssembly()
		{
			Assembly											HasPrintTextAssembly=AppDomain.CurrentDomain.GetAssemblies().Where(P => P.FullName.Contains("PrintTextAssembly")==true).FirstOrDefault();

			if (HasPrintTextAssembly!=null)
			{
				Console.WriteLine("!!! APP DOMAIN [{0} - {1}] HAS ASSEBLY PrintTextAssembly !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
			}
			else
			{
				Console.WriteLine("APP DOMAIN [{0} - {1}] HAS NOT ASSEBLY PrintTextAssembly !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
			}
		}
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------
