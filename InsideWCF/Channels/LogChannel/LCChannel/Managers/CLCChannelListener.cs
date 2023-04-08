using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using System.ServiceModel;
using Log;
//-------------------------------------------------------------------------------------------------------
namespace LCChannel
{
//-------------------------------------------------------------------------------------------------------
// Trieda implementuje CL mojho CH. Jeho ulohou je vytvorit CH.
// Generic parameter TShape je Shape CH.
// !!! TShape aj keby som nemusel implementovat som dal preto aby CLCChannelListener mohol vytvarat moje CH pre kazdy Shape. Mohol by som o robit aj tak, zeby som vytoril pre kazdy Shape vlastny CL je vsak je zbytocne pracne, ked mi staci iba jedna trieda.
// !!! Pri studiu triedy pozerat nazvoslovie premennych, kde je pouzite slovo 'Channel' (CH) a kde 'Listener' (CL).
//-------------------------------------------------------------------------------------------------------
	internal class CLCChannelListener<TShape> : ChannelListenerBase<TShape> where TShape : class, IChannel
	{
//-------------------------------------------------------------------------------------------------------
		// Referencia na nasledujuci CL v CS.
		// !!! Musi mat rovnaky Shape ako moj CL, kedze vsetky CH v CS musia mat rovnaky Shape.
		protected IChannelListener<TShape>						MInnerListener;
		// Data pre log. Sluzi aj ako property CL ku ktorej sa pristupuje cez GetProperty<>().
		protected CLogData										MLogData;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLCChannelListener(BindingContext Context, CLogData LogData)
			// Zaslem timouts z Binding.
			: base(Context.Binding)
		{
			MLogData=LogData;

			MLogData.WriteLog(CDebugHelper.GetConstructorCallString());

			// Necham BindingContext, aby vytvoril nasledujuci CL v CS.
			// !!! Predavam mu Shape - to preto, lebo Shape je pre KAZDY CH V CS ROVNAKY. V JEDNOM CS NEMOZU BYT CH S ROZLICNYM SHAPE.
			// !!! BuildInnerChannelListener() zoberie nasledujuci BE (odstrani aktualny z internej koleckie cez Remove()) a zavola jeho metodu BuildChannelListener().
			MInnerListener=Context.BuildInnerChannelListener<TShape>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override Uri				Uri
		{
			get
			{
				MLogData.WriteLog(CDebugHelper.GetMethodCallString());
				return(this.MInnerListener.Uri);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Jej ulohou je vytvorit CH (POZOR NIE CL, ale CH) podla zvoleneho Shape.
		// Je to vlastne factory metoda a je private, kedze sa vyuziva iba v ramci triedy.
		// !!! Ako parameter mu da nasledujuci CH v CS, aby pri vytvoreni mojho CH mal ten referenciu na dalsi CH v CS.
		// Metoda sa vyuziva v Accept() metodach.
		private TShape WrapChannel(TShape InnerChannel)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			if(InnerChannel==null)
				throw(new ArgumentNullException("InnerChannel cannot be null !", "InnerChannel"));

			if(typeof(TShape)==typeof(IInputChannel))
				return((TShape)(object)new CLCInputChannel(this, (IInputChannel) InnerChannel, MLogData));
			if (typeof(TShape)==typeof(IReplyChannel))
				return((TShape)(object)new CLCReplyChannel(this, (IReplyChannel) InnerChannel, MLogData));
			if (typeof(TShape)==typeof(IDuplexChannel))
				return((TShape)(object)new CLCDuplexChannel(this, (IDuplexChannel) InnerChannel, MLogData));
			if (typeof(TShape)==typeof(IInputSessionChannel))
				return((TShape)(object)new CLCInputSessionChannel(this, (IInputSessionChannel) InnerChannel, MLogData));
			if (typeof(TShape)==typeof(IReplySessionChannel))
				return((TShape)(object)new CLCReplySessionChannel(this, (IReplySessionChannel) InnerChannel, MLogData));
			if (typeof(TShape)==typeof(IDuplexSessionChannel))
				return((TShape)(object)new CLCDuplexSessionChannel(this, (IDuplexSessionChannel) InnerChannel, MLogData));

			// Chybny Shape.
			throw(new ArgumentException(String.Format("Invalid channel shape passed: {0} !", InnerChannel.GetType())));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Klucova metoda celeho CHL. Prave tato (aj ked az na urovni TCH) vytvara CH pri vytvoreni connection.
		protected override TShape OnAcceptChannel(TimeSpan Timeout)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// !!! Vola CL nizsie v CS. Az CL pre TCH moze skutocne vytvorit CH po vytvoreni connection a v navratovej hodnote ho poslat vyssie. !!! Tento moj CHL vytvori CH a preda mu referenciu na CH nizsie v stacku. CH si ho ulozi a de-facto tak sa vytvara stack, pretoze podstatou stacku je aby kazdy item mal referenciu na item nizsie v stacku a bol definovany vrchol stacku.
			TShape			InnerChannel=MInnerListener.AcceptChannel(Timeout);

			// ??? Ked sa robi Close() moze byt InnerChannel aj null.
			if (InnerChannel!=null)
				return(WrapChannel(InnerChannel));
			
			return(null);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// V tejto metode sa vykonava telo CL.
		// Mohol by tu byt napriklad nejaky inicializacny kod - AJ KED TEN SA ZVYCAJNE ROBI V TRIEDACH CH.
		// !!! Co vsak je klucove tak tu musi byt realizovana klucova business logika CL a teda predanie volania nasledujucemu CL v stacku.
		protected override IAsyncResult OnBeginAcceptChannel(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Vola BeginAcceptChannel() nasledujuceho CL. Nie OnBeginAcceptChannel() pretoze ta je protected.
			return(MInnerListener.BeginAcceptChannel(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// V tejto metode sa vykonava telo CL.
		// Mohol by tu byt napriklad nejaky inicializacny kod - AJ KED TEN SA ZVYCAJNE ROBI V TRIEDACH CH.
		// !!! Co vsak je klucove tak tu musi byt realizovana klucova business logika CL a teda predanie volania nasledujucemu CL v stacku.
		// Klucova metoda celeho CHL. Prave tato (aj ked az na urovni TCH) vytvara CH pri vytvoreni connection.
		protected override TShape OnEndAcceptChannel(IAsyncResult Result)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// !!! Vola CL nizsie v CS. Az CL pre TCH moze skutocne vytvorit CH po vytvoreni connection a v navratovej hodnote ho poslat vyssie. !!! Tento moj CHL vytvori CH a preda mu referenciu na CH nizsie v stacku. CH si ho ulozi a de-facto tak sa vytvara stack, pretoze podstatou stacku je aby kazdy item mal referenciu na item nizsie v stacku a bol definovany vrchol stacku.
			TShape			InnerChannel=MInnerListener.EndAcceptChannel(Result);

			// ??? Ked sa robi Close() moze byt InnerChannel aj null.
			if (InnerChannel!=null)
				return(WrapChannel(InnerChannel));

			return(null);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		protected override IAsyncResult OnBeginWaitForChannel(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Vola BeginWaitForChannel() nasledujuceho CL. Nie OnBeginWaitForChannel() pretoze ta je protected.
			return(MInnerListener.BeginWaitForChannel(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		protected override bool OnEndWaitForChannel(IAsyncResult Result)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Vola EndWaitForChannel() nasledujuceho CL. Nie OnEndWaitForChannel() pretoze ta je protected.
			return(MInnerListener.EndWaitForChannel(Result));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// !!! Sluzi na dotaz ci je CH prirpaveny (TEDA CONNECTION NADVIAZANA) a ja metodou Accept() mozem ziadat o jeho vytvorenie.
		protected override bool OnWaitForChannel(TimeSpan Timeout)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Vola WaitForChannel() nasledujuceho CL. Nie OnWaitForChannel() pretoze ta je protected.
			return(MInnerListener.WaitForChannel(Timeout));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		protected override void OnAbort()
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Vola Abort() nasledujuceho CL. Nie OnAbort() pretoze ta je protected.
			MInnerListener.Abort();
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		protected override IAsyncResult OnBeginClose(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Vola BeginClose() nasledujuceho CL. Nie OnBeginClose() pretoze ta je protected.
			return(MInnerListener.BeginClose(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		protected override IAsyncResult OnBeginOpen(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Vola BeginOpen() nasledujuceho CL. Nie OnBeginOpen() pretoze ta je protected.
			return(MInnerListener.BeginOpen(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		protected override void OnClose(TimeSpan Timeout)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Vola Close() nasledujuceho CL. Nie OnClose() pretoze ta je protected.
			MInnerListener.Close(Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		protected override void OnEndClose(IAsyncResult Result)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Vola EndClose() nasledujuceho CL. Nie OnEndClose() pretoze ta je protected.
			MInnerListener.EndClose(Result);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		protected override void OnEndOpen(IAsyncResult Result)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Vola EndOpen() nasledujuceho CL. Nie OnEndOpen() pretoze ta je protected.
			MInnerListener.EndOpen(Result);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		protected override void OnOpen(TimeSpan Timeout)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Vola Open() nasledujuceho CL. Nie OnOpen() pretoze ta je protected.
			MInnerListener.Open(Timeout);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Virtualna metoda.
		// Definovana v rozhrani IChannelListener.
		// Sluzi na ziskanie property lubovolneho CL v stacku.
		// Ak dany CL nema takuto property posle volanie nizsie do stacku.
		public override T GetProperty<T>()
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			if (typeof(T)==typeof(CLogData))
				return((T) ((object) MLogData));

			return(MInnerListener.GetProperty<T>());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------