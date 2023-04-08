using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.Net.Security;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-----------------------------------------------------------------------------------------------------------
namespace ReliableSession_FaultEvent_Shared
{
//-----------------------------------------------------------------------------------------------------------
	public class CSimpleTestInterface : ISimpleTestInterface
	{
//-----------------------------------------------------------------------------------------------------------
		public string ToUpper(string Param)
		{
			Console.WriteLine(string.Format("ToUpper() CALLED - [{0}] !",Param));

			return(Param.ToUpper());
		}
//-----------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------