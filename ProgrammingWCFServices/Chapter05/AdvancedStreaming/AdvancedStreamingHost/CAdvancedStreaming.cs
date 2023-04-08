using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace AdvancedStreamingHost
{
//-------------------------------------------------------------------------------------------------------
	//[ServiceBehavior(InstanceContextMode=InstanceContextMode.Single)]
	public class CAdvancedStreaming : IAdvancedStreaming
	{
//-------------------------------------------------------------------------------------------------------
		private static void MyStreamFillThread(object Param)
		{
			CMyTestStream			MyStream=(CMyTestStream) Param;

			Console.WriteLine("MyStreamFillThread() 111 !");

			// Trochu zbrzdim zapis - iba na test ci ak je LENGTH streamu ==0 sa HNED SKONCI CITANIE.
			//Thread.Sleep(3*1000);

			Console.WriteLine("MyStreamFillThread() 222 !");

			CStreamHelper.SlowFillStream(MyStream);

			Console.WriteLine("MyStreamFillThread() 333 !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!!!! Tato funkcia vracia NENAPLNENY STREAM - aby demonstrovala, ze PO VRATENI STREAM HO UZ NIE JE MOZNE DALEJ PLNIT.
		public CMyTestStream GetNotFullyFilledStream()
		{
			Console.WriteLine("GetMyTestStream() 111 !");

			Thread				T=new Thread(MyStreamFillThread);
			CMyTestStream		S=new CMyTestStream("SERVICE");

			T.Start(S);

			// Pockam, kym sekundarny thread aspon TROCHU nenaplni Stream.
			Thread.Sleep(10*1000);

			Console.WriteLine("GetMyTestStream() 222 !");

			// !!!!!! Ked operacie skonci, tak sa ZOBERIE IBA TA CAST STREAMU, KTORY JE UZ NAPLNENY. AK HO WORKER THREAD ESTE DALEJ NAPLNA, TAK TOTO SA UZ IGNORUJE a NEPRENESIE NA CLIENT.
			return(S);
		}
//-------------------------------------------------------------------------------------------------------
		public CMyTestStream GetAlreadyFilledStream()
		{
			Console.WriteLine("GetAlreadyFilledMyTestStream() 111 !");

			Thread				T=new Thread(MyStreamFillThread);
			CMyTestStream		S=new CMyTestStream("SERVICE");

			// CELY STREAM SA HNED NAPLNI A VRATI - no PRENASANY JE STREAMOVANE - AZ KED HO CLIENT VYZIADA.
			CStreamHelper.FastFillStream(S);

			Console.WriteLine("GetAlreadyFilledMyTestStream() 222 !");

			return(S);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------