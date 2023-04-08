using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Security.Permissions;
using System.Security.Principal;
//-------------------------------------------------------------------------------------------------------
namespace SharedLibrary
{
//-------------------------------------------------------------------------------------------------------
	public static class CHelperClass
	{
//-------------------------------------------------------------------------------------------------------
		public static void HostHelper<T>()
		{
			try
			{
				using(ServiceHost SH=new ServiceHost(typeof(T)))
				{
					try
					{
						SH.Open();

						Console.WriteLine("Press any key to STOP !");
						Console.ReadLine();
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
							Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
						else
							Console.WriteLine(string.Format("EXCEPTION: [{0}], INNER EXCEPTION: [{1}] !",E.Message,E.InnerException.Message));
					}
				}
			}
			catch(Exception E)
			{
				if (E.InnerException==null)
					Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
				else
					Console.WriteLine(string.Format("EXCEPTION: [{0}], INNER EXCEPTION: [{1}] !",E.Message,E.InnerException.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static void ShowUserNameAuthentificationInfo(string FunctionName)
		{
			IPrincipal			CP=Thread.CurrentPrincipal;

			Console.WriteLine(string.Format("-------------------- {0} --------------------",FunctionName));
			Console.WriteLine(string.Format("IsAuthenticated: [{0}] !",CP.Identity.IsAuthenticated.ToString().ToUpper()));
			Console.WriteLine(string.Format("Name: [{0}] !",CP.Identity.Name.ToUpper()));
			Console.WriteLine(string.Format("Is BOY: [{0}] !",CP.IsInRole("Boys").ToString().ToUpper()));
			Console.WriteLine(string.Format("Is GIRL: [{0}] !",CP.IsInRole("Girls").ToString().ToUpper()));
			Console.WriteLine(string.Format("-------------------- {0} --------------------",FunctionName));
			Console.WriteLine("");
		}
//-------------------------------------------------------------------------------------------------------
		public static void ShowWindowsAuthentificationInfo(string FunctionName)
		{
			IPrincipal			CP=Thread.CurrentPrincipal;

			Console.WriteLine(string.Format("-------------------- {0} --------------------",FunctionName));
			Console.WriteLine(string.Format("IsAuthenticated: [{0}] !",CP.Identity.IsAuthenticated.ToString().ToUpper()));
			Console.WriteLine(string.Format("Name: [{0}] !",CP.Identity.Name.ToUpper()));
			Console.WriteLine(string.Format("Is in Administrators: [{0}] !",CP.IsInRole("Administrators").ToString().ToUpper()));
			Console.WriteLine(string.Format("-------------------- {0} --------------------",FunctionName));
			Console.WriteLine("");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------