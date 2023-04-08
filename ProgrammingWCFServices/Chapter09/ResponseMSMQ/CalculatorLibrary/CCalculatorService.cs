using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Transactions;
using System.Runtime.Serialization;
using System.Runtime.CompilerServices;
using System.ServiceModel;
using ResponseMSMQShared;
//-------------------------------------------------------------------------------------------------------
namespace CalculatorLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CCalculatorService : ICalculatorContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CCalculatorService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void ProxyHelper(bool Add1, string QueueEndpointName, string MethodID, int ReturnValue, ExceptionDetail Error)
		{
			CResponseCalculatorProxy			Client=null;
			string								QueueName;

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue(QueueEndpointName);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CResponseCalculatorProxy(TCPBinding,QueueName);

				// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				// Vytvorim vlastny context.
				CMyResponseContext			MyResponseContext=new CMyResponseContext(QueueEndpointName,null,MethodID);

				// Pouzijem novy context.
				using(OperationContextScope Scope=new OperationContextScope(Client.InnerChannel))
				{
					// Nastavim headers.
					CResponseMSMQHelper.SetMyResponseContext(MyResponseContext);

					// Notifikujem Response Service.
					if (Add1==true)
						Client.OnAdd1Completed(ReturnValue,Error);
					else
						Client.OnAdd2Completed(ReturnValue,Error);
				}

				Console.WriteLine("ALL OK !\n");
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=false)]
        public void Add1(int Param1, int Param2)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			CMyResponseContext		MyResponseContext=CResponseMSMQHelper.GetMyResponseContext();

			Console.WriteLine(string.Format("Add1({0},{1}), ID: {2}, FaultAddress: {3} !",Param1,Param2,MyResponseContext.MethodID,MyResponseContext.FaultAddress));

			int		ReturnValue=Param1+Param2;

			ProxyHelper(true,MyResponseContext.ResponseAddress,MyResponseContext.MethodID,ReturnValue,null);

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=false)]
        public void Add2(int Param1, int Param2)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			CMyResponseContext		MyResponseContext=CResponseMSMQHelper.GetMyResponseContext();

			Console.WriteLine(string.Format("Add1({0},{1}), ID: {2}, FaultAddress: {3} !",Param1,Param2,MyResponseContext.MethodID,MyResponseContext.FaultAddress));

			ExceptionDetail		ED=new ExceptionDetail(new Exception("SOME ERROR"));

			ProxyHelper(false,MyResponseContext.ResponseAddress,MyResponseContext.MethodID,0,ED);

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
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