using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Trieda ja impelemntaciu rozhrania IAsyncResult (u mna ich oznacujem ako Request) a sluzia ako identifikacny objekt prenasany medzi metodami BeginTryReceive() a EndTryReceive() na identifikaciu asynchronnej operacie.
*/
//-------------------------------------------------------------------------------------------------------
	internal class CFTCTryReceiveAsyncResult : CFTCAsyncResult
	{
//-------------------------------------------------------------------------------------------------------
		// Packet do neho sa ulozi Packet (A V NOM OBSIAHNUTU Message), ktory sa v meotde EndTryReceive() posle do WCF na spracovanie.
		private CFTCPacket										MPacket;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CFTCTryReceiveAsyncResult(AsyncCallback AsyncCallback, object AsyncState, TimeSpan Timeout)
			: base(AsyncCallback,AsyncState,Timeout)
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MPacket=null;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CFTCPacket				Packet
		{
			get
			{
				lock(MSyn)
				{
					return(MPacket);
				}
			}
			private set
			{
				lock(MSyn)
				{
					MPacket=value;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Klucova metoda. Jej ulohou je odpalit interny WCF callback pre dany Request aby ten mohol vola EndTryReceive() a skrze jej out parameter dostat objekt typu Message, ktory bol ulozeny v packete.
		public void DoFinish(CFTCPacket FTCPacket)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			lock(MSyn)
			{
				// !!!!! Test na SESSION-EXIT packet. Ak ano nastavim priznak konca, ktory sa pouzije v EndTryReceive() aby ta (cez vratenie TRUE a NULL ako out Message) mohla dat najavo, ze CH sa konci.
				if (FTCPacket.MessageType==EMessageType.E_MT_STOP)
					HasClosed=true;

				MPacket=FTCPacket;
				MCompleted=true;
			}

			// Odpalim WaitHandle.
			MAsyncWaitHandle.Set();

			try
			{
				// Zavolam interny WCF callback, ktory nasledne vyvola moju EndTryReceive().
				// !!!!!! BeginInvoke() je nevyhnutnostou.
				// !!!!!! Ked som pouzil iba Invoke() doslo k DEAD-LOCKu.
				// !!!!!! DEAD-LOCK pri zaslani SESSION-EXIT Packetu, ked sa mal CH zastavit.
				// !!!!!! Dovod bol v tom, kazdy packet (aj SESSION-EXIT) sposbi vyolanie CTryReceiveChannelThread.EndTryReceive().
				// !!!!!! Pri beznych packetoch je to jedina vec co sa vykona.
				// !!!!!! Avsak pri SESSION-EXIT packete, vracia EndTryReceive true a out Message=null - ABY WCF VEDELA, ZE SA CH MA UKONCIT.
				// !!!!!! PRUSER je v tom, ze WCF zalova Close() pre CH V TOM ISTOM THREADE AKO TOTO VOLANIE.
				// !!!!!! No a kedze Close() ROBI UKONCENIE TOHTO THREADU - TOHO V KTOROM SA VYKONAVA TOTO TELO DOCHADZA K DEADLOCKU.
				// !!!!!! To preto, lebo Close() vysle event na ukoncenie tohto trheadu, ale ten visi, kedze caka az Close() SKONCI.
				// !!!!!! Riesenim je BeginInvoke(), ktora sa realizuje v inom threade. Parametre Callbeck a State mozu byt null, kedze vysledok tejto operacie ma nezaujima.
				if (MAsyncCallback!=null)
					MAsyncCallback.BeginInvoke(this,null,null);
			}
			catch(Exception E)
			{
				CSettings.Log.Write(CDebugHelper.GetExceptionString(E),ELogRecordType.E_LRT_EXCEPTION);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------