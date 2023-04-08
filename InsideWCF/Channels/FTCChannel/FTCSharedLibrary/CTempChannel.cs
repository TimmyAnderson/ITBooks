using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
	internal class CTempChannel : IDuplexSessionChannel
	{
//-------------------------------------------------------------------------------------------------------
		private CFTCSessionID									MSessionID;
		// !!! Moja implementacia TryReceive.
		private	CTryReceiveChannelThread						MTRCT;
		private	bool											MShouldClose;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public event EventHandler								Closed;
		public event EventHandler								Closing;
		public event EventHandler								Opened;
		public event EventHandler								Opening;
		public event EventHandler								Faulted;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTempChannel(CFTCSessionID SessionID, CChannelAcceptChannelThread ChannelAcceptChannelThread)
		{
			MSessionID=SessionID;

			Console.WriteLine(string.Format("CHANNEL WITH SESSION: {0} WAS CREATED !",MSessionID.SessionID));

			MTRCT=new CTryReceiveChannelThread(SessionID,@"..\..\..\!Packets1",Test.MMessageEncoder,ChannelAcceptChannelThread);
			MShouldClose=false;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTryReceiveChannelThread							TRCT
		{
			get
			{
				return(MTRCT);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												ShouldClose
		{
			get
			{
				return(MShouldClose);
			}
			set
			{
				MShouldClose=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		public Uri												Via
		{
			get
			{
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public IDuplexSession									Session
		{
			get
			{
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public EndpointAddress									LocalAddress
		{
			get
			{
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CommunicationState								State
		{
			get
			{
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public EndpointAddress									RemoteAddress
		{
			get
			{
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Tuto metodu som pridal iba preto, aby mi nepouzity EVENT nahlasil WARNING.
		protected virtual void OnClosed(object Sender, EventArgs EA)
		{
			if (Closed!=null)
				Closed(Sender,EA);
		}
//-------------------------------------------------------------------------------------------------------
		// Tuto metodu som pridal iba preto, aby mi nepouzity EVENT nahlasil WARNING.
		protected virtual void OnClosing(object Sender, EventArgs EA)
		{
			if (Closing!=null)
				Closing(Sender,EA);
		}
//-------------------------------------------------------------------------------------------------------
		// Tuto metodu som pridal iba preto, aby mi nepouzity EVENT nahlasil WARNING.
		protected virtual void OnOpened(object Sender, EventArgs EA)
		{
			if (Opened!=null)
				Opened(Sender,EA);
		}
//-------------------------------------------------------------------------------------------------------
		// Tuto metodu som pridal iba preto, aby mi nepouzity EVENT nahlasil WARNING.
		protected virtual void OnOpening(object Sender, EventArgs EA)
		{
			if (Opening!=null)
				Opening(Sender,EA);
		}
//-------------------------------------------------------------------------------------------------------
		// Tuto metodu som pridal iba preto, aby mi nepouzity EVENT nahlasil WARNING.
		protected virtual void OnFaulted(object Sender, EventArgs EA)
		{
			if (Faulted!=null)
				Faulted(Sender,EA);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginTryReceive(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			Console.WriteLine(string.Format("CHANNEL WITH SESSION: {0} WAS BeginTryReceive !",MSessionID.SessionID));

			// HACK: Moj KOD !!!
			return(MTRCT.BeginTryReceive(Timeout,Callback,State));
		}
//-------------------------------------------------------------------------------------------------------
		public bool EndTryReceive(IAsyncResult Result, out Message Message)
		{
			// HACK: Moj KOD !!!
			bool		Ret=MTRCT.EndTryReceive(Result,out Message);

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		public void Open(TimeSpan Timeout)
		{
			// HACK: Moj KOD !!!
			MTRCT.Start();
		}
//-------------------------------------------------------------------------------------------------------
		public void Close(TimeSpan Timeout)
		{
			// HACK: Moj KOD !!!
			MTRCT.Stop();

			Console.WriteLine(string.Format("CHANNEL WITH SESSION: {0} WAS CLOSED !",MSessionID.SessionID));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginReceive(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginReceive(AsyncCallback Callback, object State)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginWaitForMessage(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public Message EndReceive(IAsyncResult Result)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public bool EndWaitForMessage(IAsyncResult Result)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public Message Receive(TimeSpan Timeout)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public Message Receive()
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public bool TryReceive(TimeSpan Timeout, out Message Message)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public bool WaitForMessage(TimeSpan Timeout)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public T GetProperty<T>() where T:class
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public void Abort()
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginClose(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginClose(AsyncCallback Callback, object State)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginOpen(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginOpen(AsyncCallback Callback, object State)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public void Close()
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public void EndClose(IAsyncResult Result)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public void EndOpen(IAsyncResult Result)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public void Open()
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginSend(Message Message, TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginSend(Message Message, AsyncCallback Callback, object State)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public void EndSend(IAsyncResult Result)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public void Send(Message Message, TimeSpan Timeout)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public void Send(Message Message)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------