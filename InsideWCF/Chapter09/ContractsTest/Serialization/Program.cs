using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.Runtime.Serialization;
using System.IO;
using System.Xml;
using System.ServiceModel.Description;
using System.ServiceModel.Channels;
using Contracts;
//-------------------------------------------------------------------------------------------------------
namespace Serialization
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void MessageContractMessageSerializationDemo()
		{
			CChangeReservationNewDateTime	NewReservation=new CChangeReservationNewDateTime(5, DateTime.Parse("02/02/2007 9:30 PM"));
			CMyMessageContractWriter		Writer=new CMyMessageContractWriter(NewReservation);
			Message							Message=Message.CreateMessage(MessageVersion.Soap11, "urn:SomeAction", Writer);

			Message.Headers.Add(MessageHeader.CreateHeader("ReservationId", "http://contoso.com/Restaurant", 5, true));

			Console.WriteLine(Message.ToString());
		}
//-------------------------------------------------------------------------------------------------------
		private static void DataContractMessageSerializationDemo()
		{
			CRequestReservationParams	Reservation1=new CRequestReservationParams(DateTime.Parse("02/02/2007 9:30 PM"), "Dusty's", "Justin Smith");
			DataContractSerializer		Serializer=new DataContractSerializer(typeof(CRequestReservationParams), "ReservationRequest", "urn:Test");
			MemoryStream				Stream=new MemoryStream();
			XmlDictionaryWriter			Writer=XmlDictionaryWriter.CreateTextWriter(Stream, Encoding.UTF8, false);
			Message						Message=Message.CreateMessage(MessageVersion.Soap11, "urn:SomeAction", Reservation1, Serializer);

			Message.WriteBodyContents(Writer);

			Writer.Flush();

			Stream.Position=0;

			Console.WriteLine("Serialized Reservation: [{0}] !\n", new StreamReader(Stream).ReadToEnd());

			Stream.Position=0;

			XmlDictionaryReader			Reader=XmlDictionaryReader.CreateTextReader(Stream, XmlDictionaryReaderQuotas.Max);

			Message=Message.CreateMessage(MessageVersion.Soap11, Message.Headers.Action, Reader);

			CRequestReservationParams	Reservation2=Message.GetBody<CRequestReservationParams>(Serializer);

			Console.WriteLine("Deserialized Reservation:");
			Console.WriteLine("  Date: \t[{0}] !", Reservation2.ResDateTime);
			Console.WriteLine("  Party: \t[{0}] !", Reservation2.PartyName);
			Console.WriteLine("  Restaurant: \t[{0}] !\n", Reservation2.RestaurantName);
		}
//-------------------------------------------------------------------------------------------------------
		private static void DataContractSerializerDemo()
		{
			CRequestReservationParams	Reservation1=new CRequestReservationParams(DateTime.Parse("2/2/2007 9:30 PM"), "Dusty's BBQ", "Justin Smith");
			DataContractSerializer		Serializer=new DataContractSerializer(typeof(CRequestReservationParams), "ReservationRequest", "http://contoso.com/Restaurant");
			MemoryStream				Stream=new MemoryStream();
			XmlDictionaryWriter			Writer=XmlDictionaryWriter.CreateTextWriter(Stream, Encoding.UTF8, false);

			Serializer.WriteObject(Writer, Reservation1);
			Writer.Flush();

			Stream.Position=0;

			Console.WriteLine("Serialized Reservation: [{0}] !\n", new StreamReader(Stream).ReadToEnd());

			Stream.Position=0;

			XmlDictionaryReader			Reader=XmlDictionaryReader.CreateTextReader(Stream, XmlDictionaryReaderQuotas.Max);

			CRequestReservationParams	Reservation2=(CRequestReservationParams) Serializer.ReadObject(Reader);

			Console.WriteLine("Deserialized Reservation:");
			Console.WriteLine("  Date: \t[{0}] !", Reservation2.ResDateTime);
			Console.WriteLine("  Party: \t[{0}] !", Reservation2.PartyName);
			Console.WriteLine("  Restaurant: \t[{0}] !\n", Reservation2.RestaurantName);
		}
//-------------------------------------------------------------------------------------------------------
		private static void ContractImportDemo()
		{
			ContractDescription		ContractDescription=ContractDescription.GetContract(typeof(IRestaurantService3));

			foreach(OperationDescription OpDesc in ContractDescription.Operations)
			{
				Console.WriteLine("\nOperation Name: [{0}] !", OpDesc.Name);
		        
				foreach(MessageDescription MsgDesc in OpDesc.Messages)
				{
					Console.WriteLine("  Message Direction: [{0}] !", MsgDesc.Direction);
					Console.WriteLine("  Message Action: [{0}] !", MsgDesc.Action);
					Console.WriteLine("  Message Type: [{0}] !", (MsgDesc.MessageType!=null) ? MsgDesc.MessageType.ToString() : "Untyped");
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="Program";

			ContractImportDemo();
			DataContractSerializerDemo();
			DataContractMessageSerializationDemo();
			MessageContractMessageSerializationDemo();

			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------