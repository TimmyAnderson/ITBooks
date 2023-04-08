using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Description;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace MessageHeadersHost
{
//-------------------------------------------------------------------------------------------------------
	public class CService1 : IService1
	{
//-------------------------------------------------------------------------------------------------------
		public void Operation1(ref string Message)
		{
			Console.WriteLine("CService1.Operation1() CALLED !");

			try
			{
				CCustomHeaderData					ResponseMessageCustomHeaderData=new CCustomHeaderData("Atreyu","",12);
				MessageHeader<CCustomHeaderData>	ResponseMessageTMH=new MessageHeader<CCustomHeaderData>(ResponseMessageCustomHeaderData);
				MessageHeader						ResponseMessageMH=ResponseMessageTMH.GetUntypedHeader("ResponseOperation","NS");

				// Pridam HEADER do OUTGOING MESSAGE COLLECTION - pre RESPONSE MESSAGE.
				OperationContext.Current.OutgoingMessageHeaders.Add(ResponseMessageMH);

				Message+=" [Operation1]";

				// Citam aktualny MessageHeader.
				CCustomHeaderData					Header=OperationContext.Current.IncomingMessageHeaders.GetHeader<CCustomHeaderData>("Operation1","NS");

				Console.WriteLine(string.Format("!!! OPERATION 1 - HEADER: [{0}] !",Header));

				// Volam INY SERVICE.
				using (ChannelFactory<IService2> CF=new ChannelFactory<IService2>("SE"))
				{
					using(IDisposable D=CF.CreateChannel() as IDisposable)
					{
						IService2		Proxy=D as IService2;

						// !!! Musim vytvorit CUSTOM OperationContextScope.
						using(OperationContextScope S=new OperationContextScope(D as IContextChannel))
						{
							try
							{
								CCustomHeaderData	CustomHeaderData=new CCustomHeaderData("Jenny","Thompson",13);

								// Prihodim data do MessageHeaders.
								MessageHeader<CCustomHeaderData>	TMH=new MessageHeader<CCustomHeaderData>(CustomHeaderData);

								MessageHeader		MH=TMH.GetUntypedHeader("Operation2","NS");

								OperationContext.Current.OutgoingMessageHeaders.Add(MH);

								Proxy.Operation2(ref Message);
							}
							catch(Exception E)
							{
								Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
							}

							// !!! Tu sa OperationContext ukonci sa nahradi sa POVODNYM OperationContextScope.
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
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------