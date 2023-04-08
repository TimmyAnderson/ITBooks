using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace Service
{
//-------------------------------------------------------------------------------------------------------
	public class CMyCustomAuthorizationService : IMyCustomAuthorizationService
	{
//-------------------------------------------------------------------------------------------------------
		private void PrintSecurityInfo(string MethodName)
		{
			// !!!!! Pristupujem ku CUSTOM implementacii IPrincipal.
			CMyCustomPrincipal		CP=(CMyCustomPrincipal) Thread.CurrentPrincipal;

			Console.WriteLine(string.Format("-------------------- {0} --------------------",MethodName));
			Console.WriteLine(string.Format("IsAuthenticated: [{0}] !",CP.Identity.IsAuthenticated.ToString().ToUpper()));
			Console.WriteLine(string.Format("Name: [{0}] !",CP.Identity.Name.ToUpper()));
			Console.WriteLine(string.Format("Is BOY: [{0}] !",CP.IsInRole("Boys").ToString().ToUpper()));
			Console.WriteLine(string.Format("Is GIRL: [{0}] !",CP.IsInRole("Girls").ToString().ToUpper()));
			Console.WriteLine(string.Format("Is CHILD: [{0}] !",CP.IsInRole("Children").ToString().ToUpper()));
			Console.WriteLine(string.Format("-------------------- {0} --------------------",MethodName));
			Console.WriteLine("");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Method1()
		{
			PrintSecurityInfo("Method1");
		}
//-------------------------------------------------------------------------------------------------------
		public void Method2()
		{
			PrintSecurityInfo("Method2");
		}
//-------------------------------------------------------------------------------------------------------
		public void Method3()
		{
			PrintSecurityInfo("Method3");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------