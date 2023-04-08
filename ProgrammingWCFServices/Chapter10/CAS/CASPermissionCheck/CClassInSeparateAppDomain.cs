using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security;
//-------------------------------------------------------------------------------------------------------
namespace CASPermissionCheck
{
//-------------------------------------------------------------------------------------------------------
	// Musim ju dedit MarshalByRefObject, kedze bude pouzita v INEJ APP DOMAIN a ja chcem k nej pristupovat z akutalnej AppDomain.
	public class CClassInSeparateAppDomain : MarshalByRefObject
	{
//-------------------------------------------------------------------------------------------------------
		private void WriteToFile(string Message)
		{
			try
			{
				using (StreamWriter SW=new StreamWriter("..\\..\\TEST.txt",true))
				{
					SW.WriteLine(string.Format("Time: [{0}], Message: [{1}] !",DateTime.Now.ToString(),Message));
				}
			}
			catch(IOException E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Test()
		{
			try
			{
				Console.WriteLine(string.Format("ACTUAL APP DOMAIN: {0} !",AppDomain.CurrentDomain.FriendlyName));

				WriteToFile("Test() - In NEW APP DOMAIN");

				Console.WriteLine("Test() - SUCESSFULLY CALLED !");
			}
			catch(SecurityException E)
			{
				Console.WriteLine(string.Format("Test() - SECURITY EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------