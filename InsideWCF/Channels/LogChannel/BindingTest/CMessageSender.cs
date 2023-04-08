using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using System.ServiceModel;
using Log;
//-------------------------------------------------------------------------------------------------------
namespace BindingTest
{
//-------------------------------------------------------------------------------------------------------
	class CMessageSender<TChannelShape> where TChannelShape : class, IChannel
	{
//-------------------------------------------------------------------------------------------------------
		private Uri												MAddress;
		private Binding											MBinding;
		private IChannelFactory<TChannelShape>					MChannelFactoryStack;
		private TChannelShape									MChannel;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMessageSender(Uri Address, Binding Binding)
		{
			MAddress=Address;
			MBinding=Binding;
			MChannel=null;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Start()
		{
			if (MChannel!=null)
				throw(new Exception("Sender is opened !"));

			try
			{
				MChannelFactoryStack=MBinding.BuildChannelFactory<TChannelShape>(new BindingParameterCollection());
				MChannelFactoryStack.Open();
				MChannel=MChannelFactoryStack.CreateChannel(new EndpointAddress(MAddress));

				MChannel.Open();
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E,"CF FATAL ERROR"));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void Stop()
		{
			if (MChannel==null)
				throw(new Exception("Sender is closed !"));

			try
			{
				if (MChannel!=null)
				{
					// Pri Duplex CH nesmie mi ostat ziadna M nesparcovana (cez volanie Receive()) ked dosla do CH.
					MChannel.Close();
					MChannel=null;
				}

				if (MChannelFactoryStack!=null)
				{
					MChannelFactoryStack.Close();
					MChannelFactoryStack=null;
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E,"CF FATAL ERROR"));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void SendMessage(string Body)
		{
			// !!! Pozor na verzu SOAP. Musi sediet s tou, ktoru pouziva B.
			Message		M=Message.CreateMessage(MBinding.MessageVersion, "urn:SomeAction",Body);

			PrintMessage(M,"OUTPUT MESSAGE");
			
			try
			{
				if ((MChannel is IDuplexChannel)==true)
				{
					IDuplexChannel	DC=(IDuplexChannel) MChannel;

					DC.Send(M);

					// !!! Pri Duplex CH nesmie mi ostat ziadna M nesparcovana (cez volanie Receive()) ked dosla do CH.

					// Kedze Receiver som naprogramoval tak aby VZDY poslal na zaslanu M nejaku odpoved tak musim ju vycitat aby som mohol CH neskor korekne uzavriet cez Close().
					// !!! Preto volam Receive(). Mozem synchronne, lebo viem, ze M dojde a bude iba jedna. Verziu s TimeSpan pouzit nemozem, kedze po preteceny TimeSpan by sa CH dostal do FAULTED state.
					Message			RespM=DC.Receive();

					// Vypisem M.
					PrintMessage(M,"DUPLEX RESPONSE MESSAGE");
				}
				else if ((MChannel is IOutputChannel)==true)
				{
					IOutputChannel	OC=(IOutputChannel) MChannel;

					OC.Send(M);
				}
				else if ((MChannel is IRequestChannel)==true)
				{
					IRequestChannel	RC=(IRequestChannel) MChannel;
					Message			MR;

					MR=RC.Request(M);
					PrintMessage(MR,"RESPONSE MESSAGE");
				}
				else
					throw(new InvalidOperationException("Unknown channel !"));
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E,"CF FATAL ERROR"));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private void PrintMessage(Message M, string PrintHeader)
		{
			Console.WriteLine(PrintHeader);
			Console.WriteLine(M.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------