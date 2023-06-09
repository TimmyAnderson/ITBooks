using System;
using System.Collections.Generic;
using System.Text;
using CallbackContractHierarchyLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CallbackContractHierarchyClient
{
//-------------------------------------------------------------------------------------------------------
	public class CCallbackContractHierarchyCatcher : ICallbackContractHierarchyCallback2
	{
//-------------------------------------------------------------------------------------------------------
		private string											MClientName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CCallbackContractHierarchyCatcher(string ClientName)
		{
			MClientName=ClientName;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void OnCallback1(string Message)
		{
			Console.WriteLine(string.Format("PROXY: {0} FROM SERVER: {1} !",MClientName,Message));
		}
//-------------------------------------------------------------------------------------------------------
		public void OnCallback2(string MessagePart1, string MessagePart2)
		{
			Console.WriteLine(string.Format("PROXY: {0} FROM SERVER: ({1},{2}) !",MClientName,MessagePart1,MessagePart2));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------