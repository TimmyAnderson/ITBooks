using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Security.Principal;
using CallbackAuthenticationLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CallbackAuthenticationClient
{
//-------------------------------------------------------------------------------------------------------
	class CCallbackAuthenticationCatcher : ICallbackAuthenticationCallback
	{
//-------------------------------------------------------------------------------------------------------
		public void OnCallback()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Console.WriteLine("CALLBACK CALLED !");

			WindowsIdentity		WI=(WindowsIdentity) Thread.CurrentPrincipal.Identity;

			Console.WriteLine(string.Format("Name: {0} !",WI.Name));

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------