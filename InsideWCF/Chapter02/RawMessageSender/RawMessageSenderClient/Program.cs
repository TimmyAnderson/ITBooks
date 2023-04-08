using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;
using System.ServiceModel;
using System.ServiceModel.Channels;
using RawMessageSenderLibrary;
//-------------------------------------------------------------------------------------------------------
namespace RawMessageSenderClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static Message GenerateMessage(Int32 ProductID, Int32 Quantity) 
		{
			MemoryStream				MS=null;
			XmlDictionaryWriter			Writer=null;
			XmlDictionaryReader			Reader=null;

			try
			{
				// MS sa nesmie zatvorit - asi ho Message interne pouziva.
				MS=new MemoryStream();
			    Writer=XmlDictionaryWriter.CreateTextWriter(MS, Encoding.UTF8, false);
    
				Writer.WriteStartElement("Order");
				Writer.WriteElementString("ProdID", ProductID.ToString());
				Writer.WriteElementString("Qty", Quantity.ToString());
				Writer.WriteEndElement();

				Writer.Flush();
				MS.Position=0;

				// !!! Reader sa nesmie zatvorit - asi ho Message interne pouziva.
				Reader=XmlDictionaryReader.CreateTextReader(MS, XmlDictionaryReaderQuotas.Max);

				// Vytvorim RAW MESSAGE, ktoru poslem do SERVICE.
				Message					Ret=Message.CreateMessage(MessageVersion.Soap12WSAddressing10, String.Empty, Reader);

				return(Ret);
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
			finally
			{
				if (Writer!=null)
				{
					Writer.Close();
					Writer=null;
				}

				if (MS!=null)
				{
					// !!! Nesmim zatvarat stream - Message ho pouziva.
					MS=null;
				}

				if (Reader!=null)
				{
					// !!! Nesmim zatvarat stream - Message ho pouziva.
					Reader=null;
				}
			}

			return(null);
		}
//-------------------------------------------------------------------------------------------------------
		static void Test()
		{
			bool								WriteToConsole=false;

			CRawMessageSenderProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			WSHttpBinding						WSBinding=new WSHttpBinding(SecurityMode.None);

			// Nastavim textovy encoder.
			WSBinding.MessageEncoding=WSMessageEncoding.Text;

			try
			{
				Client=new CRawMessageSenderProxy(WSBinding,"http://localhost:4000/IRawMessageSenderContract");

				// Otvaram kanal.
				Client.Open();

				Message							Msg=null;

				for (int i=0;i<10;i++)
				{
					Msg=GenerateMessage(i,i);

					// Vytvorim si vlastnu MessageId.
					UniqueId					UniqueID=new UniqueId(i.ToString());

					// Nastavim MessageId.
					Msg.Headers.MessageId=UniqueID;
					// Nastavim Action.
					Msg.Headers.Action="urn:SubmitOrder";   

					Console.WriteLine("Sending Message # {0} !",UniqueID.ToString());

					if (WriteToConsole==true)
					{
						// !!! Jednu Message mozem iba raz zapistat. A to bud na disk, alebo ju poslat do Service.
						CInsideWCFHelper.WriteClientMessageToFile(Msg.Headers.MessageId.ToString(),Msg);
					}
					else
					{
						// Volam SERVICE.
						Client.SubmitOrder(Msg);
					}
				}

				Console.WriteLine("ALL OK !\n");
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E,"FATAL EXCEPTION"));
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						Client.Close();
						Console.WriteLine(String.Format("Close() OK"));
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
			}
		}
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