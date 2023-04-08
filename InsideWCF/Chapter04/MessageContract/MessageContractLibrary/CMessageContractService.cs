using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace MessageContractLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CMessageContractService : IMessageContractContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CMessageContractService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SomeDCOperation(CMyDataContract MyDataContract)
		{
			Console.Clear();
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine(string.Format("Message: {0} !",MyDataContract.ToString())); 
			Console.WriteLine();

			Console.WriteLine(OperationContext.Current.RequestContext.RequestMessage.ToString());
		}
//-------------------------------------------------------------------------------------------------------
		public void SomeMCOperation(CMyMessageContract MyMessageContract)
		{
			Console.Clear();
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine(string.Format("Message: {0} !",MyMessageContract.ToString()));
			Console.WriteLine();

			Console.WriteLine(OperationContext.Current.RequestContext.RequestMessage.ToString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine(CDebugHelper.GetDestructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------