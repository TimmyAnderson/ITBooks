using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace CustomSchemaHost
{
//-------------------------------------------------------------------------------------------------------
	public class CTestService : ITestService
	{
//-------------------------------------------------------------------------------------------------------
		public OTA_VehResRS ReserveVehicle([MessageParameter(Name="OTA_VehResRQ")] OTA_VehResRQ ReservationReq)
		{
			Console.WriteLine(string.Format("EchoToken: [{0}] !", ReservationReq.EchoToken));

			// Nejaky Response iba na simulaciu.
            OTA_VehResRS			Resp=new OTA_VehResRS();

			Resp.EchoToken=ReservationReq.EchoToken;

			return(Resp);
		}
//-------------------------------------------------------------------------------------------------------
		public OTA_VehResRS MyTest(OTA_VehResRQ Req1, OTA_VehResRS Req2)
		{
			Console.WriteLine(string.Format("EchoToken_1: [{0}], EchoToken_2: [{1}] !", Req1.EchoToken,Req2.EchoToken));

			return(Req2);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------