using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace HelloWCFLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CHelloWCFService : IHelloWCFContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CHelloWCFService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Say(string Input)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine("Message received, the body contains: {0} !",Input); 
			Console.WriteLine();

			Message		Msg=OperationContext.Current.RequestContext.RequestMessage;

			Console.WriteLine(Msg.ToString());
			Console.WriteLine();

			CInsideWCFHelper.WriteMessageAsStringToFile("Say",Msg);
		}
//-------------------------------------------------------------------------------------------------------
		public void SayWith2Params(string Input1, string Input2)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine("Message received, the body contains: {0} and {1} !",Input1,Input2);
			Console.WriteLine();

			Message		Msg=OperationContext.Current.RequestContext.RequestMessage;

			Console.WriteLine(Msg.ToString());
			Console.WriteLine();

			CInsideWCFHelper.WriteMessageAsStringToFile("SayWith2Params",Msg);
		}
//-------------------------------------------------------------------------------------------------------
		public void SayPurchaseOrder(string SomeParam, CPurchaseOrder PO)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine("Message received, the body contains: {0} and {1} !",SomeParam,PO.ToString());
			Console.WriteLine();

			Message		Msg=OperationContext.Current.RequestContext.RequestMessage;

			Console.WriteLine(Msg.ToString());
			Console.WriteLine();

			CInsideWCFHelper.WriteMessageAsStringToFile("SayPurchaseOrder",Msg);
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