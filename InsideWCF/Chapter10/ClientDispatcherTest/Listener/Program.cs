using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.IO;
using System.Xml;
using Contracts;
//-------------------------------------------------------------------------------------------------------
namespace Listener
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void ReceiveRequest(IAsyncResult AR)
		{
			// Get the channel stack.
			IReplyChannel						Channels=(IReplyChannel) AR.AsyncState;

			// Get the requestContext.
			RequestContext						Context=Channels.EndReceiveRequest(AR);

			// Show the received message.
			Console.WriteLine(string.Format("\nRequest Received: [{0}] !", Context.RequestMessage.ToString()));

			// !!!!! Rucne vytvorim RESPONSE MESSAGE.

			ContractDescription					CD=ContractDescription.GetContract(typeof(IRestaurantService3));
			OperationDescription				OD=CD.Operations.Find("RequestReservation");

			// !!!!! Ziskam MessageDescription pre RESPONSE MESSAGE.
			MessageDescription					ResponseMessageDescription=OD.Messages.Find("http://contoso.com/Restaurant/IRestaurantService3/RequestReservationResponse");
			
			// !!! Vytvorim SERIALIZER pre TELO RESPONSE MESSAGE, ktore je typu 'int?'.
			// !!!!! Ako ROOT NAME a ROOT NAMESPACE pouzijem hodnoty z RESPONSE MESSAGE pre Body.
			DataContractSerializer				Serializer=new DataContractSerializer(typeof(int?), ResponseMessageDescription.Body.ReturnValue.Name, ResponseMessageDescription.Body.ReturnValue.Namespace);

			MemoryStream						Stream=new MemoryStream();
			XmlDictionaryWriter					Writer=XmlDictionaryWriter.CreateTextWriter(Stream, Encoding.UTF8, false);

			// !!! Musim zapisat WRAPPER ELEMENT, ktoreho meno je 'RequestReservationResponse'. Da sa ziskat z WrapperName ResponseMessageDescription. Namespace 'http://contoso.com/Restaurant' som ziskal z WrapperNamespace ResponseMessageDescription.
			Writer.WriteStartElement(ResponseMessageDescription.Body.WrapperName,ResponseMessageDescription.Body.WrapperNamespace);

			// Zapisem RETURN VALUE.
			Serializer.WriteObject(Writer, 123);

			// Ukoncim ELEMENT.
			Writer.WriteEndElement();

			// Zapisem obsah MESSAGE do MEMORY STREAM.
			Writer.Flush();
			Writer.Close();

			Stream.Position=0;

			// Vytvorim READER, ktory bude cistat obsah MEMORY STREAM.
			XmlDictionaryReader					Reader=XmlDictionaryReader.CreateTextReader(Stream,new XmlDictionaryReaderQuotas());

			// Ako parameter davam READER.
			Message								Reply=Message.CreateMessage(MessageVersion.Soap11,ResponseMessageDescription.Action,Reader);

			// Send the reply.
			Context.Reply(Reply);

			// Close the context.
			Context.Close();

			// Close the channels.
			Channels.Close();

			Reader.Close();
			Stream.Close();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="LISTENER";

			// Create a binding.
			BasicHttpBinding					Binding=new BasicHttpBinding();
			
			// Create an address.
			Uri									Address=new Uri("http://localhost:4000/MyListener");

			// Build the ChannelListener stack.
			IChannelListener<IReplyChannel>		ListenerStack=Binding.BuildChannelListener<IReplyChannel>(Address, new BindingParameterCollection());

			// Open the listener stack.
			ListenerStack.Open();

			// BasicHttp will return (no sessions).
			IReplyChannel						ReceiveChannels=ListenerStack.AcceptChannel();

			// Open the channel stack.
			ReceiveChannels.Open();

			// Try to Receive a Message, need to do async.
			ReceiveChannels.BeginReceiveRequest(new AsyncCallback(ReceiveRequest), ReceiveChannels);

			// Cleanup.
			ListenerStack.Close();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------