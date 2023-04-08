using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace PerSessionReleaseInstanceOnCompleteService
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