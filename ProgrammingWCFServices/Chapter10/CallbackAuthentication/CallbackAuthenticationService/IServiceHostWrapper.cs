using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace CallbackAuthenticationService
{
//-------------------------------------------------------------------------------------------------------
	public interface IServiceHostWrapper
	{
//-------------------------------------------------------------------------------------------------------
		ServiceHost												Host
		{
			get;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		void StartService();
		void StopService();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------