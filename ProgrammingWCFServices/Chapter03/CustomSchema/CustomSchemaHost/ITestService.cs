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
    [ServiceContract(Name="VehReservationService", Namespace="http://www.opentravel.org/OTA/2003/05")]
	// !!!!! MUSIM POUZIT XML SERIALIZER.
    [XmlSerializerFormat(Style=OperationFormatStyle.Document, Use=OperationFormatUse.Literal)]
	public interface ITestService
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract]
        OTA_VehResRS ReserveVehicle([MessageParameter(Name="OTA_VehResRQ")]OTA_VehResRQ ReservationReq);
        [OperationContract]
        OTA_VehResRS MyTest(OTA_VehResRQ Req1, OTA_VehResRS Req2);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------