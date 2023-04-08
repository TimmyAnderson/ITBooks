using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.Net.Security;
//-------------------------------------------------------------------------------------------------------
namespace SecurityWithPrivateQueuesService
{
//-------------------------------------------------------------------------------------------------------
	public class CPrintService : IPrintService
	{
//-------------------------------------------------------------------------------------------------------
		public void PrintText(string Text)
		{
			ServiceSecurityContext		SSC=ServiceSecurityContext.Current;
			

			Console.WriteLine(string.Format("PRINCIPAL.PrimaryIdentity: [{0}] !",SSC.PrimaryIdentity.Name));
			Console.WriteLine(string.Format("PRINCIPAL.WindowsIdentity: [{0}] !",SSC.WindowsIdentity.Name));

			Console.WriteLine(string.Format("SERVICE: [{0}] !",Text));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------