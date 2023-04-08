using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannel
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CDelegatorBindingElement : BindingElement
	{
//-------------------------------------------------------------------------------------------------------
		public override bool CanBuildChannelFactory<TShape>(BindingContext Context)
		{
			return(Context.CanBuildInnerChannelFactory<TShape>());
		}
//-------------------------------------------------------------------------------------------------------
		public override bool CanBuildChannelListener<TShape>(BindingContext Context)
		{
			return(Context.CanBuildInnerChannelListener<TShape>());
		}
//-------------------------------------------------------------------------------------------------------
		public override IChannelFactory<TShape> BuildChannelFactory<TShape>(BindingContext Context)
		{
			if(!this.CanBuildChannelFactory<TShape>(Context))
				throw(new InvalidOperationException("Unsupported channel type !"));

			if (Context==null)
				throw(new ArgumentNullException("context"));

			CDelegatorChannelFactory<TShape>		Factory=new CDelegatorChannelFactory<TShape>(Context);

			return((IChannelFactory<TShape>) Factory);
		}
//-------------------------------------------------------------------------------------------------------
		public override IChannelListener<TShape> BuildChannelListener<TShape>(BindingContext Context)
		{
			if(!this.CanBuildChannelListener<TShape>(Context))
				throw(new InvalidOperationException("Unsupported channel type !"));

			if (Context==null)
				throw(new ArgumentNullException("context"));

			CDelegatorChannelListener<TShape>		Listener=new CDelegatorChannelListener<TShape>(Context);

			return((IChannelListener<TShape>) Listener);
		}
//-------------------------------------------------------------------------------------------------------
		public override BindingElement Clone()
		{
			return(new CDelegatorBindingElement());
		}
//-------------------------------------------------------------------------------------------------------
		public override T GetProperty<T>(BindingContext Context)
		{
			return(Context.GetInnerProperty<T>());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------