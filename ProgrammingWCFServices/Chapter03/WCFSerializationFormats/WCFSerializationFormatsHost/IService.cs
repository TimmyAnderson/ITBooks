using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace WCFSerializationFormatsHost
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	//[DataContractFormat(Style=OperationFormatStyle.Document)]
	//[DataContractFormat(Style=OperationFormatStyle.Rpc)]
	// Mozem pouzit IBA s Test2() v CLIENT a MUSIM ZAKOMENTOVAT Method1().
	//[XmlSerializerFormat(Style=OperationFormatStyle.Document)]
	// Mozem pouzit IBA s Test2() v CLIENT.
	[XmlSerializerFormat(Style=OperationFormatStyle.Rpc)]
	public interface IService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		CName1 Method1(CName1 Name1);
		[OperationContract]
		CName2 Method2(CName2 Name2);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------