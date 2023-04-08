using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.IO;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace StreamingLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CStreamingService : IStreamingContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CStreamingService()
		{
			Console.WriteLine("CStreamingService CONSTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SendStream(Stream Message)
		{
			try
			{
				Console.WriteLine("CStreamingService.SendStream() STARTED !");

				CStreamHelper.ReadStream(Message);

				// !!! Stream sa musi uzavriet.
				Message.Close();
				Console.WriteLine("CStreamingService.SendStream() STREAM CLOSED !");

				Console.WriteLine("CStreamingService.SendStream() FINISHED !");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("ReadStreamThread()EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
        public Stream ReceiveStream()
        {
			Console.WriteLine("CStreamingService.ReceiveStream() STARTED !");

			Stream			S=new CMyStream();

			CStreamHelper.FillStream(S);

			// Presuniem Stream na zaciatok.
			S.Seek(0,SeekOrigin.Begin);

			// !!! Tu nemam kedy Stream uzavriet, takze sa spolieham, ze ho zavrie WCF a CLIENT.

			Console.WriteLine("CStreamingService.ReceiveStream() FINISHED !");

			return(S);
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CStreamingService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------