using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Runtime.Serialization;
using MessageHeadersHost;
//-------------------------------------------------------------------------------------------------------
namespace InterceptorSharedClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			try
			{
				using(ChannelFactory<IService1> CF=new ChannelFactory<IService1>("SE"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						try
						{
							IService1				Proxy=Disp as IService1;
							string					Message="Client";

							using (OperationContextScope S=new OperationContextScope(Proxy as IContextChannel ))
							{
								CCustomHeaderData	CustomHeaderData=new CCustomHeaderData("Timmy","Anderson",12);

								// Prihodim data do MessageHeaders.
								MessageHeader<CCustomHeaderData>	TMH=new MessageHeader<CCustomHeaderData>(CustomHeaderData);

								MessageHeader		MH=TMH.GetUntypedHeader("Operation1","NS");

								OperationContext.Current.OutgoingMessageHeaders.Add(MH);

								Proxy.Operation1(ref Message);

								CCustomHeaderData	ResponseCustomData=OperationContext.Current.IncomingMessageHeaders.GetHeader<CCustomHeaderData>("ResponseOperation","NS");

								Console.WriteLine(string.Format("!!! RESPONSE MESSAGE - HEADER: [{0}] !",ResponseCustomData));
							}

							Console.WriteLine(string.Format("Message: [{0}] !",Message));
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
						}
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";
			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------