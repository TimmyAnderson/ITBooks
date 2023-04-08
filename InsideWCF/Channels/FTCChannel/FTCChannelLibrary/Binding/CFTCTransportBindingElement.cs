using System;
using System.Collections.Generic;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Text;
using FTCSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace FTCChannelLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Trieda implementujuca moj Transport BE. Vytvara moju CF a CL.
*/
//-------------------------------------------------------------------------------------------------------
    public class CFTCTransportBindingElement : TransportBindingElement
    {
//-------------------------------------------------------------------------------------------------------
        public CFTCTransportBindingElement()
        {
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);
        }
//-------------------------------------------------------------------------------------------------------
        public CFTCTransportBindingElement(CFTCTransportBindingElement Original)
        {
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public override string									Scheme
        {
            get 
            {
                return("ftc");
            }
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public override BindingElement Clone()
        {
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Klon vytvorim tak, ze vytvorim novu instanciu a pouzijem jej copy-constructor.
            return(new CFTCTransportBindingElement(this));
        }
//-------------------------------------------------------------------------------------------------------
        public override T GetProperty<T>(BindingContext Context)
        {
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Iba preposlem volanie do Context.
            return(Context.GetInnerProperty<T>());
        }
//-------------------------------------------------------------------------------------------------------
        public override bool CanBuildChannelFactory<TChannel>(BindingContext Context)
        {
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Akceptujem iba Duplex Session CH.
            if (typeof(TChannel)==typeof(IDuplexSessionChannel))
                return(true);
            else
                return(false);

			// !!! Kedze toto je Transport BE tak uz nevolam Context, kedze toto je najnizsi BE v stacku.
        }
//-------------------------------------------------------------------------------------------------------
        public override bool CanBuildChannelListener<TChannel>(BindingContext Context)
        {
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Akceptujem iba Duplex Session CH.
            if (typeof(TChannel)==typeof(IDuplexSessionChannel))
                return(true);
            else
                return(false);

			// !!! Kedze toto je Transport BE tak uz nevolam Context, kedze toto je najnizsi BE v stacku.
        }
//-------------------------------------------------------------------------------------------------------
        public override IChannelFactory<TChannel> BuildChannelFactory<TChannel>(BindingContext Context)
        {
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Vytvorim moj CF.
			return((IChannelFactory<TChannel>)(object)new CFTCChannelFactory(this,Context));
        }
//-------------------------------------------------------------------------------------------------------
        public override IChannelListener<TChannel> BuildChannelListener<TChannel>(BindingContext Context)
        {
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Vytvorim moj CL.
            return((IChannelListener<TChannel>)(object)new CFTCChannelListener(this,Context));
        }
//-------------------------------------------------------------------------------------------------------
    }
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------