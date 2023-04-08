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
// Trieda je mojou implementaciou BE, ktorej ulohou je vytvarat CL\CF pre dany Shape.
//-------------------------------------------------------------------------------------------------------
	public class CLCBindingElement : BindingElement
	{
//-------------------------------------------------------------------------------------------------------
		// Data pre log. Sluzi aj ako property BE ku ktorej sa pristupuje cez GetProperty<>().
		private CLogData										MLogData;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLCBindingElement(CLogData LogData)
		{
			MLogData=LogData;

			MLogData.WriteLog(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		public override BindingElement Clone()
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Nie je co klonovat, MLogData je singleton a tak iba vytvorim novu instanciu.
			return(new CLCBindingElement(MLogData));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		public override T GetProperty<T>(BindingContext Context)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Najprv zistim ci T nie je CLogData.
			if (typeof(T)==typeof(CLogData))
				return((T) ((object) MLogData));

			// Ak nie zavolam BindingContext a ten urobi toto.
			// 1. Vytvori klon kolekcie BE.
			// 2. Odstrani z nej aktualny BE - teda CLCBindingElement.
			// 3. Na novom vrchole kolekcie BE zavola GetProperty().
			// Takto sa enumeruje cela kolekcia BE.
			return(Context.GetInnerProperty<T>());
		}
//-------------------------------------------------------------------------------------------------------
		// Virtualna metoda.
		public override bool CanBuildChannelFactory<TShape>(BindingContext Context)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString(1));

			// !!! Tu by mohol byt nejaky test, ktory by zistil ci som schopny vytvorit stack CF. Kedze moj CH ma bezat za kazdych podmienok ziaden test tu nie je.

			// Volanie Context.CanBuildInnerChannelFactory() urobi toto.
			// 1. Vytvori klon kolekcie BE.
			// 2. Odstrani z nej aktualny BE - teda CLCBindingElement.
			// 3. Na novom vrchole kolekcie BE zavola CanBuildChannelFactory().
			// Takto sa enumeruje cela kolekcia BE.
			bool				CanBuild=Context.CanBuildInnerChannelFactory<TShape>();

			MLogData.WriteLog(CDebugHelper.GetMethodCallString(2),"Result: " + CanBuild);

			return(CanBuild);
		}
//-------------------------------------------------------------------------------------------------------
		// Virtualna metoda.
		public override bool CanBuildChannelListener<TShape>(BindingContext Context)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString(1));

			// !!! Tu by mohol byt nejaky test, ktory by zistil ci som schopny vytvorit stack CL. Kedze moj CH ma bezat za kazdych podmienok ziaden test tu nie je.

			// Volanie Context.CanBuildInnerChannelListener() urobi toto.
			// 1. Vytvori klon kolekcie BE.
			// 2. Odstrani z nej aktualny BE - teda CLCBindingElement.
			// 3. Na novom vrchole kolekcie BE zavola CanBuildChannelListener().
			// Takto sa enumeruje cela kolekcia BE.
			bool				CanBuild=Context.CanBuildInnerChannelListener<TShape>();

			MLogData.WriteLog(CDebugHelper.GetMethodCallString(2),"Result: " + CanBuild);

			return(CanBuild);
		}
//-------------------------------------------------------------------------------------------------------
		// Virtualna metoda.
		public override IChannelFactory<TShape> BuildChannelFactory<TShape>(BindingContext Context)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Najprv otestujem ci sa CF da vytvorit.
			if(!this.CanBuildChannelFactory<TShape>(Context))
				throw(new InvalidOperationException("Unsupported channel type !"));

			if (Context==null)
				throw(new ArgumentNullException("Context"));

			// Vytvorim si svoju CF.
			// !!! V jej konstruktore sa vola Context.BuildInnerChannelFactory<TShape>() a ten sposobi toto.
			// 1. Odstrani z nej aktualny BE - teda CLCBindingElement - uz sa nerobi klon kolekcie BE.
			// 2. Na novom vrchole kolekcie BE zavola BuildChannelFactory().
			// !!! Takto sa enumeruje cela kolekcia BE a vytvara stack CF.
			CLCChannelFactory<TShape>		Factory=new CLCChannelFactory<TShape>(Context,MLogData);

			return((IChannelFactory<TShape>) Factory);
		}
//-------------------------------------------------------------------------------------------------------
		// Virtualna metoda.
		public override IChannelListener<TShape> BuildChannelListener<TShape>(BindingContext Context)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Najprv otestujem ci sa CL da vytvorit.
			if(!this.CanBuildChannelListener<TShape>(Context))
				throw(new InvalidOperationException("Unsupported channel type !"));

			if (Context==null)
				throw(new ArgumentNullException("Context"));

			// Vytvorim si svoj CL.
			// !!! V jej konstruktore sa vola Context.BuildInnerChannelListener<TShape>() a ten sposobi toto.
			// 1. Odstrani z nej aktualny BE - teda CLCBindingElement - uz sa nerobi klon kolekcie BE.
			// 2. Na novom vrchole kolekcie BE zavola BuildChannelListener().
			// !!! Takto sa enumeruje cela kolekcia BE a vytvara stack CL.
			CLCChannelListener<TShape>		Listener=new CLCChannelListener<TShape>(Context,MLogData);

			return((IChannelListener<TShape>) Listener);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------