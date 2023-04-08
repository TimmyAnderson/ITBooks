using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace DirectBindingUsage
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			Console.Title="TEST";

			try
			{
				// Vytvorim BINDING.
				BasicHttpBinding							Binding=new BasicHttpBinding();
				
				// Nastavim TIMEOUTS.
				Binding.OpenTimeout=TimeSpan.FromDays(1);
				Binding.ReceiveTimeout=TimeSpan.FromDays(2);
				Binding.SendTimeout=TimeSpan.FromDays(3);
				Binding.CloseTimeout=TimeSpan.FromDays(4);

				// Urcim adresu na ktorej bude prijmat MESSAGES.
				Uri											Address=new Uri("http://localhost:4000/MyListener");
					
				// Pomocou BINDING vytvorim CHANNEL LISTENER STACK.
				IChannelListener<IReplyChannel>				ListenerStack=Binding.BuildChannelListener<IReplyChannel>(Address,new BindingParameterCollection());

				// Otvorim CHANNEL LISTENER STACK.
				ListenerStack.Open();

				Console.WriteLine("CHANNEL LISTENER STACK OPENED !");

				// HTTP BASIC BINDING pri volani metody AcceptChannel() OKAMZITE VRACIA NOVY CHANNEL.
				// !!! V pripade TCP BINDING by naopak AcceptChannel() bol BLOKOVANY az do prichodu NOVEJ POZIADAVKY na vytvorenie CHANNEL.
				IReplyChannel								ReceiveChannelStack=ListenerStack.AcceptChannel();

				// Otvorim novy CHANNEL.
				ReceiveChannelStack.Open();

				Console.WriteLine("CHANNEL STACK (RECEIVING) OPENED !");

				// Cakam na prichod MESSAGE v INOM THREADE.
				ReceiveChannelStack.BeginReceiveRequest(new AsyncCallback(ReceiveRequest),ReceiveChannelStack);

				Console.WriteLine("WAITING for MESSAGE to RECEIVE !");

				// Vytvorim CHANNEL FACTORY STACK.
				IChannelFactory<IRequestChannel>			ChannelFactoryStack=Binding.BuildChannelFactory<IRequestChannel>(new BindingParameterCollection());

				// Otvorim CHANNEL FACTORY STACK.
				ChannelFactoryStack.Open();

				Console.WriteLine("CHANNEL FACTORY STACK OPENED !");

				// Vytvorim CHANNEL STACK z CHANNEL FACTORY STACK.
				IRequestChannel								SendChannels=ChannelFactoryStack.CreateChannel(new EndpointAddress(Address));

				// Otvorim CHANNEL STACK.
				SendChannels.Open();

				Console.WriteLine("CHANNEL STACK (SENDING) OPENED !");

				Console.WriteLine();
				Console.WriteLine();
				Console.WriteLine();
				Console.WriteLine("Press any key to send MESSAGE !");
				Console.ReadLine();

				// Vytvorim REQUEST MESSAGE.
				Message										RequestMessage=Message.CreateMessage(MessageVersion.Soap11, "urn:SomeAction","Hi there !");

				Console.WriteLine();
				Console.WriteLine();
				Console.WriteLine();

				// Zobrazim RESPONSE MESSAGE.
				Console.WriteLine(string.Format("Message to SEND: [{0}] !",RequestMessage.ToString()));

				// Odoslem REQUEST MESSAGE a prijmem RESPONSE MESSAGE.
				Message										ReplyMessage=SendChannels.Request(RequestMessage);

				Console.WriteLine();
				Console.WriteLine();
				Console.WriteLine();

				// Zobrazim RESPONSE MESSAGE .
				Console.WriteLine(string.Format("Received MESSAGE: [{0}] !",RequestMessage.ToString()));

				Console.WriteLine();
				Console.WriteLine();
				Console.WriteLine();
	
				Console.WriteLine(string.Format("Message RECEIVED: [{0}] !",ReplyMessage.ToString()));

				// Zavriem SENDING CHANNEL STACK.
				SendChannels.Close();

				// Zavriem CHANNEL FACTORY STACK.
				ChannelFactoryStack.Close();

				// Zavriem CHANNEL LISTENER STACK.
				ListenerStack.Close();
			}
			catch(Exception E)
			{
				Console.WriteLine("EXCEPTION: [{0}] !",E.Message);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void ReceiveRequest(IAsyncResult AR)
		{
			// Ziskam CHANNEL, ktory som si preniesol cez AsyncState.
			IReplyChannel									Channels=(IReplyChannel) AR.AsyncState;

			// Kedze sa jedna o REQUEST-RESPONSE MEP, tak musim RequestContext.
			RequestContext									Context=Channels.EndReceiveRequest(AR);

			Console.WriteLine();
			Console.WriteLine();
			Console.WriteLine();

			// Zobrazim MESSAGE.
			Console.WriteLine(string.Format("Message RECEIVED: [{0}] !",Context.RequestMessage.ToString()));

			// Vytvorim RESPONSE MESSAGE.
			Message											ReplyMessage=Message.CreateMessage(MessageVersion.Soap11, "urn:SomeReplyAction","Message back back !");

			// Odoslem REPLY.
			Context.Reply(ReplyMessage);

			// Uzatvorim RequestContext.
			Context.Close();

			// Uzatvorim CHANNEL.
			Channels.Close();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
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