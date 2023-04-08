using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel.Channels;
using System.ServiceModel;
using Log;
//-------------------------------------------------------------------------------------------------------
namespace BindingTest
{
//-------------------------------------------------------------------------------------------------------
	class CMessageReceiver<TChannelShape> where TChannelShape : class, IChannel
	{
//-------------------------------------------------------------------------------------------------------
		private object											MSyn=new object();
		private Thread											MT=null;
		private AutoResetEvent									MExitThread;
		private Uri												MAddress;
		private Binding											MBinding;
		private TChannelShape									MChannel;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMessageReceiver(Uri Address, Binding Binding)
		{
			MExitThread=new AutoResetEvent(false);
			MAddress=Address;
			MBinding=Binding;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private bool WaitForChannel()
		{
			IChannelListener<TChannelShape>		ListenerStack=MBinding.BuildChannelListener<TChannelShape>(MAddress, new BindingParameterCollection());

			ListenerStack.Open();

			while(true)
			{
				if (MExitThread.WaitOne(0,false)==true)
					return(false);

				// !!! Ked som to tu dal, tak to tu ostalo visiet.
//				if (ListenerStack.WaitForChannel(TimeSpan.FromMilliseconds(1*1000))==true)
				{
					MChannel=ListenerStack.AcceptChannel();
					MChannel.Open();
					return(true);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private void WaitForMessage()
		{
			while(true)
			{
				try
				{
					if (MExitThread.WaitOne(0,false)==true)
						return;

					if ((MChannel is IDuplexChannel)==true)
					{
						IDuplexChannel	DC=(IDuplexChannel) MChannel;

						try
						{
							Message			M;

							/*
							// !!!!! Pri Duplex MEP ak RAZ HODI TimeoutException TAK JE CH FAULTED. !!!!!
							// V Request-Reply MEP to nevadi a TimeoutException neznamena prechod CH do FAULTED stavu.
							// !!! Teda Receive(TimeSpan) nemozem pouzit.
							M=DC.Receive(TimeSpan.FromMilliseconds(1*1000));
							*/

							// Mam dve moznosti riesenia. Bud pouzit asnychronnu verziu, alebo spoliehat sa, ze pri Close() vracia Receive() hodnotu null.

							// Riesenie cislo 1.
							/*
							// Zavolam asynchornnu BeginReceive().
							IAsyncResult	AR=DC.BeginReceive(null,null);

							// Cakam na 2 handle, bud Exit, alebo koniec BeginReceive().
							WaitHandle[]	WH=new WaitHandle[]{MExitThread,AR.AsyncWaitHandle};
							int				Index;

							// Cakam.
							if ((Index=WaitHandle.WaitAny(WH))==0)
								return;

							// Dosla M.
							M=DC.EndReceive(AR);

							// Testnem ci nie je null.
							if (M!=null)
							{
								PrintMessage(M,"INPUT MESSAGE");

								Message		MOut=GetResponseMessage("Hi there back");

								DC.Send(MOut);
							}
							else
							{
								// Ak bola M null potom sa CH uzatvoril a ja koncim trhead.
								Console.WriteLine("No message !");
								return;
							}
							*/
							
							// Riesenie cislo 2.

							// Budem sa spomiehat nato, ze Receive() ked je CH uzatvarany cez Close() vracia null namiesto M. A teda thread koncim ked pride mu ako navratova hodnota s M null.
							M=DC.Receive();

							// Testnem ci nie je null.
							if (M!=null)
							{
								PrintMessage(M,"INPUT MESSAGE");

								Message		MOut=GetResponseMessage("Hi there back");

								DC.Send(MOut);
							}
							else
							{
								// Ak bola M null potom sa CH uzatvoril a ja koncim trhead.
								Console.WriteLine("No message !");
								return;
							}
						}
						catch
						{
						}
					}
					else if ((MChannel is IInputChannel)==true)
					{
						IInputChannel	IC=(IInputChannel) MChannel;

						try
						{
							Message		M;
								
							M=IC.Receive(TimeSpan.FromMilliseconds(1*1000));

							PrintMessage(M,"INPUT MESSAGE");
						}
						catch
						{
						}
					}
					else if ((MChannel is IReplyChannel)==true)
					{
						IReplyChannel	RC=(IReplyChannel) MChannel;

						try
						{
							RequestContext	ReqC;
								
							ReqC=RC.ReceiveRequest(TimeSpan.FromMilliseconds(1*1000));

							PrintMessage(ReqC.RequestMessage,"INPUT MESSAGE");
							SendResponse(ReqC);
						}
						catch
						{
						}
					}
					else
						throw(new InvalidOperationException("Unknown channel !"));
				}
				catch(Exception E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E,"CF FATAL ERROR"));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private Message GetResponseMessage(string Body)
		{
			// !!! Pozor na verzu SOAP. Musi sediet s tou, ktoru pouziva B.
			Message		M=Message.CreateMessage(MBinding.MessageVersion, "urn:SomeReplyAction", "Hi there back");

			return(M);
		}
//-------------------------------------------------------------------------------------------------------
		private void SendResponse(RequestContext ReqC)
		{
			Message		Reply=GetResponseMessage("Hi there back");

			ReqC.Reply(Reply);
			ReqC.Close();
		}
//-------------------------------------------------------------------------------------------------------
		private void PrintMessage(Message M, string PrintHeader)
		{
			Console.WriteLine(PrintHeader);
			Console.WriteLine((M!=null) ? M.ToString() : "NULL");
		}
//-------------------------------------------------------------------------------------------------------
		private void ThreadMethod()
		{
			try
			{
				MBinding.OpenTimeout=TimeSpan.FromDays(1);
				MBinding.ReceiveTimeout=TimeSpan.FromDays(2);
				MBinding.SendTimeout=TimeSpan.FromDays(3);
				MBinding.CloseTimeout=TimeSpan.FromDays(4);

				if (WaitForChannel()==true)
					WaitForMessage();

				// !!! Nesmie sa CH ukoncit, ked je este nejake nespracovana M - cez Receive().
				// Tu vsak uz mam istotu, ze bola spracovana.
				MChannel.Close();
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E,"CL FATAL ERROR"));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Start()
		{
			lock(MSyn)
			{
				if (MT!=null)
					throw(new Exception("Receiver is opened !"));

				MT=new Thread(ThreadMethod);
				MT.Start();
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void Stop()
		{
			lock(MSyn)
			{
				MExitThread.Set();

				try
				{
					if (MT.Join(10*1000)==false)
						MT.Abort();
				}
				catch(Exception E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				finally
				{
					MT=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------