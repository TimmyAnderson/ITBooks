using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using FTCSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace FTCChannelLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Trieda realizujuca moj B. Ma vzdy dve BE a to CFTCMessageEncodingBindingElement a CFTCTransportBindingElement.
*/
//-------------------------------------------------------------------------------------------------------
	public class CFTCBinding : Binding
	{
//-------------------------------------------------------------------------------------------------------
		// Verzia SOAP pouzita pri serializacii a deserializacii M.
		// !!! Je to zaroven jediny konfigurovatelny parameter B, ktory ovplyvnuje chovanie FTC. Dalsie su uz v triede CSettings.
		private MessageVersion									MVersion;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFTCBinding(MessageVersion Version)
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MVersion=Version;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string									Scheme
		{
			get
			{
				// Meno schemy.
				return("ftc");
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override BindingElementCollection CreateBindingElements()
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Vytvorim kolekciu BE.
			BindingElementCollection	BEC=new BindingElementCollection();

			// !!! Poradie je klucove. Transport BE musi byt posledny.

			// Pridam ME BE.
			BEC.Add(new CFTCMessageEncodingBindingElement(MVersion));
			// Pridam Transport BE.
			BEC.Add(new CFTCTransportBindingElement());

			return(BEC);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------