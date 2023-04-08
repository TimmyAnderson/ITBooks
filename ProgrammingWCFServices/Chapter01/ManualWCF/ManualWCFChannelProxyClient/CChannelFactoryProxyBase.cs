using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
/*
	Bazicka trieda pre proxy vyuzivajuce ChannelFactory.
*/
//-------------------------------------------------------------------------------------------------------
namespace ManualWCFChannelProxyClient
{
//-------------------------------------------------------------------------------------------------------
	// Zapuzdruje pracu s ChannelFactory.
	class CChannelFactoryProxyBase<T> where T : class
	{
//-------------------------------------------------------------------------------------------------------
		protected ChannelFactory<T>								MChannelFactory;
		protected T												MContract;
		protected Binding										MBinding;
		protected EndpointAddress								MEndpointAddress;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected CChannelFactoryProxyBase(Binding Binding, EndpointAddress EndpointAddress)
		{
			MBinding=Binding;
			MEndpointAddress=EndpointAddress;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Open()
		{
			Close();

			// Po ChannelFactory.Close() je vzdy treba vytvorit novu instanciu ChannelFactory.
			MChannelFactory=new ChannelFactory<T>(MBinding, MEndpointAddress);
			MContract=MChannelFactory.CreateChannel();
		}
//-------------------------------------------------------------------------------------------------------
		public void Close()
		{
			try
			{
				// !!! Po volani Close() musim vytvorit cely objekt ChannelFactory<> znova.
				if (MChannelFactory!=null)
					MChannelFactory.Close();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("!!! EXCEPTION: {0} !",E.Message));
			}
			finally
			{
				MContract=null;
				MChannelFactory=null;
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------