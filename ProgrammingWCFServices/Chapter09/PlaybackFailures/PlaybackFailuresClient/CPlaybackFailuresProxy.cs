using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using PlaybackFailuresLibrary;
//-------------------------------------------------------------------------------------------------------
namespace PlaybackFailuresClient
{
//-------------------------------------------------------------------------------------------------------
	public class CPlaybackFailuresProxy : ClientBase<IPlaybackFailuresContract>, IPlaybackFailuresContract
	{
//-------------------------------------------------------------------------------------------------------
		public CPlaybackFailuresProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void PrintText(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.PrintText(Message);
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowExceptionWithTransaction1(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.ThrowExceptionWithTransaction1(Message);
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowExceptionWithTransaction2(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.ThrowExceptionWithTransaction2(Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------