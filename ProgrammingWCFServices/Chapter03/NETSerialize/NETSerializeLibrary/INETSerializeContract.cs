using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace NETSerializeLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract()]
	public interface INETSerializeContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		CSimpleName GetSimpleName();
		[OperationContract]
		void PrintSimpleName(CSimpleName SimpleName);
		[OperationContract]
		CNameWithAddress GetNameWithAddress();
		[OperationContract]
		void PrintNameWithAddress(CNameWithAddress NameWithAddress);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------