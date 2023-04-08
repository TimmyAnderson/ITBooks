using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace AppDomainTests
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CCrossAppDomainTestNoMarshal
	{
//-------------------------------------------------------------------------------------------------------
		private string											MSharedField="Timmy Anderson";
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void CallbackCalledInRemoteAppDomain()
		{
			try
			{
				Console.WriteLine(string.Format("Code CallbackCalledInRemoteAppDomain() is EXECUTED in APP DOMAIN [{0}] with SHARED FIELD [{1}] !",AppDomain.CurrentDomain.FriendlyName,MSharedField));

				MSharedField="Jenny Thompson";

				Console.WriteLine(string.Format("Code CallbackCalledInRemoteAppDomain() is EXECUTED in APP DOMAIN [{0}] with SHARED FIELD [{1}] !",AppDomain.CurrentDomain.FriendlyName,MSharedField));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("Code CallbackCalledInRemoteAppDomain() EXCEPTION [{0}] in APP DOMAIN [{1}] !",E.Message,AppDomain.CurrentDomain));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void CreateAppDomain()
		{
			try
			{
				Console.WriteLine(string.Format("Code CreateAppDomain() is EXECUTED in APP DOMAIN [{0}] with SHARED FIELD [{1}] !",AppDomain.CurrentDomain.FriendlyName,MSharedField));

				AppDomain											Domain=AppDomain.CreateDomain("OtherDomain");

				// !!!!!! CODE HODI EXCEPTION, pretoze sa pristupuje k METHOD vytvorenej v OBJECT patriacej INEJ APP DOMAIN a CLASS CCrossAppDomainTest NEMOZE byt MARSHALLED-BY-REFERENCE (nededi z MarshalByRefObject) ani MARSHALLED-BY-VALUE (NIE je SERIALIZABLE).
				Domain.DoCallBack(CallbackCalledInRemoteAppDomain);

				Console.WriteLine(string.Format("Code CreateAppDomain() is EXECUTED in APP DOMAIN [{0}] with SHARED FIELD [{1}] !",AppDomain.CurrentDomain.FriendlyName,MSharedField));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("Code CreateAppDomain() EXCEPTION [{0}] in APP DOMAIN [{1}] !",E.Message,AppDomain.CurrentDomain));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------