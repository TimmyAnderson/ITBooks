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
	Trieda implementuje FaultConverter. Vyuziva sa iba v Transport CH, v metode GetProperty<T>().
	!!! Nemusel by som u implementovat, kedze ju pouzivam iba v Transport CH a v MSDN dokumentacii sa pise, ze tu by sa uz mal pouzivat default FaultConverter() (ziskam ho z FaultConverter.GetDefaultFaultConverter()). Ja tento default FaultConverter aj ozaj v oboch metodach pouzivam a moj FaultConverter vlastne iba zaloguje volanie tychto metod.

	FaultConverter sluzi na serizalizaciu a deserializaciu Exception, teda konverziu z Exception do FaultMessage a naopak.

	!!! FaultConverter sa WCF vyziada ked dojde k Exception.
	1. Pri internych chybach CH. Ak napriklad Message neobsahovala <To> tak ho WCF vyvolala aby na stranu Sender zaslal informaciu o tom, ze Message nema <To>.
	2. Ak Service hodi Exception. Vtedy sa tiez vyvola a je mozem tuto Exception zachytit a vytvorit vlastny FaultMessage. Aj vzhladom na odporucanie v dokumentacii som napokon to nechal na default FaultConverter, ale mohol by som si vyrobit vlastnu FaultMessage.
*/
//-------------------------------------------------------------------------------------------------------
	public class CFTCFaultConverter : FaultConverter
	{
//-------------------------------------------------------------------------------------------------------
		// Verzia SOAP pouzita pri konverzii Exception na FaultMessage a naopak.
		private MessageVersion									MVersion;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFTCFaultConverter(MessageVersion Version)
		{
			MVersion=Version;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Konverzia FaultMessage na Exception.
        protected override bool OnTryCreateException(Message Message, MessageFault Fault, out Exception Exception)
        {
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);

			// !!! V dokumentacii sa pise, ze TCH by mali delegovat volania na FaultConverter.GetDefaultFaultConverter().
			return(FaultConverter.GetDefaultFaultConverter(MVersion).TryCreateException(Message,Fault,out Exception));
        }
//-------------------------------------------------------------------------------------------------------
		// Konverzia Exception na FaultMessage.
        protected override bool OnTryCreateFaultMessage(Exception Exception, out Message Message)
        {
			CSettings.Log.Write(string.Format("!!!!! FAULT !!!!! - '{0}' !",CDebugHelper.GetExceptionString(Exception)),ELogRecordType.E_LRT_EXCEPTION);

			return(FaultConverter.GetDefaultFaultConverter(MVersion).TryCreateFaultMessage(Exception,out Message));

			// !!! Aj ked toto je korektna implementacia, tak v dokumentacii sa pise, ze TCH by mali delegovat volania na FaultConverter.GetDefaultFaultConverter().

			/*
			MessageFault		Fault;

			if (Exception.GetType()==typeof(FaultException<InvalidOperationException>))
			{
				Fault=MessageFault.CreateFault(new FaultCode("IOE"),new FaultReason(Exception.Message));
				Message=Message.CreateMessage(MVersion,Fault,"");
				return(true);
			}
			else
			{
				Message=null;
				return(false);				
			}
			*/
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------