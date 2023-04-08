using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace ManualWCFLibrary
{
//-------------------------------------------------------------------------------------------------------
	// Mohol by byt aj internal, lebo pristupove prava .NET nemaju nic spolocne s contracts, ale kedze sa jedna o DLL, ktora je linkovana HOST musia byt pristupove prava na public.
	[ServiceContract()]
	public interface IIntGetSetContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		int GetIntValue();
		[OperationContract]
		void SetIntValue(int Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------