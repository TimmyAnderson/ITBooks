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
	internal sealed class COneWaySessionfulReceiver : ISomeContractOneWaySession
	{
//-------------------------------------------------------------------------------------------------------
		internal COneWaySessionfulReceiver()
		{
			CPrintHelper.Print("RECEIVER OBJECT: OneWaySessionfulReceiver !", "ctor");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SomeOperation(string Input)
		{
			CPrintHelper.Print("RECEIVER OBJECT: OneWaySessionfulReceiver !", String.Format("SomeOperation: {0}", Input));
		}
//-------------------------------------------------------------------------------------------------------
		public void SomeOtherOperation(string Input)
		{
			CPrintHelper.Print("RECEIVER OBJECT: OneWaySessionfulReceiver !", String.Format("SomeOtherOperation: {0}", Input));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------