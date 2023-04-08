using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.Transactions;
using System.ServiceModel.Description;
using DelegatorChannel;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannelTest
{
//-------------------------------------------------------------------------------------------------------
	internal sealed class COneWayReceiver : ISomeContractOneWay
	{
//-------------------------------------------------------------------------------------------------------
		public COneWayReceiver()
		{
			CPrintHelper.Print("RECEIVER OBJECT: OneWayReceiver !", "ctor");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// ISomeContract implementation.
		public void SomeOperation(string Input)
		{
			CPrintHelper.Print("RECEIVER OBJECT: OneWayReceiver !", string.Format("SomeOperation: {0}", Input));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------