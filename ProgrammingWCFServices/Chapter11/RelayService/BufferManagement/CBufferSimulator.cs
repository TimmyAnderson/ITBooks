using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel.Channels;
using Microsoft.ServiceBus;
//-------------------------------------------------------------------------------------------------------
namespace BufferManagement
{
//-------------------------------------------------------------------------------------------------------
	public class CBufferSimulator
	{
//-------------------------------------------------------------------------------------------------------
        private MessageBufferClient								MClient;
        private MessageBufferPolicy								MPolicy;
        private TransportClientEndpointBehavior					MCredential;
        private Uri												MURI;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public CBufferSimulator()
        {
            Console.Write("Your Service Namespace: ");

            string				ServiceNamespace=Console.ReadLine();

            Console.Write("Your Issuer Name: ");

            string				IssuerName=Console.ReadLine();

            Console.Write("Your Issuer Secret: ");

            string				IssuerSecret=Console.ReadLine();

            // Vytvorim POLICY pre BUFFER.
            MPolicy=new MessageBufferPolicy();
            MPolicy.Authorization=AuthorizationPolicy.Required;
            MPolicy.MaxMessageCount=10;
            MPolicy.ExpiresAfter=TimeSpan.FromMinutes(5);
            MPolicy.TransportProtection=TransportProtectionPolicy.AllPaths;
            
            // Vytvorim CREDENTIALS pre ENDPOINT, aby som mohol citam MESSAGES z BUFFER.
            MCredential=new TransportClientEndpointBehavior();
            MCredential.CredentialType=TransportClientCredentialType.SharedSecret;
            MCredential.Credentials.SharedSecret.IssuerName=IssuerName;
            MCredential.Credentials.SharedSecret.IssuerSecret=IssuerSecret;

            // Vytvorim URI pre BUFFER.
            MURI=ServiceBusEnvironment.CreateServiceUri("https", ServiceNamespace, "MessageBuffer");
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public void CreateMessageBuffer()
        {
            Console.Write("Press [Enter] to create the message buffer: ");
            Console.ReadLine();

            // Vytvorim MESSAGE BUFFER.
            MClient=MessageBufferClient.CreateMessageBuffer(MCredential,MURI,MPolicy);

            Console.WriteLine(string.Format("Message buffer created at [{0}].",MClient.MessageBufferUri));
        }
//-------------------------------------------------------------------------------------------------------
        public void SendMessages()
        {
            Console.Write("Press [Enter] to connect to the message buffer: ");
            Console.ReadLine();

            // Ziskam referenciu na EXISTUJUCI BUFFER.
            MessageBufferClient		ClientBuffer=MessageBufferClient.GetMessageBuffer(MCredential,MURI);

            Console.WriteLine(string.Format("Connected to the message buffer at [{0}].",ClientBuffer.MessageBufferUri));

            Console.Write("Press [Enter] to send messages to the message buffer: ");
            Console.ReadLine();

            for (int i=1;i<=3;i++)
            {
				string				Body=string.Format("<<My MESSAGE {0}>>",(i+1));

				// Vytvorim WCF MESSAGE, ktoru chcem zaslat do BUFFER.
                Message				MSG=Message.CreateMessage(MessageVersion.Default, string.Empty, Body);

				// Zaslem MESSAGE do BUFFER.
                ClientBuffer.Send(MSG);

                Console.WriteLine(string.Format("Sent message with body [{0}] to the message buffer.", Body));

				// Uzatvorim MESSAGE OBJEKT.
                MSG.Close();
            }
        }
//-------------------------------------------------------------------------------------------------------
        public void RetrieveMessages()
        {
			// WCF MESSAGE.
            Message				RetrievedMessage;

            Console.Write("Press [Enter] to retrieve the first message in the message buffer: ");
            Console.ReadLine();

            // Vyberiem 1. MESSAGE z BUFFER.
            RetrievedMessage=MClient.Retrieve();

            Console.WriteLine(string.Format("Retrieved message with body [{0}].",RetrievedMessage.GetBody<string>()));

			// Uzatvorim MESSAGE OBJEKT.
            RetrievedMessage.Close();
        
            Console.Write("Press [Enter] to retrieve the next message from the message buffer: ");
            Console.ReadLine();

            // Vyberiem 2. MESSAGE z BUFFER.
            RetrievedMessage=MClient.Retrieve();

            Console.WriteLine(string.Format("Retrieved message with body [{0}].",RetrievedMessage.GetBody<string>()));

			// Uzatvorim MESSAGE OBJEKT.
            RetrievedMessage.Close();

            Console.Write("Press [Enter] to lock, peek, and delete the next message from the message buffer: ");
            Console.ReadLine();

            // Urobim LOCK a PEEK 3. MESSAGE z BUFFER.
            Message				LockedMessage=MClient.PeekLock();

			// Zmazem LOCKED MESSAGE z BUFFER.
            MClient.DeleteLockedMessage(LockedMessage);

            Console.WriteLine(string.Format("Message with body [{0}] locked, peeked, and then deleted.",LockedMessage.GetBody<string>()));

			// Uzatvorim MESSAGE OBJEKT.
            LockedMessage.Close();
        }
//-------------------------------------------------------------------------------------------------------
        public void DeleteMessageBuffer()
        {
            Console.Write("Press [Enter] to delete the message buffer: ");
            Console.ReadLine();

            // Zmazem BUFFER.
            MClient.DeleteMessageBuffer();

            Console.WriteLine(string.Format("Message buffer at [{0}] was deleted.",MClient.MessageBufferUri));
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------