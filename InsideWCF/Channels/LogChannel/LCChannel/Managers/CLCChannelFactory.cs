using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using Log;
//-------------------------------------------------------------------------------------------------------
namespace LCChannel
{
//-------------------------------------------------------------------------------------------------------
// Trieda implementuje CF mojho CH. Jeho ulohou je vytvorit CH.
// Generic parameter TShape je Shape CH.
// !!! TShape aj keby som nemusel implementovat som dal preto aby CLCChannelFactory mohol vytvarat moje CH pre kazdy Shape. Mohol by som o robit aj tak, zeby som vytoril pre kazdy Shape vlastny CL je vsak je zbytocne pracne, ked mi staci iba jedna trieda.
// !!! Pri studiu triedy pozerat nazvoslovie premennych, kde je pouzite slovo 'Channel' (CH) a kde 'Factory' (CF).
//-------------------------------------------------------------------------------------------------------
	internal class CLCChannelFactory<TShape> : ChannelFactoryBase<TShape>
	{
//-------------------------------------------------------------------------------------------------------
		// Referencia na nasledujuci CF v CS.
		// !!! Musi mat rovnaky Shape ako moj CF, kedze vsetky CH v CS musia mat rovnaky Shape.
		protected IChannelFactory<TShape>						MInnerFactory;
		// Data pre log. Sluzi aj ako property CF ku ktorej sa pristupuje cez GetProperty<>().
		protected CLogData										MLogData;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLCChannelFactory(BindingContext Context, CLogData LogData)
			// Zaslem timouts z Binding.
			: base(Context.Binding)
		{
			MLogData=LogData;

			MLogData.WriteLog(CDebugHelper.GetConstructorCallString());

			// Necham BindingContext, aby vytvoril nasledujuci CF v CS.
			// !!! Predavam mu Shape - to preto, lebo Shape je pre KAZDY CH V CS ROVNAKY. V JEDNOM CS NEMOZU BYT CH S ROZLICNYM SHAPE.
			// !!! BuildInnerChannelFactory() zoberie nasledujuci BE (odstrani aktualny z internej koleckie cez Remove()) a zavola jeho metodu BuildChannelFactory().
			MInnerFactory=Context.BuildInnerChannelFactory<TShape>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Jej ulohou je vytvorit CH (POZOR NIE CF, ale CH) podla zvoleneho Shape.
		// Je to vlastne factory metoda a je private, kedze sa vyuziva iba v ramci triedy.
		// !!! Ako parameter mu da nasledujuci CH v CS, aby pri vytvoreni mojho CH mal ten referenciu na dalsi CH v CS.
		// Metoda sa vyuziva v OnCreateChannel() metodach.
		private TShape WrapChannel(TShape InnerChannel)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			if(InnerChannel==null)
				throw(new ArgumentNullException("InnerChannel cannot be null !", "InnerChannel"));

			if(typeof(TShape)==typeof(IOutputChannel))
				return((TShape)(object)new CLCOutputChannel(this, (IOutputChannel) InnerChannel, MLogData));
			if(typeof(TShape)==typeof(IRequestChannel))
				return((TShape)(object)new CLCRequestChannel(this, (IRequestChannel) InnerChannel, MLogData));
			if(typeof(TShape)==typeof(IDuplexChannel))
				return((TShape)(object)new CLCDuplexChannel(this, (IDuplexChannel) InnerChannel, MLogData));
			if(typeof(TShape)==typeof(IOutputSessionChannel))
				return((TShape)(object)new CLCOutputSessionChannel(this, (IOutputSessionChannel) InnerChannel, MLogData));
			if(typeof(TShape)==typeof(IRequestSessionChannel))
				return((TShape)(object)new CLCRequestSessionChannel(this, (IRequestSessionChannel) InnerChannel, MLogData));
			if(typeof(TShape)==typeof(IDuplexSessionChannel))
				return((TShape)(object)new CLCDuplexSessionChannel(this, (IDuplexSessionChannel) InnerChannel, MLogData));

			// Chybny Shape.
			throw new ArgumentException(String.Format("Invalid channel shape passed: {0} !", InnerChannel.GetType()));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		protected override TShape OnCreateChannel(EndpointAddress Address, Uri Via)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Vola CreateChannel() nasledujuceho CF. Nie OnCreateChannel() pretoze ta je protected.
			TShape				InnerChannel=MInnerFactory.CreateChannel(Address, Via);

			// Volanim WrapChannel() a poslanim ako parametra uz vytvoreneho CH mozem takto vytvarat CS, kedze CH obsahuje referenciu na CH nizsie v CS a tym padom mi vznika CS.
			return(WrapChannel(InnerChannel));
		}
//-------------------------------------------------------------------------------------------------------
		// Virtualna metoda.
		// !!!!!! Pozor toto nie je abstraktna, ale virtualna metoda.
		protected override void OnAbort()
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString(1));

