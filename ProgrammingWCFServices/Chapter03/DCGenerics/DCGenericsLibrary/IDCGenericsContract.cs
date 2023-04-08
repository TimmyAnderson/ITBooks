using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DCGenericsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IDCGenericsContract<T>
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void SendInt(CGenericClass1<int> Value);
		[OperationContract]
		void SendGenerics(CGenericClass1<T> Value);

		// Toto uz WCF nezoberie a HOST HODI EXCEPTION.
		/*
		[OperationContract]
		void SendGenericsMethod<M>(CGenericClass1<M> Value);
		*/
		[OperationContract]
		void SendCName1(CGenericClass1<CName> Value);
		[OperationContract]
		void SendCName2(CGenericClass2<CName> Value);
		[OperationContract]
		void SendCName3(CGenericClass3<CName> Value);
		[OperationContract]
		void SendCName4(CGenericClass4<CName> Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------