using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace MessagesTest
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static string GetMessageDirectory()
		{
			DirectoryInfo	WorkingDir=new DirectoryInfo(AppDomain.CurrentDomain.BaseDirectory);
			string			ParentDir=WorkingDir.Parent.Parent.Parent.FullName;
			string			DestinationDir=string.Format("{0}\\Messages",ParentDir);

			return(DestinationDir);
		}
//-------------------------------------------------------------------------------------------------------
	    private static void PrintMessageVersion(String Name, MessageVersion Version)
		{
	        Console.WriteLine("Name={0}\nEnvelope={1}\nAddressing={2} !\n", Name, Version.Envelope.ToString(), Version.Addressing.ToString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    private static void GetMessageVersions()
		{
			MessageVersion		Version=MessageVersion.Default;

			PrintMessageVersion("Default", Version);

			Version=MessageVersion.Soap11WSAddressing10;
			PrintMessageVersion("Soap11WSAddressing10", Version);

			Version=MessageVersion.Soap11WSAddressingAugust2004;
			PrintMessageVersion("Soap11WSAddressingAugust2004", Version);

			Version=MessageVersion.Soap12WSAddressing10;
			PrintMessageVersion("Soap12WSAddressing10", Version);

			Version=MessageVersion.Soap12WSAddressingAugust2004;
			PrintMessageVersion("Soap12WSAddressingAugust2004", Version);

			Version=MessageVersion.None;
			PrintMessageVersion("None", Version);
		}
//-------------------------------------------------------------------------------------------------------
	    private static void SimpleMessageCreation()
		{
			Message				Msg=Message.CreateMessage(MessageVersion.Soap12WSAddressing10, "SomeAction", "Hello There");

			Console.WriteLine(Msg.ToString());

			Msg.Close();
		}
//-------------------------------------------------------------------------------------------------------
		private static void CreateMessagesFromGraph()
		{
			CName				Name=new CName("Timmy","Anderson");
			CPersonInfo			PersonInfo=new CPersonInfo(Name,12);

			// Vytvorenie MESSAGE, kde <Body> je objekt PersonInfo.
			Message				Msg=Message.CreateMessage(MessageVersion.Soap12WSAddressing10,"SomeAction",PersonInfo);
			
			// Pridam vlastny header.
			Msg.Headers.Add(MessageHeader.CreateHeader("MyName","MyNamespace","MyValue"));

			Console.WriteLine(Msg.ToString());

			try
			{
				using (XmlWriter W=new XmlTextWriter(string.Format("{0}\\WriteMessageMethodTest.msg",GetMessageDirectory()),UTF8Encoding.UTF8))
				{
					Msg.WriteMessage(W);
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("ERROR: [{0}] !",E.Message));
			}

			Msg.Close();
		}
//-------------------------------------------------------------------------------------------------------
		private static void CreateMessagesFromXmlReader()
		{
			CName				Name=new CName("Timmy","Anderson");
			CPersonInfo			PersonInfo=new CPersonInfo(Name,12);

			// Vytvorenie MESSAGE, kde <Body> je objekt PersonInfo.
			Message				Msg=Message.CreateMessage(MessageVersion.Soap12WSAddressing10,"SomeAction",PersonInfo);
			
			// Pridam vlastny header.
			Msg.Headers.Add(MessageHeader.CreateHeader("MyName","MyNamespace","MyValue"));

			Console.WriteLine("ORIGINAL MESSAGE:");
			Console.WriteLine(Msg.ToString());

			try
			{
				using (XmlWriter W=new XmlTextWriter(string.Format("{0}\\WriteMessageMethodTest.msg",GetMessageDirectory()),UTF8Encoding.UTF8))
				{
					Msg.WriteMessage(W);
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("ERROR: [{0}] !",E.Message));
				return;
			}
			finally
			{
				Msg.Close();
			}

			try
			{
				using (XmlReader R=new XmlTextReader(string.Format("{0}\\WriteMessageMethodTest.msg",GetMessageDirectory())))
				{
					// Vytvorim Message z XmlReader.
					Message		MsgRead=Message.CreateMessage(MessageVersion.Soap12WSAddressing10,"SomeAction",R);
					
					Console.WriteLine("\n\nNEW MESSAGE:");
					Console.WriteLine(Msg.ToString());

					Console.WriteLine();
					Console.WriteLine(string.Format("State: [{0}] !",MsgRead.State));

					MsgRead.Close();

					Console.WriteLine();
					Console.WriteLine(string.Format("State: [{0}] !",MsgRead.State));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("ERROR: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void CreateMessagesFromBodyWriter()
		{
			CName						Name=new CName("Timmy","Anderson");
			CPersonInfo					PersonInfo=new CPersonInfo(Name,12);

			// Vytvorenie MESSAGE, kde <Body> je objekt PersonInfo.
			Message						Msg=Message.CreateMessage(MessageVersion.Soap12WSAddressing10,"SomeAction",PersonInfo);
			
			// Pridam vlastny header.
			Msg.Headers.Add(MessageHeader.CreateHeader("MyName","MyNamespace","MyValue"));

			Console.WriteLine("ORIGINAL MESSAGE:");
			Console.WriteLine(Msg.ToString());

			try
			{
				using (XmlWriter W=new XmlTextWriter(string.Format("{0}\\WriteMessageMethodTest.msg",GetMessageDirectory()),UTF8Encoding.UTF8))
				{
					Msg.WriteMessage(W);
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("ERROR: [{0}] !",E.Message));
				return;
			}
			finally
			{
				Msg.Close();
			}

			try
			{
				// BODY je vytvoreny pomocou BodyWriter.
				Message					MsgRead=Message.CreateMessage(MessageVersion.Soap12WSAddressing10,"SomeAction",new CBodyWriter(string.Format("{0}\\WriteMessageMethodTest.msg",GetMessageDirectory())));

				Console.WriteLine("\n\nNEW MESSAGE:");

				Console.WriteLine(MsgRead.ToString());

				MsgRead.Close();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("ERROR: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void CreateFaultMessages()
		{
			// Reprezentuje FAULT DETAIL.
			CName				Name=new CName("Timmy","Anderson");
			CPersonInfo			PersonInfo=new CPersonInfo(Name,12);

			// Name NESMIE MAT MEDZERU.
			FaultCode			FC=new FaultCode("SomeCode");
			FaultReason			FR=new FaultReason("Some Reason");

			// Vytvorim MessageFault.
			MessageFault		MF=MessageFault.CreateFault(FC,FR,PersonInfo);

			Message				MsgSource=Message.CreateMessage(MessageVersion.Soap12WSAddressing10,MF,"SomeAction");
			MessageBuffer		MB=MsgSource.CreateBufferedCopy(10000);
			Message				Msg1=MB.CreateMessage();

			// Pridam vlastny header.
			Msg1.Headers.Add(MessageHeader.CreateHeader("MyName","MyNamespace","MyValue"));

			Console.WriteLine("MESSAGE:");
			Console.WriteLine(Msg1.ToString());

			try
			{
				using (XmlWriter W=new XmlTextWriter(string.Format("{0}\\WriteFaultMessage.msg",GetMessageDirectory()),UTF8Encoding.UTF8))
				{
					Msg1.WriteMessage(W);
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("ERROR: [{0}] !",E.Message));
				return;
			}
			finally
			{
				Msg1.Close();
			}

			Message				Msg2=MB.CreateMessage();

			// Vytvorim MessageFault z Message.
			MessageFault		MessageFaultFromMessage=MessageFault.CreateFault(Msg2,10000);

			Console.WriteLine("\n\nMESSAGE FAULT:");
			Console.WriteLine(string.Format("Message.IsFault: [{0}] !",Msg2.IsFault));
			Console.WriteLine(string.Format("Code.Name: [{0}] !",MessageFaultFromMessage.Code.Name));
			Console.WriteLine(string.Format("Reason: [{0}] !",MessageFaultFromMessage.Reason));
			Console.WriteLine(string.Format("Detail: [{0}] !",MessageFaultFromMessage.GetDetail<CPersonInfo>()));

			Msg2.Close();
		}
//-------------------------------------------------------------------------------------------------------
		private static void GetBodyTest()
		{
			CName				Person=new CName("Timmy","Anderson");
			Message				Message=Message.CreateMessage(MessageVersion.Default, "Action", Person);

			Message.Headers.Add(MessageHeader.CreateHeader("MyName","MyNamespace","MyValue"));

			XmlDictionaryReader	Reader=Message.GetReaderAtBodyContents();         
			var					NewMessage=Message.CreateMessage(MessageVersion.Default, "NewAction", Reader);

			Console.WriteLine(string.Format("Original MESSAGE: [{0}] !",Message));
			Console.WriteLine();
			Console.WriteLine(string.Format("New MESSAGE: [{0}] !",NewMessage));
			Console.WriteLine();
			Console.WriteLine(string.Format("BODY: [{0}] !",NewMessage.GetBody<CName>()));

			Message.Close();
		}
//-------------------------------------------------------------------------------------------------------
		private static void CustomMessageHeader()
		{
			CName						Name=new CName("Timmy","Anderson");
			CPersonInfo					PersonInfo=new CPersonInfo(Name,12);

			// Vytvorenie MESSAGE, kde <Body> je objekt PersonInfo.
			Message						Msg=Message.CreateMessage(MessageVersion.Soap12WSAddressing10,"SomeAction",PersonInfo);
			
			// Pridam vlastny header.
			Msg.Headers.Add(MessageHeader.CreateHeader("MyName","MyNamespace","MyValue"));

			// Vytvorim CUSTOM HEADER.
			CCustomMessageHeader		CustomHeader=new CCustomMessageHeader("CUSTOM NAME","CUSTOM NAMESPACE","CUSTOM VALUE");

			// Pridam CUSTOM HEADER.
			Msg.Headers.Add(CustomHeader);

			Msg.Headers.MessageId=new UniqueId();

			EndpointAddress				AddressTo=new EndpointAddress("net.tcp://Address_To");
			EndpointAddress				AddressFaultTo=new EndpointAddress("net.tcp://Address_FaultTo");
			EndpointAddress				AddressReplyTo=new EndpointAddress("net.tcp://Address_ReplyTo");

			AddressTo.ApplyTo(Msg);

			Msg.Headers.FaultTo=AddressFaultTo;
			Msg.Headers.ReplyTo=AddressReplyTo;

			// Najdem INDEX pre HEADER.
			int							HeaderIndex=Msg.Headers.FindHeader("MyName","MyNamespace");

			if (HeaderIndex!=-1)
			{
				string					HeaderValue=Msg.Headers.GetHeader<string>(HeaderIndex);

				Console.WriteLine(string.Format("HEADER VALUE: [{0}] !",HeaderValue));
			}

			Console.WriteLine();
			Console.WriteLine(string.Format("State: [{0}] !",Msg.State));
			Console.WriteLine(string.Format("To: [{0}] !",Msg.Headers.To));
			Console.WriteLine(string.Format("MessageId: [{0}] !",Msg.Headers.MessageId));
			Console.WriteLine(string.Format("RelatesTo: [{0}] !",Msg.Headers.RelatesTo));
			Console.WriteLine(string.Format("From: [{0}] !",Msg.Headers.From));
			Console.WriteLine(string.Format("FaultTo: [{0}] !",Msg.Headers.FaultTo));
			Console.WriteLine(string.Format("ReplyTo: [{0}] !",Msg.Headers.ReplyTo));

			Console.WriteLine("\n\nORIGINAL MESSAGE:");
			Console.WriteLine(Msg.ToString());

			try
			{
				using (XmlWriter W=new XmlTextWriter(string.Format("{0}\\WriteMessageMethodTest.msg",GetMessageDirectory()),UTF8Encoding.UTF8))
				{
					Msg.WriteMessage(W);
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("ERROR: [{0}] !",E.Message));
				return;
			}
			finally
			{
				Msg.Close();
			}

			Message						MsgRead=null;

			try
			{
				using (XmlReader R=new XmlTextReader(string.Format("{0}\\WriteMessageMethodTest.msg",GetMessageDirectory())))
				{
					// Vytvorim Message z XmlReader.
					MsgRead=Message.CreateMessage(MessageVersion.Soap12WSAddressing10,"SomeAction",R);

					Console.WriteLine("\n\nNEW MESSAGE:");
					Console.WriteLine(Msg.ToString());
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("ERROR: [{0}] !",E.Message));
			}
			finally
			{
				MsgRead.Close();
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//GetMessageVersions();
			//SimpleMessageCreation();
			//CreateMessagesFromGraph();
			//CreateMessagesFromXmlReader();
			//CreateMessagesFromBodyWriter();
			//CreateFaultMessages();
			//GetBodyTest();
			CustomMessageHeader();
		
			Console.WriteLine();
			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------