			// !!! Vola Abort() predka, ktory zabezpeci aby sa vsetky CH vytvorene tymto CF boli abortovane.
			// A Abort() v CH zas zabezpeci, aby sa Abort siril aj do predkov CH. takze kazy CH bude abortovany.
			//base.Abort();

			// !!!!!!!!!!!!! Ked som toto volanie nedal potom sa mi pri uzatvarani proxy vyhodila chyba, ktora je popisana ComplexTest.Program.
			// ????? Vyzera to tak, ze nestaci vola predka, ktory uzatvara CH, ale aj MInnerFactory, ktory uzatvori CF.
			// TODO: ????? Neviem ci poradie je OK.
			MInnerFactory.Abort();

			MLogData.WriteLog(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
		// Virtualna metoda.
		// !!!!!! Pozor toto nie je abstraktna, ale virtualna metoda.
		// !!!!!! Preto je treba volat predka.
		protected override IAsyncResult OnBeginClose(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			IAsyncResult		AR;
			
			// !!! Vola OnBeginClose() predka, ktory zabezpeci aby sa vsetky CH vytvorene tymto CF boli abortovane.
			//AR=base.BeginClose(Timeout, Callback, State);

			// !!!!!!!!!!!!! Ked som toto volanie nedal potom sa mi pri uzatvarani proxy vyhodila chyba, ktora je popisana ComplexTest.Program.
			// ????? Vyzera to tak, ze nestaci vola predka, ktory uzatvara CH, ale aj MInnerFactory, ktory uzatvori CF.
			AR=MInnerFactory.BeginClose(Timeout, Callback, State);

			return(AR);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		protected override IAsyncResult OnBeginOpen(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Vola BeginOpen() nasledujuceho CF. Nie OnBeginOpen() pretoze ta je protected.
			return(MInnerFactory.BeginOpen(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		// Virtualna metoda.
		// !!!!!! Pozor toto nie je abstraktna, ale virtualna metoda.
		// !!!!!! Preto je treba volat predka.
		protected override void OnClose(TimeSpan Timeout)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// !!! Vola Close() predka, ktory zabezpeci aby sa vsetky CH vytvorene tymto CF boli uzavrete.
			// A Close() v CH zas zabezpeci, aby sa Close siril aj do predkov CH. Takze kazdy CH bude uzavrety.
			//base.Close(Timeout);

			// !!!!!!!!!!!!! Ked som toto volanie nedal potom sa mi pri uzatvarani proxy vyhodila chyba, ktora je popisana ComplexTest.Program.
			// ????? Vyzera to tak, ze nestaci vola predka, ktory uzatvara CH, ale aj MInnerFactory, ktory uzatvori CF.
			// TODO: ????? Neviem ci poradie je OK.
			MInnerFactory.Close(Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		// Virtualna metoda.
		// !!!!!! Pozor toto nie je abstraktna, ale virtualna metoda.
		// !!!!!! Preto je treba volat predka.
		protected override void OnEndClose(IAsyncResult Result)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// !!! Vola OnEndClose() predka, ktory zabezpeci aby sa vsetky CH vytvorene tymto CF boli abortovane.
			//base.EndClose(Result);

			// !!!!!!!!!!!!! Ked som toto volanie nedal potom sa mi pri uzatvarani proxy vyhodila chyba, ktora je popisana ComplexTest.Program.
			// ????? Vyzera to tak, ze nestaci vola predka, ktory uzatvara CH, ale aj MInnerFactory, ktory uzatvori CF.
			// TODO: ????? Neviem ci poradie je OK.
			MInnerFactory.EndClose(Result);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		protected override void OnEndOpen(IAsyncResult Result)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Vola EndOpen() nasledujuceho CF. Nie OnEndOpen() pretoze ta je protected.
			MInnerFactory.EndOpen(Result);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		protected override void OnOpen(TimeSpan Timeout)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Vola Open() nasledujuceho CF. Nie OnOpen() pretoze ta je protected.
			MInnerFactory.Open(Timeout);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Virtualna metoda.
		// Definovana v rozhrani IChannelFactory.
		// Sluzi na ziskanie property lubovolneho CF v stacku.
		// Ak dany CF nema takuto property posle volanie nizsie do stacku.
		public override T GetProperty<T>()
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			if (typeof(T)==typeof(CLogData))
				return((T) ((object) MLogData));

			return(MInnerFactory.GetProperty<T>());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------