using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using EHExtensionCallbackLibrary;
//-------------------------------------------------------------------------------------------------------
namespace EHExtensionCallbackClient
{
//-------------------------------------------------------------------------------------------------------
	[CMyErrorHandlerBehavior()]
	class CEHExtensionCallbackCatcher : IEHExtensionCallbackCallback
	{
//-------------------------------------------------------------------------------------------------------
		public void OnEvent(string Message)
		{
			Console.WriteLine(string.Format("OnEvent() - FROM SERVER: {0} !",Message));

			throw(new ObjectDisposedException("THIS IS OBJECT DISPOSED EXCEPTION"));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------