using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ReentrancyTestHost;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace ReentrancyTestClient
{
//-------------------------------------------------------------------------------------------------------
	//[CallbackBehavior(ConcurrencyMode=ConcurrencyMode.Multiple)]
	public class CCallback : ICallback
	{
//-------------------------------------------------------------------------------------------------------
		public void SomeCallback(string Value)
		{
			Console.WriteLine(string.Format("CALLBACK BEGIN Value: {0} !",Value));

			Thread.Sleep(10*1000);

			Console.WriteLine(string.Format("CALLBACK END Value: {0} !",Value));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------