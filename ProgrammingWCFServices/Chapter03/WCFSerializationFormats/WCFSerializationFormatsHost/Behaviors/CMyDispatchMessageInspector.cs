using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.ServiceModel.Dispatcher;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace WCFSerializationFormatsHost
{
//-------------------------------------------------------------------------------------------------------
	public class CMyDispatchMessageInspector : IDispatchMessageInspector
	{
//-------------------------------------------------------------------------------------------------------
		public object AfterReceiveRequest(ref Message Request, IClientChannel channel,InstanceContext InstanceContext)
		{
			return(null);
		}
//-------------------------------------------------------------------------------------------------------
		public void BeforeSendReply(ref Message Reply, object CorrelationState)
		{
			string				Content=Reply.ToString();

			Console.WriteLine("\nMessage:\n");
			Console.WriteLine(Content);

			try
			{
				using (FileStream Writer=new FileStream("..//..//..//!Files//Message.xml", FileMode.Create))
				{
					using (StreamWriter SW=new StreamWriter(Writer))
					{
						SW.Write(Content);
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------