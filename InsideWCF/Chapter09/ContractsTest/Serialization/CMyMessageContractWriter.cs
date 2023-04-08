using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.Runtime.Serialization;
using System.IO;
using System.Xml;
using System.ServiceModel.Description;
using System.ServiceModel.Channels;
using Contracts;
//-------------------------------------------------------------------------------------------------------
namespace Serialization
{
//-------------------------------------------------------------------------------------------------------
	sealed class CMyMessageContractWriter : BodyWriter
	{
//-------------------------------------------------------------------------------------------------------
		private string											MWrapperNamespace;
		private string											MWrapperName;
		private DateTime										MNewReservationDate;
		private string											MNewDateElementName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CMyMessageContractWriter(CChangeReservationNewDateTime Instance)
			: base(true)
		{
			MWrapperNamespace="http://contoso.com/Restaurant";
			MWrapperName="ChangeReservationNewDateTime";
			MNewReservationDate=(DateTime) Instance.NewDateTime;
			MNewDateElementName="NewReservationDate";
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override void OnWriteBodyContents(XmlDictionaryWriter Writer)
		{
			Writer.WriteStartElement(MWrapperName, MWrapperNamespace);
			Writer.WriteElementString(MNewDateElementName, MNewReservationDate.ToString("u"));
			Writer.WriteEndElement();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------